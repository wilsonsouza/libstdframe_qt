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
#include <std.groupbox.hpp>
#include <std.layouts.hpp>
#include <std.treewidget.hpp>
#include <std.treewidgetitem.hpp>
#include <std.treeview.hpp>
//-----------------------------------------------------------------------------------------------//

namespace std
{
   //-----------------------------------------------------------------------------------------------//
   template <class treewidget_t = treewidget, class layout_t = vertical_box>
   class Q_DECL_EXPORT groupbox_widget_impl : public groupbox, public layout_t
   {
   public:
      using layout_value = layout_t;
      using treewidget_value = treewidget_t;
      //
   public:
      explicit groupbox_widget_impl(QWidget * owner, unicodestring const & caption) :
         groupbox{ caption, owner },
         layout_value{ this }
      {
         addWidget{ m_control = new treewidget_value{} };
      }
      ~groupbox_widget_impl() override = default;
      //
   public:
      treewidget_value * m_control{ nullptr };
   };
};