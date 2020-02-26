#pragma once

#include "WidgetIPC.g.h"

namespace winrt::WidgetIPCSample::implementation
{
    struct WidgetIPC : WidgetIPCT<WidgetIPC>
    {
        WidgetIPC();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void MyButton_Click(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::WidgetIPCSample::factory_implementation
{
    struct WidgetIPC : WidgetIPCT<WidgetIPC, implementation::WidgetIPC>
    {
    };
}
