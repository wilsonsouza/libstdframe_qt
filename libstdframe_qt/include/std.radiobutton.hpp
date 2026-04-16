//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012, 2018, 2026
// For many platform
//
// 2WW Engenharia de Sistemas
// (c) 2012, 2026
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.defs.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT radiobutton : public QRadioButton
   {
      Q_OBJECT
   public:
      explicit radiobutton(QWidget * owner,
                           unicodestring const & caption,
                           unicodestring const & name,
                           bool const & enabled,
                           bool const & checked);
      ~radiobutton() override;
      //function event
   public:
      function<bool(bool const & clicked, radiobutton * sender)> on_clicked{ nullptr };
      function<bool(bool const & toggled, radiobutton * sender)> on_toggled{ nullptr };
      function<bool(bool const & pressed, radiobutton * sender)> on_pressed{ nullptr };
   };
}
