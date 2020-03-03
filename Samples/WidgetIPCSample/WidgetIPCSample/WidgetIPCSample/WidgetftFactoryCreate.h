#pragma once

#include <Windows.h>
#include "winrt\WidgetFTServer.h"

namespace winrt::WidgetIPCSample::implementation
{
    WidgetFTServer::WidgetftFactory WidgetftFactoryCreate();
}
