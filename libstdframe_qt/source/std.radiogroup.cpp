//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//-----------------------------------------------------------------------------------------------//
#include <std.radiogroup.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   radiogroup * radiogroup::add(stringlist const & items)
   {
      for_each(items.cbegin(), items.cend(), [=](unicodestring const & value)
      {
         auto control = new radiobutton{ nullptr, value, value, false, false };
         control->on_clicked = [this](bool const & checked, radiobutton * sender)->auto
         {
            return dispatch_event(sender->on_clicked, checked, sender);
         };
      });
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   radiogroup * radiogroup::set_enabled(unicodestring const & name,
                                        bool const & enabled,
                                        bool const & all)
   {
      if (all)
      {
         for_each(cbegin(), cend(), [=](auto const & value)
         {
            value.second->setEnabled(enabled);
         });
      }
      else
      {
         auto value_ptr = find(name);
         static_exception(value_ptr == end(), unicodestring{ "item %1 not found!" }.bind(name));
         value_ptr->second->setEnabled(enabled);
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   bool radiogroup::get_enabled(unicodestring const & name)
   {
      auto value_ptr = find(name);
      static_exception(value_ptr == end(), unicodestring{ "item %1 not found!" }.bind(name));
      return value_ptr->second->isEnabled();
   }
   radiobutton * radiogroup::get_byname(unicodestring const & name) const
   {
      auto value_ptr = find(name);
      static_exception(value_ptr == end(), unicodestring{ "item %1 not found!" }.bind(name));
      return(value_ptr->second);
   }
   //-----------------------------------------------------------------------------------------------//
   radiogroup::list_value_type const radiogroup::get_object_list() const
   {
      auto out_list = list_value_type{};
      //
      for_each(begin(), end(), [&](auto const & value)
      {
         out_list.push_back(value.second);
      });
      return out_list;
   }
   //-----------------------------------------------------------------------------------------------//
   radiogroup::hash_value_type const & radiogroup::get_object_mapper()
   {
      return *this;
   }
}