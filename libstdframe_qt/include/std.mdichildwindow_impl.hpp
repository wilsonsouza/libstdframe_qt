//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012, 2018, 2026
// For many platform
//
// 2WW Engenharia de Sistemas
// (c) 2012, 2026, 2015
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)

#include <std.defsx.hpp>
#include <std.layouts.hpp>
#include <std.widget_impl.hpp>
#include <std.icons.hpp>
//-----------------------------------------------------------------------------------------------//
namespace sql
{
   class Q_DECL_EXPORT query;
   class Q_DECL_EXPORT table;
};
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT mdichildwindow;
   namespace implement
   {
      class Q_DECL_EXPORT mdichildwindow : public QMdiSubWindow, public task_group
      {
      public:
         explicit mdichildwindow(QWidget* owner,
                                 unicodestring const& name = unicodestring{},
                                 Qt::WindowFlags f = Qt::WindowFlags{});
         virtual ~mdichildwindow() override = default;
         virtual bool close() = 0;
         virtual bool create(mdichildwindow* child) = 0;
         /**/
      public:
         function<bool const(mdichildwindow* sender)> on_close{ nullptr };
         function<bool const(mdichildwindow* sender)> on_activate{ nullptr };
         function<bool const(mdichildwindow* sender)> on_deactivate{ nullptr };
         function<bool const(mdichildwindow* sender, uint const& mode)> on_show{ nullptr };
         function<bool const(mdichildwindow* sender, QPoint const& p)> on_context_menu_requested{ nullptr };
         function<bool const(mdichildwindow* sender,
                             Qt::WindowStates old_states,
                             Qt::WindowStates new_states)> on_window_state_changed{ nullptr };
         function<bool const(QObject* sender, QObject* child, void* msg, void* data)> on_notify{ nullptr };
         /**/
      protected:
         icons_impl::pointer<icons::common> m_iconlist{ new icons_impl<icons::common>{} };
      };
   }
}