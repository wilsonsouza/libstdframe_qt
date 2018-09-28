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
#include <std.action.hpp>
#include <std.toolbaritems.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   using qtoolbar = QToolBar;
   class Q_DECL_EXPORT toolbar : public qtoolbar
   {
      Q_OBJECT
   public:
      explicit toolbar(unicodestring const & caption,
                       QWidget * owner,
                       unicodestring const & name = "");
      ~toolbar() override = default;
      virtual toolbar * create(toolbaritems * items);
      virtual toolbar * set_enabled(unicodestring const & buttonname,
                                    bool const enabled);
      virtual bool const is_enabled(unicodestring const & buttonname);
      /**/
   public:
      function<bool(action * action, toolbar * sender)> on_command{ nullptr };
      function<bool(Qt::ToolBarAreas areas, toolbar * sender)> on_allowedareaschanged{ nullptr };
      function<bool(const QSize & siconsize, toolbar * sender) > on_iconsizechanged{ nullptr };
      function<bool(bool const & movable, toolbar * sender) > on_movablechanged{ nullptr };
      function<bool(Qt::Orientation orientation, toolbar * sender) > on_orientationchanged{ nullptr };
      function<bool(Qt::ToolButtonStyle style, toolbar * sender) > on_toolbuttonstylechanged{ nullptr };
      function<bool(bool const & toplevel, toolbar * sender) > on_toplevelchanged{ nullptr };
      function<bool(bool const & visible, toolbar * sender) > on_visibilitychanged{ nullptr };
      //
   protected:
      virtual toolbar * set_notify_everthing();
   };
   //-----------------------------------------------------------------------------------------------//
};