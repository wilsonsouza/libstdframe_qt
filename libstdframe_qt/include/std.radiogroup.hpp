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
#include <std.radiobutton.hpp>
#include <std.layouts.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class radiogroup : public vertical_box, virtual public map<unicodestring, radiobutton *>
   {
      Q_OBJECT
   public:
      using hash_value_type = map<unicodestring, radiobutton *>;
      using list_value_type = list<radiobutton *>;
      //
   public:
      radiogroup() = default;
      ~radiogroup() override = default;
      virtual radiogroup * add(stringlist const & items);
      virtual radiogroup * set_enabled(unicodestring const & name,
                                       bool const & enabled,
                                       bool const & all = false);
      virtual bool get_enabled(unicodestring const & name);
      virtual radiobutton * get_byname(unicodestring const & name) const;
      virtual radiogroup::list_value_type const get_object_list() const;
      virtual radiogroup::hash_value_type const & get_object_mapper();
      /**/
   public:
      function<bool(bool const & checked, radiobutton * sender)> on_clicked{ nullptr };
   };
}