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
#include <std.mdichildwindow.hpp>
#include <std.application.hpp>
#include <std.toolbar.hpp>
#include <std.timer.hpp>
#include <std.popup.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   mdiframewindow::mdiframewindow(QWidget * owner,
                                  application * handle,
                                  unicodestring const & name,
                                  Qt::WindowFlags wfflags) :
      mainwindow{ owner, name, wfflags },
      m_timer{ shared_ptr<timer>{ new timer{this, 0x400, name } } }
   {
      m_application_handle = handle;
      m_desktop = new mdiframewindowarea{ this };
      setCentralWidget(m_desktop);
      m_desktop->setViewMode(QMdiArea::ViewMode(m_settings->value(register_key{}.VIEWMODE,
                             m_desktop->viewMode()).toInt()));
   }
   //-----------------------------------------------------------------------------------------------//
   mdiframewindow * mdiframewindow::activate_next_childwindow()
   {
      m_desktop->activateNextSubWindow();
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   mdiframewindow * mdiframewindow::activate_previous_childwindow()
   {
      m_desktop->activatePreviousSubWindow();
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   mdiframewindow * mdiframewindow::cascade()
   {
      m_desktop->cascadeSubWindows();
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   mdiframewindow * mdiframewindow::close_active_childwindow()
   {
      m_desktop->closeActiveSubWindow();
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   mdiframewindow * mdiframewindow::close_all_childwindows()
   {
      m_desktop->closeAllSubWindows();
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   mdiframewindow * mdiframewindow::set_active_mdichildwindow(mdichildwindow * child)
   {
      m_desktop->setActiveSubWindow(dynamic_cast<QMdiSubWindow *>(child));
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   mdiframewindow * mdiframewindow::tile()
   {
      m_desktop->tileSubWindows();
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   bool const mdiframewindow::is_mdichildwindow_exists(unicodestring const & name)
   {
      auto p = m_desktop->operator [](name);
      return (p != nullptr);
   }
   //-----------------------------------------------------------------------------------------------//
   mdiframewindow * mdiframewindow::process_internal_mdichildwindow_commands(mainwindow * wnd,
                                                                             unicodestring const & name)
   {
      if (name.compare(captions::window{}.CASCADE))
      {
         this->cascade();
         return this;
      }
      /**/
      if (name.compare(captions::window{}.TILE))
      {
         this->tile();
         return this;
      }
      /**/
      if (name.compare(captions::window{}.CLOSE))
      {
         auto child = m_desktop->get_active_mdichildwindow();

         if (child != nullptr)
         {
            child->close();
            auto enabled = m_desktop->get_list_mdichildwindow().count() != 0;
            set_enable_menuitem(captions::file{}.CLOSE, enabled);
         }
         return this;
      }
      /**/
      if (name.compare(captions::window{}.CLOSEALL))
      {
         auto mutex = shared_ptr<QMutex>{ new QMutex() };
         auto locker = shared_ptr<QMutexLocker>{ new QMutexLocker(mutex.get()) };
         /**/
         close_all_childwindows();
         //refresh menu items
         set_enable_mdiactions(nullptr);
         /**/
         auto enabled = m_desktop->get_list_mdichildwindow().count() != 0;
         set_enable_menuitem(captions::file{}.CLOSE, enabled);
         return this;
      }
      /**/
      if (name.compare(captions::window{}.DOCUMENT))
      {
         auto isdoc = m_desktop->documentMode();
         auto doc = shared_ptr<popup>(*this)->operator[](name);
         /**/
         m_desktop->setDocumentMode(!isdoc);
         //repaint all windows
         update_all_mdichildwindows();

         if (doc != nullptr)
         {
            if (doc->get_actionitem() != nullptr)
            {
               doc->get_actionitem()->setChecked(!isdoc);
            }
         }
         return this;
      }
      /**/
      if (name.compare(captions::window{}.HIDE))
      {
         auto child = m_desktop->get_active_mdichildwindow();
         /**/
         if (child != nullptr)
         {
            child->show(window::mode{}.HIDE);
         }
         return this;
      }
      /**/
      if (name.compare(captions::window{}.SHOW) ||
          name.compare(captions::window{}.MAXIMIZE) ||
          name.compare(captions::window{}.REFRESH))
      {
         auto child = m_desktop->get_active_mdichildwindow();
         /**/
         if (child != nullptr)
         {
            child->show((name.compare(captions::window{}.MAXIMIZE) == 0 ? window::mode{}.MAXIMIZED : m_mode));
         }
         return this;
      }
      /**/
      if (name.compare(captions::window{}.MINIMIZE))
      {
         auto child = m_desktop->get_active_mdichildwindow();

         if (child != nullptr)
         {
            child->show(window::mode{}.MINIMIZED);
         }
         return this;
      }
      /**/
      if (name.compare(captions::window{}.NEXT))
      {
         this->activate_next_childwindow();
         return this;
      }
      /**/
      if (name.compare(captions::window{}.PREVIOUS))
      {
         this->activate_previous_childwindow();
         return this;
      }
      /**/
      if (name.compare(captions::window{}.TABBED))
      {
         auto vm = m_desktop->viewMode();
         auto tabdoc_vm = shared_ptr<popup>(*this)->operator[](name);
         //
         m_desktop->setViewMode(vm == QMdiArea::TabbedView ? QMdiArea::SubWindowView : QMdiArea::TabbedView);
         m_desktop->setTabsClosable(vm == QMdiArea::TabbedView);
         /**/
         if (tabdoc_vm != nullptr)
         {
            auto p = dynamic_cast<action *>(tabdoc_vm->get_actionitem());
            /**/
            if (p != nullptr)
            {
               p->setChecked(m_desktop->viewMode() == QMdiArea::TabbedView);
            }
         }
         /**/
         update_all_mdichildwindows();
         m_settings->setValue(register_key{}.VIEWMODE, m_desktop->viewMode());
         return this;
      }
      /**/
      if (name.compare(captions::style{}.PART))
      {
         this->set_change_style(name);
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   bool const mdiframewindow::process_on_command_event(bool const & checked, action * pac)
   {
      if (m_desktop != nullptr)
      {
         if (!m_desktop->get_list_mdichildwindow().empty())
         {
            process_internal_mdichildwindow_commands(this, pac->objectName());
         }
         else if (pac->text().compare(captions::style{}.PART) == 0)
         {
            set_change_style(pac->objectName());
            return true;
         }
      }
      /**/
      return dispatch_event_by_pplx(this, on_command, pac, checked);
   }
   //-----------------------------------------------------------------------------------------------//
   bool mdiframewindow::create(mainwindow * frame)
   {
      auto bar = statusBar();
      bool statusbar_visible = m_settings->value(register_key{}.STATUSBAR, true).toBool();
      auto toolbar_visible = m_settings->value(register_key{}.TOOLBAR, true).toBool();
      /**/
      bar->setVisible(statusbar_visible);
      /**/
      if (m_toolbar_handle != nullptr)
      {
         m_toolbar_handle->setVisible(toolbar_visible);
      }
      return true;
   }
   //-----------------------------------------------------------------------------------------------//
   mdiframewindow * mdiframewindow::update_all_mdichildwindows()
   {
      auto q = m_desktop->get_list_mdichildwindow();
      /**/
      for_each(q.begin(), q.end(), [&](QMdiSubWindow * p)
      {
         p->update();
      });
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   mdiframewindow * mdiframewindow::set_enable_mdiactions(menuitems * items)
   {
      auto locker = shared_ptr<QMutexLocker>{ new QMutexLocker{&QMutex{}} };
      auto p = get_popup()->find<menuitems>(captions::window{}.NAME);
      {
         /**/
         if (p == nullptr)
         {
            return this;
         }
         /**/
         if (p->empty())
         {
            return this;
         }
      }
      /**/
      for_each(p->begin(), p->end(), [&](menuitemdata * d)
      {
         if (!d->is_separator())
         {
            int offset = m_desktop->get_list_mdichildwindow().size();

            if (offset == 0 && d->is_action())
            {
               d->get_actionitem()->setEnabled(false);
            }
            /**/
            if (offset == 1 && d->is_action())
            {
               if (d->get_caption() != captions::window{}.NAME &&
                   d->get_caption() != captions::window{}.CLOSEALL &&
                   d->get_caption() != captions::window{}.NEXT &&
                   d->get_caption() != captions::window{}.PREVIOUS &&
                   d->get_caption() != captions::window{}.TILE)
               {
                  d->get_actionitem()->setEnabled(true);
               }
               else
               {
                  d->get_actionitem()->setEnabled(false);
               }
            }
            /**/
            if (offset > 1 && d->is_action() && d->get_caption() != captions::window{}.NAME)
            {
               d->get_actionitem()->setEnabled(true);
            }
         }
      });
      /**/
      auto close_item = operator[](captions::file{}.CLOSE);
      {
         static_exception(close_item == nullptr, "Menu item CLOSE not found!");
         close_item->setEnabled(m_desktop->get_list_mdichildwindow().count() != 0);
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   mdiframewindowarea * mdiframewindow::get_desktop()
   {
      return m_desktop;
   }
   //-----------------------------------------------------------------------------------------------//
   shared_ptr<timer> & mdiframewindow::get_timer()
   {
      return m_timer;
   }
   //-----------------------------------------------------------------------------------------------//
   application * mdiframewindow::get_application()
   {
      return m_application;
   }
   //-----------------------------------------------------------------------------------------------//
   bool mdiframewindow::event(QEvent * e)
   {
      auto id = e->type();

      if (id == QEvent::Polish)
      {
         function<bool(mdiframewindow *)> on_create = bind(&mdiframewindow::create, this, placeholders::_1);
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
         /* start timer */
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
         /**/
         if (dispatch_event_by_pplx(this, on_deactivate, this))
         {
            e->accept();
            m_timer->stop();
         }
         else
         {
            e->ignore();
         }
         /**/
         return e->isAccepted();
      }
      else if (id == QEvent::MouseButtonPress ||
               id == QEvent::MouseButtonRelease ||
               id == QEvent::MouseButtonDblClick ||
               id == QEvent::MouseMove ||
               id == QEvent::MouseMove)
      {
         if (dispatch_event_by_pplx(this, on_notify, this, WM_MOUSEACTIVATE, e))
         {
            e->accept();
         }
         else
         {
            e->ignore();
         }
         return e->isAccepted();
      }
      return QMainWindow::event(e);
   }
   //-----------------------------------------------------------------------------------------------//
   void mdiframewindow::closeEvent(QCloseEvent * e)
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
   void mdiframewindow::timerEvent(QTimerEvent * e)
   {
      static bool s_bCalled = false;
      /* run by pplx background task group */
      if (e->timerId() == m_timer->timerId() && !s_bCalled)
      {
         s_bCalled = !s_bCalled;
         /**/
         if (!dispatch_event_by_pplx(this, on_notify, this, WM_TIMER, m_timer.get()))
         {
            e->ignore();
         }
         else
         {
            e->accept();
         }
         /**/
         s_bCalled = !s_bCalled;
         return;
      }
      QMainWindow::timerEvent(e);
   }
   //-----------------------------------------------------------------------------------------------//
}
