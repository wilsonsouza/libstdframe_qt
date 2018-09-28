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
#include <std.groupbox.hpp>
#include <std.layouts.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   template <class Object/*,
      typename enable_if<is_same<typename Object, vertical_box>::value ||
      is_same<typename Object, horizontal_box>::value ||
      is_same<typename Object, formbox>::value ||
      is_same<typename Object, stacked_box>::value ||
      is_same<typename Object, gridbox>::value, Object>::type*/>
      class Q_DECL_EXPORT groupbox_impl : public groupbox
   {
   public:
      using object_type = typename Object;
      //
   public:
      groupbox_impl() :groupbox{}
      {
         m_value_type = new object_type{ nullptr, unicodestring{} };
      }
      explicit groupbox_impl(QWidget * owner, unicodestring const & name = unicodestring{}) :
         groupbox{ name, owner }
      {
         groupbox::setObjectName(name);
         m_value_type = new object_type{ this, name };
      }
      ~groupbox_impl() override = default;
      object_type * box()
      {
         return m_value_type;
      }
      //
   protected:
      object_type * m_value_type{ nullptr };
   };
}
//-----------------------------------------------------------------------------------------------//

