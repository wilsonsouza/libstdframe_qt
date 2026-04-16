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
#include <std.widget.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT control;
   //
   namespace implement
   {
      class Q_DECL_EXPORT control : public widget
      {
      public:
         using widget_type = QWidget;
      public:
         control() = delete;
         control(control const&) = delete;
         explicit control(widget_type* owner = nullptr, unicodestring const& name = unicodestring{}) :
            widget{ owner, name, Qt::WindowFlags{} }
         {
         }
         virtual ~control() override = default;
         template<typename T = control> requires(std::derived_from<T, widget_type>::value) void operator=(T const&) = delete;
         /**/
      public:
         function<bool(control* sender, QEvent* e)> on_action{ nullptr };
         function<bool(control* sender, QEvent* e)> on_change{ nullptr };
         function<bool(control* sender, QEvent* e)> on_close{ nullptr };
         function<bool(control* sender, QEvent* e)> on_context_menu{ nullptr };
         function<bool(control* sender, QEvent* e)> on_drag_enter{ nullptr };
         function<bool(control* sender, QEvent* e)> on_drag_leave{ nullptr };
         function<bool(control* sender, QEvent* e)> on_drag_move{ nullptr };
         function<bool(control* sender, QEvent* e)> on_drop{ nullptr };
         function<bool(control* sender, QEvent* e)> on_enter{ nullptr };
         function<bool(control* sender, QEvent* e)> on_focus_in{ nullptr };
         function<bool(control* sender, QEvent* e)> on_focus_out{ nullptr };
         function<bool(control* sender, QEvent* e)> on_hide{ nullptr };
         function<bool(control* sender, QEvent* e)> on_input_method{ nullptr };
         function<bool(control* sender, QEvent* e)> on_key_press{ nullptr };
         function<bool(control* sender, QEvent* e)> on_key_release{ nullptr };
         function<bool(control* sender, QEvent* e)> on_leave{ nullptr };
         function<bool(control* sender, QEvent* e)> on_mouse_double_click{ nullptr };
         function<bool(control* sender, QEvent* e)> on_mouse_move{ nullptr };
         function<bool(control* sender, QEvent* e)> on_mouse_press{ nullptr };
         function<bool(control* sender, QEvent* e)> on_mouse_release{ nullptr };
         function<bool(control* sender, QEvent* e)> on_move{ nullptr };
         function<bool(control* sender, QEvent* e)> on_paint{ nullptr };
         function<bool(control* sender, QEvent* e)> on_resize{ nullptr };
         function<bool(control* sender, QEvent* e)> on_show{ nullptr };
         function<bool(control* sender, QEvent* e)> on_tablet{ nullptr };
         function<bool(control* sender, QEvent* e)> on_wheel{ nullptr };
      };
   }
   using control = implement::control;
};
//-----------------------------------------------------------------------------------------------//