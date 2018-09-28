//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.mdiframewindow.hpp>
#include <std.mdiframewindowarea.hpp>
#include <std.menubar.hpp>
#include <std.mdichildwindow.hpp>
#include <std.mdichildwindow_impl.hpp>
#include <std.widget_impl.hpp>
#include <std.timer.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   mdichildwindow::mdichildwindow(QWidget * owner, unicodestring const & name, Qt::WindowFlags wfflags) :
      mdichildwindow_impl{ owner, name, wfflags }
   {
      setWindowIcon(m_iconlist->MYDOCUMENTS);
      /**/
      m_verticalbox = new widget_impl<vertical_box>{ this, "vertical_box", 0 };
      m_horizontalbox = new widget_impl<horizontal_box>{ this, "horizontal_box", 0 };
      m_formbox = new widget_impl<formbox>{ this, "formbox", 0 };
      m_gridbox = new widget_impl<gridbox>{ this, "groupbox", 0 };
      /**/
      setAttribute(Qt::WA_DeleteOnClose);
      /**/
      m_framewindow = reinterpret_cast<mdiframewindow *>(parent());
      /**/
      if (m_framewindow != nullptr)
      {
         if (m_framewindow->get_desktop() != nullptr)
         {
            m_framewindow->get_desktop()->addSubWindow(this);
         }
      }
      /**/
      m_timer = shared_ptr < timer >{ new timer{this, 0x64, objectName()} };
   }
   //-----------------------------------------------------------------------------------------------//
   mdichildwindow::~mdichildwindow()
   {
      disconnect();
      cancel();
   }
   //-----------------------------------------------------------------------------------------------//
   mdichildwindow * mdichildwindow::update()
   {
      show(m_mode);
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   bool mdichildwindow::close()
   {
      /* emit close window */
      if (QMdiSubWindow::close())
      {
         cancel();
         m_terminated = true;
      }
      return m_terminated;
   }
   //-----------------------------------------------------------------------------------------------//
   mdichildwindow * mdichildwindow::show(uint mode)
   {
      /* when call functions of display mode it´s lock system*/
      m_mode = mode;
      /**/
      switch (m_mode)
      {
      case window::mode{}.FULLSCREEN:
         showFullScreen();
         break;
      case window::mode{}.HIDE:
         hide();
         break;
      case window::mode{}.MAXIMIZED:
         showMaximized();
         break;
      case window::mode{}.MINIMIZED:
         showMinimized();
         break;
      case window::mode{}.NORMAL:
         showNormal();
         break;
      default:
         static_exception(window::mode{} != mode, "Invalid command to window mode!");
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   bool mdichildwindow::event(QEvent * e)
   {
      auto id = e->type();
      /**/
      if (id == QEvent::Polish)
      {
         function<bool(mdichildwindow *)> on_create = bind(&mdichildwindow::create, this, placeholders::_1);
         if (dispatch_event_by_pplx(this, on_create, this))
         {
            e->accept();
         }
         else
         {
            e->ignore();
         }
         return e->isAccepted();
      }
      else if (id == QEvent::WindowActivate)
      {
         if (dispatch_event_by_pplx(this, on_activate, this))
         {
            e->accept();
            m_timer->start();
         }
         else
         {
            e->ignore();
         }
         return e->isAccepted();
      }
      else if (id == QEvent::WindowDeactivate)
      {
         if (dispatch_event_by_pplx(this, on_deactivate, this))
         {
            e->accept();
            m_timer->stop();
         }
         else
         {
            e->ignore();
         }
         return e->isAccepted();
      }
      return QMdiSubWindow::event(e);
   }
   //-----------------------------------------------------------------------------------------------//
   void mdichildwindow::closeEvent(QCloseEvent * e)
   {
      if (!dispatch_event_by_pplx(this, on_close, this))
      {
         e->ignore();
      }
      else
      {
         e->accept();
         m_timer->stop();
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void mdichildwindow::timerEvent(QTimerEvent * e)
   {
      if (dispatch_event_by_pplx(this, on_notify, this, this, (void *)WM_TIMECHANGE, e))
      {
         e->accept();
      }
      else
      {
         e->ignore();
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void mdichildwindow::contextMenuEvent(QContextMenuEvent * e)
   {
      if (dispatch_event_by_pplx(this, on_context_menu_requested, this, e->pos()))
      {
         e->accept();
      }
      else
      {
         e->ignore();
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void mdichildwindow::showEvent(QShowEvent * e)
   {
      if (dispatch_event_by_pplx(this, on_show, this, m_mode))
      {
         e->accept();
      }
      else
      {
         e->ignore();
      }
   }
   //-----------------------------------------------------------------------------------------------//
   mdichildwindow * mdichildwindow::set_widget(QWidget * owner)
   {
      setWidget(owner);
      show();
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   shared_ptr<sql::query> & mdichildwindow::get_sqlhandle() const
   {
      return m_framewindow->get_singlequery_language_handle();
   }
   //-----------------------------------------------------------------------------------------------//
}