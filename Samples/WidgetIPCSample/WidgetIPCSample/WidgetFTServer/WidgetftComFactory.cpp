#include "pch.h"

#include "WidgetftFactory.h"

using namespace Microsoft::WRL;

CoCreatableClass(WidgetftComFactory);

class WidgetftComFactory :
    public Microsoft::WRL::RuntimeClass<
    Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::WinRtClassicComMix>,
    IActivationFactory>
{
    STDMETHODIMP ActivateInstance(__RPC__deref_out_opt IInspectable** instance) noexcept try
    {
        THROW_HR_IF_NULL(E_POINTER, instance);
        auto factory = winrt::make_self<winrt::WidgetFTServer::implementation::WidgetftFactory>();
        auto insp = factory.as<IInspectable>();
        *instance = insp.detach();
        return S_OK;
    }
    CATCH_RETURN();
};
