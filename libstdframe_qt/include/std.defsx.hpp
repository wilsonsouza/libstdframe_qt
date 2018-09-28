//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)

#include <std.defs.hpp>
#include <std.icons.hpp>
#include <std.captions.hpp>
#include <std.menuitemdata.hpp>
#include <std.submenuitemdata.hpp>
#include <std.action.hpp>
#include <std.menu.hpp>
#include <std.widget.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   struct edititems : public menuitems, public icons::edit
   {
      edititems();
   };
   //-----------------------------------------------------------------------------------------------//
   struct viewitems : public menuitems, public icons::initial_directory
   {
      viewitems();
   };
   //-----------------------------------------------------------------------------------------------//
   struct useritems : public menuitems, public icons::user
   {
      useritems();
   };
   //-----------------------------------------------------------------------------------------------//
   struct toolsitems : public menuitems, public icons::tools
   {
      toolsitems();
   };
   //-----------------------------------------------------------------------------------------------//
   struct helplibbsitems : public menuitems, public icons::help
   {
      helplibbsitems();
   };
   //-----------------------------------------------------------------------------------------------//
   struct helpwrdeveloperinfoitems : public menuitems, public icons::help
   {
      helpwrdeveloperinfoitems();
   };
   //-----------------------------------------------------------------------------------------------//
   struct fileitems : public menuitems, public icons::file
   {
      fileitems();
   };
   //-----------------------------------------------------------------------------------------------//
   struct analyzeritems : public menuitems, public icons::initial_directory
   {
      analyzeritems();
   };
   //-----------------------------------------------------------------------------------------------//
   //show mode
   namespace window
   {
      struct mode
      {
          const uint NORMAL = 0x01af;
          const uint MAXIMIZED = 0x02df;
          const uint MINIMIZED = 0x04ef;
          const uint HIDE = 0x08ab;
          const uint FULLSCREEN = 0x8ac;
          mode() = default;
          bool operator!=(uint const & value)
          {
             return(value != NORMAL || 
                    value != MAXIMIZED || 
                    value != MINIMIZED || 
                    value != HIDE || 
                    value != FULLSCREEN);
          }
      };

      //window states
      struct states
      {
          const uint NOSTATE = Qt::WindowNoState;
          const uint MINIMIZED = Qt::WindowMinimized;
          const uint MAXIMIZED = Qt::WindowMaximized;
          const uint FULLSCREEN = Qt::WindowFullScreen;
          const uint ACTIVE = Qt::WindowActive;
          states() = default;
      };

      //window Modality
      struct modality
      {
          const uint NONMODAL = Qt::NonModal;
          const uint WINDOWMODAL = Qt::WindowModal;
          const uint APPLICATIONMODAL = Qt::ApplicationModal;
          modality() = default;
      };
   }
   //-----------------------------------------------------------------------------------------------//
   struct styleitems : public menuitems, public icons::style
   {
      styleitems();
   };
   //-----------------------------------------------------------------------------------------------//
   struct windowitems : public menuitems, public icons::window
   {
      windowitems();
   };
}