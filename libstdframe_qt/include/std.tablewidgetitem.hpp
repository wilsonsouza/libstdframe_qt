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
   //-----------------------------------------------------------------------------------------------//
   class Q_DECL_EXPORT tablewidgetitem : public QTableWidgetItem, public QObject
   {
   public:
      template<typename icon_t, typename text_t, typename type_t, typename name_t>
      tablewidgetitem(typename icon_t const && icon,
                      typename text_t const && text,
                      typename type_t const && type,
                      typename name_t const && name):
         QTableWidgetItem{ forward<typename icon_t>(icon), 
         forward<typename text_t>(text), forward<typename type_t>(type) }
      {
      }
   };
}