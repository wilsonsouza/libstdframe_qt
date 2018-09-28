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
#include <std.layouts.hpp>
#include <std.treewidget.hpp>
#include <std.treewidgetitem.hpp>
#include <std.treeview.hpp>
//-----------------------------------------------------------------------------------------------//

namespace std
{
   //-----------------------------------------------------------------------------------------------//
   template <class T = treewidget, enable_if < is_class<T>{}, T >::type = 0>
   class Q_DECL_EXPORT tabbedwidget_impl: public tabbed
   {
   public:
      template<typename caption_t>
      explicit tabbedwidget_impl(caption_t const && caption) :tabbed{ nullptr }
      {
         setObjectName(forward<caption_t>(caption));
         addTab(m_control = new t{}, caption);
      }
      ~tabbedwidget_impl() override = default;
      //
   protected:
      T * m_control{ nullptr };
   };
}