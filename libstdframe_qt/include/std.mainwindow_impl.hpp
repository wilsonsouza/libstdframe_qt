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
#include <std.popup.hpp>

namespace std
{
   class Q_DECL_EXPORT menuitemdata;
   class Q_DECL_EXPORT action;
   class mainwindow_impl : public QMainWindow, public task_group, public shared_ptr < popup >
   {
   public:
      using pointer = shared_ptr<mainwindow_impl>;
      using task_value = task_group;
      using window_value = QMainWindow;
      /**/
   public:
      explicit mainwindow_impl(QWidget * owner, unicodestring const & name, Qt::WindowFlags f = 0) :
         QMainWindow{ owner, f },
         task_group{},
         popup::pointer{ new popup{name} }
      {
         setObjectName(name);
      }
      virtual ~mainwindow_impl() = default;
      /**/
   public:
      virtual bool create(mainwindow * wnd) = 0;
      virtual mainwindow * update() = 0;
      virtual mainwindow * show(uint const & mode = window::mode{}.MAXIMIZED) = 0;
      virtual mainwindow * set_change_style(unicodestring const & style) = 0;
      //
   public:
      function<bool const(bool const & checked, action * sender)> on_command{ nullptr };
      function<bool const(QWidget * sender)> on_create{ nullptr };
      function<bool const(QWidget * sender)> on_close{ nullptr };
      function<bool const(QWidget * sender)> on_activate{ nullptr };
      function<bool const(QWidget * sender)> on_deactivate{ nullptr };
      function<bool const(QWidget * sender, uint const & mode)> on_show{ nullptr };
      function<bool const(QWidget * sender, menuitemdata * data_ui, bool const & enabled)> on_update_ui{ nullptr };
      function<bool const(QObject * sender, long const msg, void * data)> on_notify{ nullptr };
   };
}