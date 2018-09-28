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
   //-----------------------------------------------------------------------------------------------//
   class Q_DECL_EXPORT menuitemdata;
   class Q_DECL_EXPORT submenuitemdata : public list<menuitemdata *>
   {
   public:
      using pointer = shared_ptr<submenuitemdata>;
      using value_type = list<menuitemdata *>;
      /**/
   public:
      submenuitemdata() = default;
      virtual ~submenuitemdata() = default;
      menuitemdata * operator[](unicodestring const & name);
      virtual menuitemdata * find(unicodestring const & name);
      /**/
   protected:
      virtual menuitemdata * find(unicodestring const & name, submenuitemdata const * sub_d);
   };
};