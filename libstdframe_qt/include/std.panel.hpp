//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2015, 2018
//
// Dedalus Prime
// (c) 2015
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.widget.hpp>
#include <std.layouts.hpp>

namespace std
{
   class Q_DECL_EXPORT panel : public widget
   {
   public:
      panel(QWidget * owner, unicodestring const & name) : widget{ owner, name }
      {
      }
      ~panel() override = default;
      //
   public:
      function<bool(widget * sender, QEvent * event_ptr, void * data_ptr)> on_notify{ nullptr };
   };
}
