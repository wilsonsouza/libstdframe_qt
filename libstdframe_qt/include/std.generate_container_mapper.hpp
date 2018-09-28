//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.widget.hpp>

namespace std
{
   //-----------------------------------------------------------------------------------------------//
   template <class widget_t = QWidget * , class map_t = map<unicodestring, widget *>,
      enable_if<is_same<widget_t, QWidget>::value>::type = 0>
      class Q_DECL_EXPORT generate_container_mapper : public map_t, public widget_t
   {
   public:
      using map_value = mapt_t;
      using widget_value = widget_t;
      //
   public:
      template <typename widget_t>
      generate_container_mapper(widget_value *& widget_param) :
         widget_value{ forward<widget_value>(widget_param) }
      {
         do_mapper();
      }
      generate_container_mapper(shared_ptr<generatecontainermapp<widget_value, map_value>> const & value):
         widget_value{value.operator->()}
      {
         append(value.operator*());
      }
      virtual ~generate_container_mapper() = default;
      generate_container_mapper<widget_value, map_value> * do_mapper()
      {
         auto queue = findChildren<widget_value *>();
         //
         for_each(queue.cbegin(), queue.cend(), [&](QWidget * value)
         {
            if (value != nullptr)
            {
               insert(value->objectName(), value);
            }
         });
         return this;
      }
   };
}