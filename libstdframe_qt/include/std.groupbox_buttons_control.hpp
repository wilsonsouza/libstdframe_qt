//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.widget_impl.hpp>
#include <std.groupbox_impl.hpp>
#include <std.button.hpp>
#include <std.icons.hpp>
#include <std.layouts.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT groupbox_buttons_control : public groupbox_impl<vertical_box>
   {
   public:
      using map_buttons = map<uint, button *>;
      //
   public:
      explicit groupbox_buttons_control(unicodestring const & caption,
                                        uint const & cols,
                                        uint const & offset);
      ~groupbox_buttons_control() override = default;
      button * get_button(uint const & buttond_id);
      virtual groupbox_buttons_control * create();
      /**/
   protected:
      uint m_cols{ 0 };
      uint m_offset{ 0 };
      shared_ptr<map_buttons> m_queue{ new map_buttons{} };
      uint m_font_size{ 0xc };
      uint m_font_style{ QFont::Bold };
      shared_ptr<QPoint> m_button_size{ new QPoint{0xc, 0xc} };
   };
}
//-----------------------------------------------------------------------------------------------//
