//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.application.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   application * g_application = nullptr;
   //-----------------------------------------------------------------------------------------------//
   application::application(int & argc, char ** aargv) :QApplication{ argc, aargv }
   {
      g_application = this;
      m_framewindow = nullptr;
      m_terminated = false;
      m_locale = std::shared_ptr<QLocale>{ new QLocale{ QLocale::Portuguese, QLocale::Brazil } };
      /**/
      connect(this, &QGuiApplication::lastWindowClosed, [=]()
      {
         dispatch_event_by_pplx(this, on_lastwindowclosed, this);
      });
      connect(this, &QGuiApplication::focusWindowChanged, [=](QWindow * wnd)
      {
         dispatch_event_by_pplx(this, on_focuswindowchanged, wnd, this);
      });
      /**/
      QLocale::setDefault(m_locale.operator*());
   }
   //-----------------------------------------------------------------------------------------------//
   application::~application()
   {
      this->disconnect();
      this->cancel();
   }
   //-----------------------------------------------------------------------------------------------//
   application * application::terminate()
   {
      if (m_framewindow)
      {
         if (m_framewindow->close())
         {
            cancel();
            m_terminated = true;
         }
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   int  application::execute()
   {
      if (m_framewindow != nullptr)
      {
         m_framewindow->show();
      }
      return exec();
   }
   //-----------------------------------------------------------------------------------------------//
   application  *  application::get_mainapp()
   {
      return g_application;
   }
   //-----------------------------------------------------------------------------------------------//
   mainwindow  *  application::get_mainwindow()
   {
      return g_application->m_framewindow;
   }
   //-----------------------------------------------------------------------------------------------//
   bool application::event(QEvent * e)
   {
      auto value_id = e->type();
      //
      return QApplication::event(e);
   }
   //-----------------------------------------------------------------------------------------------//
}