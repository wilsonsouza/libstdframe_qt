//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.action.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   void const action::set_notify_everything()
   {
      connect(this, &action::changed, [=]()
      {
         dispatch_event(on_changed, this);
      });
      connect(this, &action::hovered, [=]()
      {
         dispatch_event(on_hovered, this);
      });
      connect(this, &action::toggled, [=](bool const & checked_value)
      {
         auto value_id = 0u;
         dispatch_event(on_toggled, checked_value, this);
         /**/
         if (isEnabled())
         {
            value_id |= uint(state::ENABLED);
         }
         /**/
         if (isChecked())
         {
            value_id |= uint(state::CHECKED);
         }
         /**/
         dispatch_event(on_update_ui, this, checked_value, value_id);
      });
      connect(this, &action::triggered, [=](bool const & checked_value)
      {
         dispatch_event(on_command, checked_value, this);
      });
   }
   //-----------------------------------------------------------------------------------------------//
}