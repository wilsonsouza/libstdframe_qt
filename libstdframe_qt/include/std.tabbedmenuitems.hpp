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
#include <std.defsx.hpp>
#include <std.menuitemdata.hpp>
#include <std.menuitems.hpp>
#include <std.tabbeddefs.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   class Q_DECL_EXPORT tabbedmenuitems: public menuitems, public icons::tabbed
   {
   public:
      tabbedmenuitems();
   };
};