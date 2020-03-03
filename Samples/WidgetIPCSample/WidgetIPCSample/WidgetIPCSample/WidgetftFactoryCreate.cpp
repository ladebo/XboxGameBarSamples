#include "pch.h"
#include "WidgetftFactoryCreate.h"
#include "../WidgetFTServer/WidgetftComFactory.h"
#include "winrt\WidgetFTServer.h"


namespace winrt::WidgetIPCSample::implementation
{
    winrt::WidgetFTServer::WidgetftFactory WidgetftFactoryCreate()
    {
        winrt::com_ptr<IActivationFactory> widgetftComFactory;

        try
        {
            CoCreateInstance(
                __uuidof(WidgetftComFactory),
                nullptr,
                CLSCTX_LOCAL_SERVER,
                __uuidof(IActivationFactory),
                reinterpret_cast<void**>(widgetftComFactory.put_void()));
        }
        catch (...)
        {
            winrt::to_hresult();
        }

        winrt::com_ptr<::IInspectable> widgetftFactoryInsp;

        auto retVal = widgetftFactoryInsp.put();

        widgetftComFactory->ActivateInstance(retVal);
        //Object^ widgetftFactoryObj = reinterpret_cast<Object^>(widgetftFactoryInsp.get());
        auto widgetftFactoryObj = widgetftFactoryInsp.as<winrt::WidgetFTServer::WidgetftFactory>();
        //widgetftFactoryObj.Test();
		return widgetftFactoryObj;
    }
}