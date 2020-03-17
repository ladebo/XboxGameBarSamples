#include "pch.h"
#include "WidgetftFactoryCreate.h"
#include "../WidgetFTServer/WidgetftComFactory.h"
#include "winrt\WidgetFTServer.h"


namespace winrt::WidgetIPCSample::implementation
{
    winrt::WidgetFTServer::WidgetftFactory WidgetftFactoryCreate()
    {
        winrt::com_ptr<IActivationFactory> widgetftComFactory;
       winrt::check_hresult(CoCreateInstance(
            __uuidof(WidgetftComFactory),
            nullptr,
            CLSCTX_LOCAL_SERVER,
            __uuidof(IActivationFactory),
            reinterpret_cast<void**>(widgetftComFactory.put_void())));

        winrt::com_ptr<::IInspectable> widgetftFactoryInsp;
        widgetftComFactory->ActivateInstance(widgetftFactoryInsp.put());
        auto widgetftFactoryObj = widgetftFactoryInsp.as<winrt::WidgetFTServer::WidgetftFactory>();
        return widgetftFactoryObj;
    }
}