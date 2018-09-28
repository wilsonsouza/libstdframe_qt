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
#include <std.defs.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   template <int length_value_t = 0, int decimals_value_t = 0>
   struct tablefields
   {
      using pointer = shared_ptr<tablefields>;
      using length_value = length_value_t;
      using decimals_value = decimals_value_t;
      /**/
      unicodestring fieldname{};
      unicodestring fieldlabel{};
      unicodestring fieldalias{};
      unicodestring fieldmask{};
      int length{ length_value_t };
      int decimals{ decimals_value_t };
      /**/
      template<typename name_t, typename alias_t, typename label_t, typename mask_t>
      tablefields(name_t const && name, alias_t const && alias, label_t const && label, mask_t const && mask) :
         fieldname{ forward<name_t>(name) },
         fieldalias{ forward<alias_t>(alias) },
         fieldlabel{ forward<label_t>(label) },
         fieldmask{ forward<mask_t>(mask) }
      {
      }
   };
}
//-----------------------------------------------------------------------------------------------//


