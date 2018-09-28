//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012
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
#include <std.searchinternalcontainermapper.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT locate_control_mapper :
      public generate_container_mapper<QWidget *, map<unicodestring, widget *>>
   {
   public:
      using hash_value = map<unicodestring, widget *>;
      //
   public:
      explicit locate_control_mapper(QWidget * control) :
         generate_container_mapper<QWidget *, hash_value>{ control }
      {
      }
      ~locate_control_mapper() override = default;
      template<typename T> T * search(unicodestring const & name)
      {
         return reinterpret_cast<T *>(m_mapper->value(name));
      }
   };
}
//-----------------------------------------------------------------------------------------------//
