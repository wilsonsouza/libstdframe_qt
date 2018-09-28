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
#include <std.defs.hpp>
#include <std.menu.hpp>
#include <std.mainwindow.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   class Q_DECL_EXPORT application : public QApplication, public task_group
   {
      Q_OBJECT
   public:
      application(int & argc, char ** argv);
   #if(_DISABLED)
      Application(int & nargc, char ** lppargv, bool bguienabled);
      Application(int & nargc, char ** lppargv, QApplication::Type type);
      Application(display * lpdisplay, qt::handle hvisual = 0, qt::handle hcolormap = 0);
      Application(display * lpdisplay, int & nargc, char ** lppargv, qt::handle hvisual = 0, qt::handle hcolormap = 0);
      Application(QApplication::qs60mainApplicationfactory factory, int & nargc, char ** lppargv);
   #endif
      ~application() override;
      //overwrite
      virtual application * terminate();
      virtual int execute();
      virtual application * processevents(QEventLoop::ProcessEventsFlags flags = QEventLoop::AllEvents)
      {
         QCoreApplication::processEvents(flags);
         return this;
      }
      //static
      static application * get_mainapp();
      static mainwindow  * get_mainwindow();
      /**/
   public:
      function<bool(application *)> on_lastwindowclosed{ nullptr };
      function<bool(QWindow *, application *)> on_focuswindowchanged{ nullptr };
      /**/
   protected:
      bool event(QEvent * e) override;
      //
   protected:
      bool m_terminated{ false };
      mainwindow * m_framewindow{ nullptr };
      unicodestring m_appname{};
      unicodestring m_title{};
      unicodestring m_version{};
      unicodestring m_credit{};
      unicodestring m_owner{};
      unicodestring m_copyright{};
      shared_ptr<QLocale> m_locale{ nullptr };
   };
   //-----------------------------------------------------------------------------------------------//
};