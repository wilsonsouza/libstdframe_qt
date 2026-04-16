//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012, 2013, 2018
// For many platform
//
// 2WW Engenharia de Sistemas
// (c) 2012, 2026, 2013
//-----------------------------------------------------------------------------------------------//
#include <std.button.hpp>
//-----------------------------------------------------------------------------------------------//
using namespace std;
//-----------------------------------------------------------------------------------------------//
button::button(QWidget* owner,
               unicodestring const& caption,
               QIcon const& icon_object,
               unicodestring const& name,
               bool const enabled) :QPushButton{ icon_object, caption, owner }
{
   setObjectName((name.empty() ? caption : name));
   this->setEnabled(static_cast<bool>(enabled));
   //
   connect(this, &QPushButton::clicked, [this](bool checked_value)
   {
      dispatch_event(on_clicked, checked_value, this);
   });
}

