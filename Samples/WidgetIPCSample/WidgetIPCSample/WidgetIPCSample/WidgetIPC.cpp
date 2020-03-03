#include "pch.h"
#include "WidgetIPC.h"
#include "WidgetIPC.g.cpp"
#include "winrt\WidgetFTServer.h"

using namespace winrt;
using namespace winrt::Windows::UI::Xaml;

namespace winrt::WidgetIPCSample::implementation
{
    WidgetIPC::WidgetIPC()
    {
        InitializeComponent();
    }

    int32_t WidgetIPC::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void WidgetIPC::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void WidgetIPC::MyButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));

        winrt::com_ptr<IActivationFactory> widgetftComFactory;

        try
        {
            CoCreateInstance(
                __uuidof(widgetftComFactory),
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

        widgetftComFactory->ActivateInstance(widgetftFactoryInsp.put());
        //Object^ widgetftFactoryObj = reinterpret_cast<Object^>(widgetftFactoryInsp.get());
        auto widgetftFactoryObj = widgetftFactoryInsp.as<winrt::WidgetFTServer::WidgetftFactory>();
        widgetftFactoryObj.Test();
    }
}
