//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012, 2018, 2026
// For many platform
//
// 2WW Engenharia de Sistemas
// (c) 2012, 2026
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <std.menu.hpp>
#include <std.popup.hpp>
//-----------------------------------------------------------------------------------------------//
using namespace std;
//-----------------------------------------------------------------------------------------------//
popup::popup(unicodestring const& name = unicodestring{}) : value_type{}, QObject{}
{
   setObjectName(name);
}
//-----------------------------------------------------------------------------------------------//
popup::popup(popup const& rhs) : value_type{}, QObject{}
{
   this->assign(rhs.begin(), rhs.end());
}
//-----------------------------------------------------------------------------------------------//
popup& popup::operator+(menuitems* value)
{
   if (value != nullptr)
   {
      push_back(value);
   }
   return *this;
}
//-----------------------------------------------------------------------------------------------//
popup& popup::operator+(popup const& value)
{
   for_each(value.begin(), value.end(), [=](menuitems* p)
   {
      push_back(p);
   });
   return *this;
}
//-----------------------------------------------------------------------------------------------//
menuitemdata* popup::operator[](unicodestring const& name)
{
   for (auto& value : *this)
   {
      if (auto out = value->finditem(name); (out != nullptr))
         return out;
   }
   return nullptr;
}
//-----------------------------------------------------------------------------------------------//
menuitems* popup::operator()(unicodestring const& name)
{
   return *find_if(begin(), end(), [&](auto const&& value)
   {
      return(name.compare(value->get_caption()));
   });
}
//-----------------------------------------------------------------------------------------------//
menuitems* popup::findpopup(unicodestring const& name)
{
   return this->operator()(name);
}
//-----------------------------------------------------------------------------------------------//
template <typename find_t, typename value_t> find_t popup::find(value_t const&& name)
{
   return static_cast<find_t>(this->operator()(forward(name)));
}
//-----------------------------------------------------------------------------------------------//
menuitemdata* popup::finditem(unicodestring const& name)//search_item
{
   return this->operator[](name);
}
//-----------------------------------------------------------------------------------------------//
popup& popup::operator<<(menuitems* items)
{
   return operator+(items);
}
//-----------------------------------------------------------------------------------------------//
