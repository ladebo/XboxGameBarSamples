#pragma once

//#undef WINAPI_FAMILY
//#define WINAPI_FAMILY WINAPI_FAMILY_DESKTOP_APP
//#ifndef WIN32_LEAN_AND_MEAN
//#define WIN32_LEAN_AND_MEAN
//#endif
//#define NOMINMAX
//#include <windows.h>
//#ifdef GetCurrentTime
//#undef GetCurrentTime
//#endif
//#ifdef GetObject
//#undef GetObject
//#endif
//#ifdef SendMessage
//#undef SendMessage
//#endif
//#ifdef GetUserName
//#undef GetUserName
//#endif

#include <windows.h>
#include <sddl.h>

// c++/winrt
#include <Unknwn.h> // Enabled support for non-winrt interfaces

// WIL
// wil/cppwinrt.h enabled mixing of C++/WinRT and WIL exception types in a compatible way
// This file must come before other wil macro headers
#include <wil/cppwinrt.h>
#include <wil/resource.h>
#include <wil/result_macros.h>
#include <wil/result.h>
#include <wil/resource.h>

// WinRT
#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.Data.Json.h>
#include <winrt/Windows.Storage.h>

#include <Windows.UI.Xaml.Hosting.DesktopWindowXamlSource.h>

// WRL
#include <wrl.h>


// Local project
#include "WidgetftComFactory.h"

namespace WF = winrt::Windows::Foundation;
namespace WFC = winrt::Windows::Foundation::Collections;
