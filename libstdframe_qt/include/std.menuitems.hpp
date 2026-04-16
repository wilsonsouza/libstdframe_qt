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
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.defs.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT menuitemdata;
   class Q_DECL_EXPORT menuitems : public list<menuitemdata*>, public QObject
   {
   public:
      using pointer = shared_ptr<menuitems>;
      using value_type = list<menuitemdata*>;
      /**/
   public:
      menuitems() = default;
      explicit menuitems(unicodestring const& name);
      explicit menuitems(menuitems const& items);
      virtual ~menuitems() = default;
      virtual menuitems& operator+(menuitemdata* d);
      menuitems& separator();
      menuitemdata* finditem(std::unicodestring const& name);
      template<typename caption_t> requires(is_fundamental_v<caption_t>) auto set_caption(caption_t const&& caption);
      unicodestring const get_caption() const;
   };
}