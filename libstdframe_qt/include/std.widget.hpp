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
#include <std.layouts.hpp>
#include <std.widget_impl.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT widget : public widget_impl < vertical_box >
   {
      Q_OBJECT
   public:
      explicit widget(QWidget * owner, unicodestring const & name, Qt::WindowFlags f = 0);
      ~widget() override = default;
      //
   protected:
      bool event(QEvent * e) override;
      /**/
   protected:
      menu * m_menu{ nullptr };
   };
}