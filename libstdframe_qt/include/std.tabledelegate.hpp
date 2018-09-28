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
#include <std.action.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT tabledelegate : public action
   {
      Q_OBJECT
   public:
      explicit tabledelegate(QWidget * owner) :action{ owner }
      {
      }
      ~tabledelegate() override = default;
      //
   public:
      function<bool(bool const & checked, action * sender)> on_command{ nullptr };
   };
}