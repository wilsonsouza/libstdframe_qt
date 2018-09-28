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
   class Q_DECL_EXPORT progressbar : public QProgressBar
   {
      Q_OBJECT
   public:
      explicit progressbar(QWidget * owner, unicodestring const & name = unicodestring{});
      ~progressbar ( ) override = default;
      virtual progressbar * set_value ( int value );
      virtual progressbar * set_maximum ( int maximum );
      virtual progressbar * set_minimum ( int minimum );
      virtual progressbar * set_range ( int minimum, int maximum );
      /* event */
      enum
      {
         PSB_VALUE = 0xff,
         PSB_MAXIMUM,
         PSB_MINIMUM,
         PSB_RANGE
      };
      /**/
   public:
      function<bool const(int const & value, long const & msg, progressbar * sender, void * extra)> on_value_changed{ nullptr };
   };
}
//-----------------------------------------------------------------------------------------------//

