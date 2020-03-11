#pragma once
#include "WidgetftFactory.g.h"

namespace winrt::WidgetFTServer::implementation
{
    struct WidgetftFactory : WidgetftFactoryT<WidgetftFactory>
    {
        WidgetftFactory();
        virtual ~WidgetftFactory();
        void Test();
    };
}