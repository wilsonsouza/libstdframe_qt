//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//-----------------------------------------------------------------------------------------------//
#include <std.groupbox_buttons_control.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   groupbox_buttons_control::groupbox_buttons_control(unicodestring const & caption,
                                                      uint const & cols,
                                                      uint const & offset) :
      groupbox_impl<vertical_box>{ this, caption },
      m_cols{ cols },
      m_offset{ offset }
   {
   }
   //-----------------------------------------------------------------------------------------------//
   button * groupbox_buttons_control::get_button(uint const & button_id)
   {
      auto p = m_queue->find(button_id);
      return (p != m_queue->end() ? nullptr : p->second);
   }
   //-----------------------------------------------------------------------------------------------//
   groupbox_buttons_control * groupbox_buttons_control::create()
   {
      for (auto value = 0u; value < m_offset; ++value)
      {
         auto w = new widget_impl<vertical_box>{this, unicodestring{}, 0};
         //
         for (auto n = 0u; n < m_cols; ++n, ++value)
         {
            auto b = new button{ this, unicodestring{}.sprintf("%d", value), QIcon{} };
            auto f = b->font();
            //
            b->setFixedSize(m_button_size->x(), m_button_size->y());
            f.setPixelSize(m_font_size);
            f.setStyle(QFont::Style(m_font_style));
            w->box()->addWidget(b);
         }
         //
         w->box()->addWidget(w);
      }
      return this;
   }
}