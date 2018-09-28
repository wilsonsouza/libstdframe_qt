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

#include <std.labelmodels.hpp>

namespace std
{
   template <typename T = labelmodels<>, typename H = T::hash_value >
   class labelmodels_to_hashmapper : public H
   {
   public:
      using labelmodels_value = T;
      using hashstring_value = H;
      /**/
   public:
      labelmodels_to_hashmapper() = default;
      explicit labelmodels_to_hashmapper(labelmodels_value const & t_mapper) :hashstring_value{}
      {
         append(t_mapper.get_list_to_string_hash_mapper());
      }
      hashstring_value const & get_result() const
      {
         return *this;
      }
   };
}