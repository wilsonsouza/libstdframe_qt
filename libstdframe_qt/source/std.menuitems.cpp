//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.menuitemdata.hpp>
#include <std.menuitems.hpp>
#include <std.submenuitemdata.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   menuitems::menuitems(unicodestring const & name) : value_type{}, QObject{}
   {
      setObjectName(name);
   }
   //-----------------------------------------------------------------------------------------------//
   menuitems::menuitems(menuitems const & items) : value_type{ items }, QObject{}
   {
   }
   //-----------------------------------------------------------------------------------------------//
   menuitems & menuitems::operator+(menuitemdata * d)
   {
      if (d)
      {
         push_back(d);
      }
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   menuitems & menuitems::separator()
   {
      return operator+(new menuitemdata{ captions::tokens{}.SEPARATOR, QIcon{}, false, false });
   }
   //-----------------------------------------------------------------------------------------------//
   menuitemdata * menuitems::finditem(unicodestring const & name)
   {
      menuitemdata * result = nullptr;
      //
      for (auto d = begin(); d != end() && result == nullptr; d++)
      {
         auto value = *d;
         result = (name.compare(value->get_caption()) == 0 ? value : result);
         result = (value->is_submenu() && result == nullptr ?
                   value->get_submenu_itemdata()->find(name) : result);
      }
      return result;
   }
   //-----------------------------------------------------------------------------------------------//
   template<typename Caption> menuitems * menuitems::set_caption(Caption const && caption)
   {
      setObjectName(forward<Caption>(caption));
   }
   //-----------------------------------------------------------------------------------------------//
   unicodestring const menuitems::get_caption() const
   {
      return objectName();
   }
   //-----------------------------------------------------------------------------------------------//

}
