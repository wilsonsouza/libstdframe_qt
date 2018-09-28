//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.defs.hpp>
#include <std.action.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT toolbutton : public QToolButton
   {
      Q_OBJECT
   public:
      explicit toolbutton(QWidget * owner,
                          QIcon const & icon,
                          unicodestring const & caption = unicodestring{}) :QToolButton{ owner }
      {
         setObjectName(caption);
         setIcon(icon);
         set_notify_everything();
      }
      ~toolbutton() override
      {
         disconnect();
      }
      /* events */
   public:
      function<bool(action * sender, toolbutton * source)> on_clicked{ nullptr };
      function<bool(QObject * sender, long const & msg, long * data)> on_update_ui{ nullptr };
      //
   protected:
      virtual toolbutton * set_notify_everything();
   };
};
//-----------------------------------------------------------------------------------------------//
