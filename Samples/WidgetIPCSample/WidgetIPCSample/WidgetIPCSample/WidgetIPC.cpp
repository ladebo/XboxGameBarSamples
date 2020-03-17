#include "pch.h"
#include "WidgetIPC.h"
#include "WidgetIPC.g.cpp"
#include "WidgetftFactoryCreate.h"

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
        //myButton().Content(box_value(L"Clicked"));

        auto widgetFactObj = WidgetftFactoryCreate();
        widgetFactObj.Test();
    }
}
