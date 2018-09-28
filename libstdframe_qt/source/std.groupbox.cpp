//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <std.groupbox.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   groupbox::groupbox() : QGroupBox{}
   {
      set_notify_everything()->setObjectName(unicodestring{});
   }
   //-----------------------------------------------------------------------------------------------//
   groupbox::groupbox(unicodestring const & caption, QWidget * owner) : QGroupBox{ caption, owner }
   {
      set_notify_everything()->setObjectName(caption);
   }
   //-----------------------------------------------------------------------------------------------//
   groupbox::~groupbox()
   {
      disconnect();
   }
   //-----------------------------------------------------------------------------------------------//
   groupbox * groupbox::set_notify_everything()
   {
      connect(this, &QGroupBox::clicked, [=](bool checked)
      {
         dispatch_event(on_clicked, checked, this);
      });
      connect(this, &QGroupBox::toggled, [=](bool value)
      {
         dispatch_event(on_toggled, value, this);
      });
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
}
