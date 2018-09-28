//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//-----------------------------------------------------------------------------------------------//
#include <std.label.hpp>
#include <std.toolbutton.hpp>
#include <std.groupbox_impl.hpp>
#include <std.groupbox_top_button_control.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   groupbox_top_button_control::groupbox_top_button_control() :
      widget{ nullptr, unicodestring{}, 0 },
      m_caption{ new label{this, unicodestring{}} },
      m_topplus{ new toolbutton{this, m_iconlist->MINUS} }
   {
      m_group = new groupbox_impl<vertical_box>{ this, unicodestring{} };
   }
   //-----------------------------------------------------------------------------------------------//
   groupbox_top_button_control::groupbox_top_button_control(unicodestring const & caption,
                                                            unicodestring const & name) :
      widget{ nullptr, name, 0 },
      m_caption{ new label{this, unicodestring{}} },
      m_topplus{ new toolbutton{this, m_iconlist->MINUS} }
   {
      setWindowTitle(caption);
      m_group = new groupbox_impl<vertical_box>{ this, unicodestring{} };
   }
   //-----------------------------------------------------------------------------------------------//
   widget * groupbox_top_button_control::create()
   {
      auto top = new horizontal_box{ this, unicodestring{} };
      {
         m_topplus->setFixedSize(0x10, 0x10);
         m_topplus->setIcon(m_iconlist->PLUS);
         /**/
         if (m_topplus->isVisible())
         {
            m_topplus->setIcon(m_iconlist->MINUS);
         }
         /**/
         m_topplus->setEnabled(true);
         m_topplus->setIconSize(QSize(0xe, 0xe));

         top->addWidget([this]()->auto
         {
            m_topplus->on_clicked = [=](action * cmd, toolbutton * sender)
            {
               m_topplus->setIcon(m_iconlist->PLUS);
               m_topplus->setVisible(!m_group->isVisible());
               /**/
               if (m_topplus->isVisible())
               {
                  m_topplus->setIcon(m_iconlist->MINUS);
               }
               return true;
            };
            return m_topplus;
         }());
         /**/
         top->addWidget(m_caption);
      }
      //
      auto body = new vertical_box{ this, unicodestring{} };
      {
         body->addLayout(top);
         body->addWidget(m_group);
         //
         if (m_caption->text().length() == 0)
         {
            m_caption->setText(unicodestring{ "Opções de Pesquisa..." });
         }
         //
         box()->addLayout(body);
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   groupbox_impl<vertical_box> * groupbox_top_button_control::get_group()
   {
      return m_group;
   }
   //-----------------------------------------------------------------------------------------------//
   label * groupbox_top_button_control::get_caption()
   {
      return m_caption;
   }
   //-----------------------------------------------------------------------------------------------//
   toolbutton * groupbox_top_button_control::get_topplus()
   {
      return m_topplus;
   }
}