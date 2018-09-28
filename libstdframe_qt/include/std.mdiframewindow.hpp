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
#include <std.mainwindow.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   class Q_DECL_EXPORT mdichildwindow;
   class Q_DECL_EXPORT mdiframewindowarea;
   class Q_DECL_EXPORT timer;
   class Q_DECL_EXPORT application;
   class Q_DECL_EXPORT mdiframewindow : public mainwindow
   {
      //Q_OBJECT
   public:
      explicit mdiframewindow(QWidget * owner,
                              application * handle,
                              unicodestring const & name = unicodestring{},
                              Qt::WindowFlags wfflags = 0);
      ~mdiframewindow() override = default;
      virtual mdiframewindow * activate_next_childwindow();
      virtual mdiframewindow * activate_previous_childwindow();
      virtual mdiframewindow * cascade();
      virtual mdiframewindow * close_active_childwindow();
      virtual mdiframewindow * close_all_childwindows();
      virtual mdiframewindow * set_active_mdichildwindow(mdichildwindow * childwnd);
      virtual mdiframewindow * tile();
      virtual mdiframewindow * process_internal_mdichildwindow_commands(mainwindow * wnd,
                                                                        unicodestring const & did);
      virtual mdiframewindow * update_all_mdichildwindows();
      bool create(mainwindow * frame) override;
      /**/
   public:
      virtual bool const is_mdichildwindow_exists(unicodestring const & name);
      virtual mdiframewindow * set_enable_mdiactions(menuitems * items);
      /**/
   public:
      mdiframewindowarea * get_desktop();
      shared_ptr<timer> & get_timer();
      application * get_application();
      /**/
   public:
      function<bool const(mdiframewindow * sender)> on_create{ nullptr };
      function<bool const(action * sender, bool const & checked)> on_command{ nullptr };
      function<bool const(QObject * sender, ulong const & msg, void const * data)> on_notify{ nullptr };
      /**/
   protected:
      bool event(QEvent * e) override;
      void timerEvent(QTimerEvent * e) override;
      void closeEvent(QCloseEvent * e) override;
      bool const process_on_command_event(bool const & checked, action * ac) override;
      /**/
   protected:
      mdiframewindowarea * m_desktop{ nullptr };
      shared_ptr<timer> m_timer{ nullptr };
      application * m_application{ nullptr };
   };
}