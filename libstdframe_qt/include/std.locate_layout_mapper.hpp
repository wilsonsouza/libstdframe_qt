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
#include <std.generate_container_mapper.hpp>
#include <std.search_internal_container_mapper.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   template <typename T = QLayout * >
   class locate_layout_mapper : public generate_container_mapper<T, map<unicodestring, widget *>>
   {
   public:
      using hash_value = map<unicodestring, widget *>;
      //
   public:
      explicit locate_layout_mapper(T type) :generate_container_mapper<T, HashT>{ type }
      {
      }
      ~locate_layout_mapper() override = default;
      template <class cast_t> cast_t* cast(QObject * obj_ptr)
      {
         return reinterpret_cast<cast_t *>(obj_ptr);
      }
      template <class find_t> find_t * find(unicodestring const & name)
      {
         return cast<find_t>(m_result->value(name));
      }
   };
   //-----------------------------------------------------------------------------------------------//
}
