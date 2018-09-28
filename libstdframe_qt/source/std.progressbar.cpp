//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2017, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <std.progressbar.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   progressbar::progressbar(QWidget * owner, unicodestring const & name) :QProgressBar{ owner }
   {
      setObjectName(name);
   }
   //-----------------------------------------------------------------------------------------------//
   progressbar * progressbar::set_value(int value)
   {
      if (dispatch_event(on_value_changed, value, PSB_VALUE, this, nullptr))
      {
         QProgressBar::setValue(value);
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   progressbar * progressbar::set_maximum(int maximum)
   {
      if (dispatch_event(on_value_changed, maximum, PSB_MAXIMUM, this, nullptr))
      {
         QProgressBar::setMaximum(maximum);
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   progressbar * progressbar::set_minimum(int minimum)
   {
      if (dispatch_event(on_value_changed, minimum, PSB_MINIMUM, this, nullptr))
      {
         QProgressBar::setMinimum(minimum);
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   progressbar * progressbar::set_range(int minimum, int maximum)
   {
      if (dispatch_event(on_value_changed, minimum, PSB_RANGE, this, &maximum))
      {
         QProgressBar::setRange(minimum, maximum);
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
}