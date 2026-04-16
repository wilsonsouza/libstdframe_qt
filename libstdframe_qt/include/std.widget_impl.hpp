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
#include <std.defs.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   using qlayout = QLayout;
   class Q_DECL_EXPORT menu;
   class Q_DECL_EXPORT widget;
   //-----------------------------------------------------------------------------------------------//
   template<typename layout_t> concept is_layout = is_base_of_v<qlayout, layout_t>;
   //-----------------------------------------------------------------------------------------------//
   template<typename layout_t> requires is_layout<layout_t>
   class Q_DECL_EXPORT widget_impl : virtual public layout_t, virtual public QWidget
   {
   public:
      using value_type = layout_t;
      //
   public:
      explicit widget_impl(QWidget* owner,
                           unicodestring const& name,
                           Qt::WindowFlags flags = {}) :
         QWidget{ owner, std::move(flags) }
      {
         QWidget::setObjectName(name + "_widget");
         QWidget::setLayout(dynamic_cast<layout_t*>(this));
      }
      virtual ~widget_impl() override
      {
         value_type::disconnect();
      }
      template<typename object_t>
         requires(is_layout<object_t> || is_base_of<QWidget, object_t>) auto operator->()
      {
         return dynamic_cast<object_t*>(this);
      }
      /**/
   public:
      function<bool(QPoint const& pt, widget_impl<value_type>* sender)> on_context_menu_requested{ nullptr };
   };
}