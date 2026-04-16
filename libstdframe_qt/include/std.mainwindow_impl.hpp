//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012, 2013, 2018
// For many platform
//
// 2WW Engenharia de Sistemas
// (c) 2012, 2026, 2013
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
   namespace implement
   {
      class mainwindow : public QMainWindow, public task_group, public popup
      {
      public:
         using pointer = unique_ptr<mainwindow>;
         using task_value = task_group;
         using window_value = QMainWindow;
         /**/
      public:
         explicit mainwindow(QWidget* owner,
                             unicodestring const& name,
                             Qt::WindowFlags f = Qt::WindowFlags{});
         virtual ~mainwindow() = default;
         /**/
      public:
         virtual bool create(mainwindow* wnd) = 0;
         virtual mainwindow* update() = 0;
         virtual mainwindow* show(window::mode const& mode) = 0;
         virtual mainwindow* set_change_style(unicodestring const& style) = 0;
         //
      public:
         function<bool const(bool const& checked, action* sender)> on_command{ nullptr };
         function<bool const(QWidget* sender)> on_create{ nullptr };
         function<bool const(QWidget* sender)> on_close{ nullptr };
         function<bool const(QWidget* sender)> on_activate{ nullptr };
         function<bool const(QWidget* sender)> on_deactivate{ nullptr };
         function<bool const(QWidget* sender, window::mode const& mode)> on_show{ nullptr };
         function<bool const(QWidget* sender, menuitemdata* data_ui, bool const& enabled)> on_update_ui{ nullptr };
         function<bool const(QObject* sender, long const msg, void* data)> on_notify{ nullptr };
      };
   }
}