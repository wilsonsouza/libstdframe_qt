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
//-----------------------------------------------------------------------------------------------//
namespace std
{
   template <class label_t = labelmodels<>, class queue_t = stringlist >
   class Q_DECL_EXPORT formatqueryfieldstoalias: public label_t
   {
   public:
      using queue_value = queue_t;
      using label_value = label_t;
      //
   public:
      explicit formatqueryfieldstoalias(queue_value const & lmmapper) : label_value{}
      {
         append(lmmapper.get_formatted_query_fields_to_alias());
      }
      virtual label_value const & get_result() const
      {
         return *this;
      }
   };
}
//-----------------------------------------------------------------------------------------------//
