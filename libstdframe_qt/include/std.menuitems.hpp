//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.defs.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT menuitemdata;
   class Q_DECL_EXPORT menuitems : public list<menuitemdata *>, public QObject
   {
   public:
      using pointer = shared_ptr<menuitems>;
      using value_type = list<menuitemdata *>;
      /**/
   public:
      menuitems() = default;
      explicit menuitems(unicodestring const & name);
      explicit menuitems(menuitems const & items);
      virtual ~menuitems() = default;
      virtual menuitems & operator+(menuitemdata * d);
      menuitems & separator();
      menuitemdata * finditem(std::unicodestring const & name);
      template<typename Caption> menuitems * set_caption(Caption const && caption);
      unicodestring const get_caption() const;
   };
}