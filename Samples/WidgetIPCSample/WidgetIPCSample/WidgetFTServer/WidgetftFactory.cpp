#include "pch.h"
#include "WidgetftFactory.h"

namespace winrt::WidgetFTServer::implementation
{
    WidgetftFactory::WidgetftFactory()
    {
        auto modulePtr = ::Microsoft::WRL::GetModuleBase();
        if (modulePtr != nullptr)
        {
            modulePtr->IncrementObjectCount();
        }
    }

    WidgetftFactory::~WidgetftFactory()
    {
        auto modulePtr = ::Microsoft::WRL::GetModuleBase();
        if (modulePtr != nullptr)
        {
            modulePtr->DecrementObjectCount();
        }
    }

    void WidgetftFactory::Test()
    {
        OutputDebugString(L"Hello this is  workinngggggg");
    }
}
