//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012, 2018, 2026
// For
//
// 2WW Engenharia de Sistemas
// (c) 2012, 2026
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.defs.hpp>
#include <std.menuitems.hpp>
#include <std.menuitemdata.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   class popup : public list<menuitems*>, public QObject
   {
   public:
      using pointer = unique_ptr<popup>;
      using value_type = list<menuitems*>;
      //
   public:
      popup() = default;
      explicit popup(unicodestring const& name = unicodestring{});
      explicit popup(popup const& rhs);
      popup& operator+(menuitems* value);
      popup& operator+(popup const& value);
      virtual menuitemdata* operator[](unicodestring const& name);
      virtual menuitems* operator()(unicodestring const& name);
      virtual menuitems* findpopup(unicodestring const& name);
      template <typename find_t, typename value_t> find_t find(value_t const&& name);
      virtual menuitemdata* finditem(unicodestring const& name);//search_item
      popup& operator<<(menuitems* items);
   };
}