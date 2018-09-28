//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//-----------------------------------------------------------------------------------------------//
#include <std.toolbutton.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   toolbutton * toolbutton::set_notify_everything()
   {
      //redirect method call
      connect(this, &QToolButton::clicked, [this]()
      {
         dispatch_event(on_clicked, reinterpret_cast<action *>(defaultAction()), this);
      });
      connect(this, &QToolButton::toggled, [this](bool const & checked)
      {
         dispatch_event(on_update_ui, this, (long &)checked, (long *)isEnabled());
      });
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
}