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
#include <std.submenuitemdata.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   menuitemdata * submenuitemdata::operator[](unicodestring const & name)
   {
      return find(name);
   }
   //-----------------------------------------------------------------------------------------------//
   menuitemdata * submenuitemdata::find(unicodestring const & name)
   {
      menuitemdata * result = nullptr;
      //
      for(auto d = begin(); d != end() && result == nullptr; d++)
      {
         auto value = *d;
         result = (name.compare(value->get_caption()) == 0 ? value : nullptr);
         result = (value->is_submenu() && result == nullptr ?
                   find(name, value->get_submenu_itemdata()) : result);
      }
      return result;
   }
   //-----------------------------------------------------------------------------------------------//
   menuitemdata * submenuitemdata::find(unicodestring const & name, submenuitemdata const * sub_d)
   {
      menuitemdata * result = nullptr;
      //
      for (auto d = sub_d->begin(); d != sub_d->end() && result == nullptr; d++)
      {
         auto value = *d;
         result = (name.compare(value->get_caption()) == 0 ? value : nullptr);
         result = (value->is_submenu() && result == nullptr ?
                   find(name, value->get_submenu_itemdata()) : result);
      }
      return result;
   }
}
