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
#include <std.defs.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT menu;
   class Q_DECL_EXPORT widget;
   //-----------------------------------------------------------------------------------------------//
   template<class Object>
   class Q_DECL_EXPORT widget_impl : virtual public QWidget
   {
   public:
      using value_type = typename Object;
      using value_type_pointer = typename Object *;
      //
   public:
      explicit widget_impl(QWidget * owner, unicodestring const & name, Qt::WindowFlags flags = 0) :
         QWidget{ owner, flags }
      {
         setObjectName(name + "_QWidget");
         m_value_type->setObjectName(name + "_QWidget_QLayout");
         setLayout(m_value_type);
      }
      ~widget_impl() override
      {
         QObject::disconnect();
      }
      virtual QWidget * create()
      {
         return this;
      }
      operator QWidget *() const
      {
         return this;
      }
      value_type_pointer box()
      {
         return m_value_type;
      }
      /**/
   public:
      function<bool(QPoint const & pt, widget_impl<value_type> * sender)> on_context_menu_requested{ nullptr };
      //
   protected:
      value_type_pointer m_value_type{ new value_type{} };
   };
}