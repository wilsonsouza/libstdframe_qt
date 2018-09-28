//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//
// Last Updated: introduce new technical of c++14
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.defsx.hpp>
#include <std.layouts.hpp>
#include <std.icons.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT button;
   class Q_DECL_EXPORT timer;
   class Q_DECL_EXPORT dialog;
   class Q_DECL_EXPORT checkbox;
   class Q_DECL_EXPORT dialog_impl : public QDialog, public task_group
   {
   public:
      explicit dialog_impl(QWidget * owner, Qt::WindowFlags flags, unicodestring const & name) :
         QDialog{ owner, flags },
         task_group{},
         m_verticallay{ new vertical_box{ this, name } },
         m_buttons{ new horizontal_box{ this, HORIZONTAL_LAYOUT_BUTTONS_NAME } }
      {
         setObjectName(name);
         setWindowTitle(name);
      }
      ~dialog_impl() override = default;
      virtual bool create(dialog * dlg) = 0;
      vertical_box * vbox() const
      {
         return m_verticallay;
      }
      horizontal_box * vbuttons() const
      {
         return m_buttons;
      }
      //
   public:
      function<bool const(dialog * dlg)> on_create{ nullptr };
      function<bool const(dialog * dlg)> on_close{ nullptr };
      function<bool const(dialog * dlg, shared_ptr<timer> const & timer_ptr)> on_timer{ nullptr };
      function<bool const(dialog * sender, QEvent * event_ptr, void * param_ptr)> on_notify{ nullptr };
      function<bool const(dialog * dlg, long const & cmd_value, QObject * sender)> on_command{ nullptr };
      /**/
   protected:
      button * m_ok{ nullptr };
      button * m_cancel{ nullptr };
      button * m_help{ nullptr };
      shared_ptr<icons_impl<icons::common>> m_iconslist{ new icons_impl<icons::common>{} };
      shared_ptr<timer> m_timer{ nullptr };
      unicodestring const HORIZONTAL_LAYOUT_BUTTONS_NAME{ "HORIZONTAL_BUTTONS_LAYOUT" };
   private:
      vertical_box * m_verticallay{ nullptr };
      horizontal_box * m_buttons{ nullptr };
   };
}