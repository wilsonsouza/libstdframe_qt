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
   //-----------------------------------------------------------------------------------------------//
   class Q_DECL_EXPORT menuitemdata;
   class Q_DECL_EXPORT submenuitemdata : public list<menuitemdata *>
   {
   public:
      using pointer = unique_ptr<submenuitemdata>;
      using value_type = list<menuitemdata *>;
      /**/
   public:
      submenuitemdata() = default;
      submenuitemdata(submenuitemdata const&&) = delete;
      virtual ~submenuitemdata() = default;
      void operator=(submenuitemdata const&&) = delete;
      menuitemdata * operator[](unicodestring const & name);
      virtual menuitemdata * find(unicodestring const & name);
      /**/
   protected:
      virtual menuitemdata * find(unicodestring const & name, submenuitemdata const * sub_d);
   };
};