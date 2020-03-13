#include "pch.h"

using namespace Microsoft::WRL;

//DEFINE_TRACE_AREA(WidgetFTServer, Utils::TraceLevel::Verbose);

// 0x11 = (COM_RIGHTS_EXECUTE | COM_RIGHTS_EXECUTE_LOCAL | COM_RIGHTS_ACTIVATE_LOCAL)
// O:PSG:BU   Owner : principal self, Group : Built - in users
// (A;;0x11;;;WD)  Allow SDDL_EVERYONE
// S-1-15-2-1714399563-1326177402-2048222277-143663168-2151391019-765408921-4098702777 is this package (Microsoft.XboxGamingOverlay) SID
const wchar_t* const c_ComSecurityDescriptor = L"O:PSG:BUD:(A;;11;;;WD)(A;;11;;;S-1-15-2-4028404679-3178261574-3795030958-2183307115-4290976547-500102433-721774397)S:(ML;;NX;;;LW)";

HRESULT InitializeComSecurity()
{
    wil::unique_hlocal_security_descriptor securityDescriptor;
    RETURN_LAST_ERROR_IF(!ConvertStringSecurityDescriptorToSecurityDescriptorW(
        c_ComSecurityDescriptor,
        SDDL_REVISION_1,
        &securityDescriptor,
        NULL));

    DWORD headerSize = 0;
    DWORD daclSize = 0;
    DWORD saclSize = 0;
    DWORD ownerSize = 0;
    DWORD groupSize = 0;

    // Convert to an absolute SD to extract pointers to different components; we
    // do this to avoid a dependency on internal APIs.
    MakeAbsoluteSD(securityDescriptor.get(), nullptr, &headerSize, nullptr, &daclSize,
        nullptr, &saclSize, nullptr, &ownerSize, nullptr, &groupSize);

    DWORD totalSize = headerSize + daclSize + saclSize + ownerSize + groupSize;

    wil::unique_hlocal_security_descriptor absoluteSd(reinterpret_cast<SECURITY_DESCRIPTOR*>(LocalAlloc(LMEM_FIXED, totalSize)));
    RETURN_IF_NULL_ALLOC(absoluteSd.get());

    BYTE* position = reinterpret_cast<BYTE*>(absoluteSd.get());
    PACL dacl = reinterpret_cast<PACL>(position += headerSize);
    PACL sacl = reinterpret_cast<PACL>(position += daclSize);
    PSID owner = reinterpret_cast<PSID>(position += saclSize);
    PSID group = reinterpret_cast<PSID>(position += ownerSize);

    RETURN_IF_WIN32_BOOL_FALSE(MakeAbsoluteSD(
        securityDescriptor.get(),
        absoluteSd.get(),
        &headerSize,
        dacl,
        &daclSize,
        sacl,
        &saclSize,
        owner,
        &ownerSize,
        group,
        &groupSize));

    RETURN_IF_FAILED(CoInitializeSecurity(
        absoluteSd.get(), 
        -1, 
        nullptr, 
        nullptr, 
        RPC_C_AUTHN_LEVEL_DEFAULT, 
        RPC_C_IMP_LEVEL_IDENTIFY, 
        nullptr, 
        EOAC_NONE, 
        nullptr));

    return S_OK;
}

int __stdcall wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    winrt::init_apartment();

    winrt::com_ptr<IGlobalOptions> globalOptions;
    THROW_IF_FAILED(CoCreateInstance(CLSID_GlobalOptions, nullptr, CLSCTX_INPROC, IID_PPV_ARGS(&globalOptions)));
    LOG_IF_FAILED(globalOptions->Set(COMGLB_RO_SETTINGS, COMGLB_FAST_RUNDOWN));

    LOG_IF_FAILED(InitializeComSecurity());

    winrt::hstring traceFolder;

    try
    {
        traceFolder = winrt::Windows::Storage::ApplicationData::Current().TemporaryFolder().Path();
    }
    catch (std::exception const&)
    {
        // Swallow exceptions.
    }
    catch (winrt::hresult_error&)
    {
        // Swallow exceptions.
    }

    //Utils::TraceManager::SetupTracing(traceFolder.data(), Utils::TraceFileProcess::WidgetFTServer); // It's ok to pass empty traceFolder.
    //Utils::TraceManager::ToggleFileTracing(true);

    /*wil::SetResultLoggingCallback([](_In_ wil::FailureInfo const& fi) noexcept
    {
        TRACE_ERROR(
            WidgetFTServer,
            L"%ws, hr=0x%08X ['%S' (%u)]",
            fi.pszMessage,
            fi.hr,
            fi.pszFile,
            fi.uLineNumber);
    });*/

    wil::unique_event shutdownEvent(wil::EventOptions::ManualReset);
    // Create WRL OOP module manager. Callback will be called when
    // all objects have disconnected. 
#pragma warning( disable : 4324 )
    auto &module = Module<OutOfProc>::Create([&]()
    {
        shutdownEvent.SetEvent();
    });

    // Register all WRL objects with COM. At this point COM will start connecting
    // CoCreateInstance requests.
    winrt::check_hresult(module.RegisterObjects());

    // Wait for module to signal that all objects have disconnected
    shutdownEvent.wait(INFINITE);

    // Unregister all objects from COM and shutdown. 
    winrt::check_hresult(module.UnregisterObjects());

    //Utils::TraceManager::ShutdownTracing();

    return 0;
}
