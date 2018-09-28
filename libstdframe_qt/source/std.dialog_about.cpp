//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//-----------------------------------------------------------------------------------------------//
#include <std.button.hpp>
#include <std.widget_impl.hpp>
#include <std.label.hpp>
#include <std.dialog_about.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   dialog_about::dialog_about(QWidget * owner, unicodestring const & caption) :
      dialog{ owner, 0, caption }
   {
   }
   //-----------------------------------------------------------------------------------------------//
   bool dialog_about::create(dialog * dlg)
   {
      auto app = static_cast<QGuiApplication *>(QCoreApplication::instance());
      auto queue = new widget_impl<vertical_box>{ this, unicodestring{} };
      auto app_name = app->applicationDisplayName();
      auto version = app->applicationVersion();
      auto name_copy = app->organizationName();
      auto domain = unicodestring{ "Created by Wilson Souza" };
      /**/
      dialog::create(this);
      m_ok->on_clicked = [this](bool const & checked, button * sender)->bool
      {
         return close();
      };
      //
      queue->box()->addWidget(new label{ this, app_name + " " + version }, 0, Qt::AlignCenter);
      queue->box()->addWidget(new label{ this, name_copy }, 0, Qt::AlignCenter);
      queue->box()->addWidget(new label{ this, domain }, 0, Qt::AlignCenter);
      queue->box()->addStretch();
      queue->box()->addStretch();
      queue->box()->addWidget(m_ok, 0, Qt::AlignCenter);
      setMaximumSize(domain.length() * 15, 250);
      m_ok->setEnabled(true);
      return true;
   }
}
//-----------------------------------------------------------------------------------------------//

