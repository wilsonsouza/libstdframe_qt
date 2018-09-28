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
#include <std.widget.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT control;
   class Q_DECL_EXPORT control_impl : public widget
   {
   public:
      explicit control_impl(QWidget * owner = nullptr, unicodestring const & name = unicodestring{}) :
         widget{ owner, name, 0 }
      {
      }
      ~control_impl() override = default;
      /**/
   public:
      function<bool(control * sender, QEvent * e)> on_action{ nullptr };
      function<bool(control * sender, QEvent * e)> on_change{ nullptr };
      function<bool(control * sender, QEvent * e)> on_close{ nullptr };
      function<bool(control * sender, QEvent * e)> on_context_menu{ nullptr };
      function<bool(control * sender, QEvent * e)> on_drag_enter{ nullptr };
      function<bool(control * sender, QEvent * e)> on_drag_leave{ nullptr };
      function<bool(control * sender, QEvent * e)> on_drag_move{ nullptr };
      function<bool(control * sender, QEvent * e)> on_drop{ nullptr };
      function<bool(control * sender, QEvent * e)> on_enter{ nullptr };
      function<bool(control * sender, QEvent * e)> on_focus_in{ nullptr };
      function<bool(control * sender, QEvent * e)> on_focus_out{ nullptr };
      function<bool(control * sender, QEvent * e)> on_hide{ nullptr };
      function<bool(control * sender, QEvent * e)> on_input_method{ nullptr };
      function<bool(control * sender, QEvent * e)> on_key_press{ nullptr };
      function<bool(control * sender, QEvent * e)> on_key_release{ nullptr };
      function<bool(control * sender, QEvent * e)> on_leave{ nullptr };
      function<bool(control * sender, QEvent * e)> on_mouse_double_click{ nullptr };
      function<bool(control * sender, QEvent * e)> on_mouse_move{ nullptr };
      function<bool(control * sender, QEvent * e)> on_mouse_press{ nullptr };
      function<bool(control * sender, QEvent * e)> on_mouse_release{ nullptr };
      function<bool(control * sender, QEvent * e)> on_move{ nullptr };
      function<bool(control * sender, QEvent * e)> on_paint{ nullptr };
      function<bool(control * sender, QEvent * e)> on_resize{ nullptr };
      function<bool(control * sender, QEvent * e)> on_show{ nullptr };
      function<bool(control * sender, QEvent * e)> on_tablet{ nullptr };
      function<bool(control * sender, QEvent * e)> on_wheel{ nullptr };
   };
   //-----------------------------------------------------------------------------------------------//
   class control : public control_impl
   {
   public:
      explicit control(QWidget * owner, unicodestring const & name = unicodestring{}) :
         control_impl{ owner, name }
      {
      }
      ~control() override = default;
   };
};
//-----------------------------------------------------------------------------------------------//