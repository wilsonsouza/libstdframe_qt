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
#include <std.menuitems.hpp>
#include <std.icons.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   struct edititems : public menuitems, public icons::edit
   {
      edititems() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct viewitems : public menuitems, public icons::initial_directory
   {
      viewitems() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct useritems : public menuitems, public icons::user
   {
      useritems() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct toolsitems : public menuitems, public icons::tools
   {
      toolsitems() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct helplibbsitems : public menuitems, public icons::help
   {
      helplibbsitems() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct helpwrdeveloperinfoitems : public menuitems, public icons::help
   {
      helpwrdeveloperinfoitems() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct fileitems : public menuitems, public icons::file
   {
      fileitems() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct analyzeritems : public menuitems, public icons::initial_directory
   {
      analyzeritems() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct styleitems : public menuitems, public icons::style
   {
      styleitems() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct windowitems : public menuitems, public icons::window
   {
      windowitems() = default;
   };
   //-----------------------------------------------------------------------------------------------//
}