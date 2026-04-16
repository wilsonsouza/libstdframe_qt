//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012, 2018, 2026
// For many platform
//
// 2WW Engenharia de Sistemas
// (c) 2012, 2026
//-----------------------------------------------------------------------------------------------//
#include <std.action.hpp>
//-----------------------------------------------------------------------------------------------//
using namespace std;
//-----------------------------------------------------------------------------------------------//
action::action(type_object* object,
               unicodestring const&& name,
               type_icon const&& icon) :
   implement::action{ object,
   std::remove_reference_t<unicodestring>(name),
   std::remove_reference_t<type_icon>(icon) }
{
   set_notify_everything();
}
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
   connect(this, &action::toggled, [=](bool const& checked_value)
   {
      auto value_id = 0u;
      dispatch_event(on_toggled, checked_value, this);
      /**/
      if (isEnabled())
      {
         value_id |= static_cast<uint>(state::ENABLED);
      }
      /**/
      if (isChecked())
      {
         value_id |= static_cast<uint>(state::CHECKED);
      }
      /**/
      dispatch_event(on_update_ui, this, checked_value, value_id);
   });
   connect(this, &action::triggered, [=](bool const& checked_value)
   {
      dispatch_event(on_command, checked_value, this);
   });
}
//-----------------------------------------------------------------------------------------------//
