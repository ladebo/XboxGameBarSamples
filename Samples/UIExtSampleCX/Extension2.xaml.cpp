﻿//
// Extension2.xaml.cpp
// Implementation of the Extension2 class.
//

#include "pch.h"
#include "Extension2.xaml.h"

using namespace UIExtSampleCX;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

Extension2::Extension2()
{
	InitializeComponent();
}

void UIExtSampleCX::Extension2::MyButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	myButton->Content = "Clicked";
}