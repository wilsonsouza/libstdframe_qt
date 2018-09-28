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