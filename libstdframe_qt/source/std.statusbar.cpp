//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.defsx.hpp>
#include <std.statusbar.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   statusbar::statusbar(QWidget * owner, unicodestring const & name) :QStatusBar{ owner }
   {
      m_list_widget = shared_ptr<QList<QWidget *>>{ new QList<QWidget *>{} };
      setObjectName(name);
      connect(this, &QStatusBar::messageChanged, [=](unicodestring const & msg)
      {
         dispatch_event(on_message_changed, msg, this);
      });
   }
   //-----------------------------------------------------------------------------------------------//
   statusbar::~statusbar()
   {
      disconnect();
      /* remove all widget on statubar control */
      for_each(m_list_widget->cbegin(), m_list_widget->cend(), [=](QWidget * control)
      {
         remove(control);
      });
   }
   //-----------------------------------------------------------------------------------------------//
   statusbar * statusbar::add_permanent(QWidget * owner, int strecth_value)
   {
      this->m_list_widget->append(owner);
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   statusbar * statusbar::add(QWidget * owner, int strecth_value)
   {
      addWidget(owner, strecth_value);
      this->m_list_widget->append(owner);
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   statusbar * statusbar::remove(QWidget * owner)
   {
      removeWidget(owner);
      update();
      this->m_list_widget->removeOne(owner);
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   int statusbar::insert_permanent(int index, QWidget * owner, int strecth_value)
   {
      return insertPermanentWidget(index, owner, strecth_value);
   }
   //-----------------------------------------------------------------------------------------------//
   int statusbar::insert(int index, QWidget * owner, int strecth_value)
   {
      this->m_list_widget->append(owner);
      return insertWidget(index, owner, strecth_value);
   }
}