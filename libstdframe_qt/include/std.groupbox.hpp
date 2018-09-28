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
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT groupbox: public QGroupBox
   {
      Q_OBJECT
   public:
      groupbox();
      explicit groupbox(unicodestring const & caption, QWidget * owner = nullptr);
      ~groupbox() override;
      //
   public:
      function<bool(bool const & checked, groupbox * sender)> on_clicked{ nullptr };
      function<bool(bool const & enabled, groupbox * sender)> on_toggled{ nullptr };
      //
   protected:
      groupbox * set_notify_everything();
   };
};
//-----------------------------------------------------------------------------------------------//

