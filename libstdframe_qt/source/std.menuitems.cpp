//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012, 2018, 2026
// For
//
// 2WW Engenharia de Sistemas
// (c) 2012, 2026
//-----------------------------------------------------------------------------------------------//
#include <std.menuitemdata.hpp>
#include <std.menuitems.hpp>
#include <std.submenuitemdata.hpp>
//-----------------------------------------------------------------------------------------------//
using namespace std;
//-----------------------------------------------------------------------------------------------//
menuitems::menuitems(unicodestring const& name) : value_type{}, QObject{}
{
   setObjectName(name);
}
//-----------------------------------------------------------------------------------------------//
menuitems::menuitems(menuitems const& items) : value_type{ items }, QObject{}
{
}
//-----------------------------------------------------------------------------------------------//
menuitems& menuitems::operator+(menuitemdata* d)
{
   if (d)
   {
      push_back(d);
   }
   return *this;
}
//-----------------------------------------------------------------------------------------------//
menuitems& menuitems::separator()
{
   return operator+(new menuitemdata{ captions::tokens{}.SEPARATOR, QIcon{}, false, false });
}
//-----------------------------------------------------------------------------------------------//
menuitemdata* menuitems::finditem(unicodestring const& name)
{
   menuitemdata* result = nullptr;
   //
   for (auto d = begin(); d != end() && result == nullptr; d++)
   {
      auto value = *d;
      result = (name.compare(value->get_caption()) == 0 ? value : result);
      result = (value->is_submenu() && result == nullptr ?
                value->get_submenuitemdata()->find(name) : result);
   }
   return result;
}
//-----------------------------------------------------------------------------------------------//
template<typename caption_t> requires(is_fundamental_v<caption_t>) auto set_caption(caption_t const&& caption)
{
   setObjectName(forward<caption_t>(caption));
   return *this;
}
//-----------------------------------------------------------------------------------------------//
unicodestring const menuitems::get_caption() const
{
   return static_cast<unicodestring>(objectName());
}
//-----------------------------------------------------------------------------------------------//
