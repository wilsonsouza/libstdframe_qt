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
#include <std.mdichildwindow.hpp>
#include <std.mdiframewindowarea.hpp>
#include <std.application.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   mdiframewindowarea::mdiframewindowarea(QWidget * owner, unicodestring const & name) :
      QMdiArea{ owner },
      task_group{}
   {
      setObjectName(name);
      m_framewindow = static_cast<mdiframewindow *>(owner);
      setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
      setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
   #if(_DISABLED)
      QObject::connect(this, &QMdiArea::subWindowActivated, [=](QMdiSubWindow * pWnd)
      {
         QList<QMdiSubWindow *> pList = subWindowList();
         /**/
         if (pWnd != nullptr)
            reinterpret_cast<MDIChildWindow *>(pWnd)->
            OnActivate(reinterpret_cast<MDIChildWindow *>(pWnd));
         /**/
         if (pList.empty())
            return;
         /**/
         for (QList<QMdiSubWindow *>::Iterator n = pList.begin(); n != pList.end(); n++)
         {
            QMdiSubWindow * pSubWnd = n.operator*();

            if (pSubWnd != pWnd && pSubWnd != nullptr)
               reinterpret_cast<MDIChildWindow *>(pSubWnd)->
               OnDeactivate(reinterpret_cast<MDIChildWindow *>(pSubWnd));
         }
      });
   #endif
   }
   //-----------------------------------------------------------------------------------------------//
   void mdiframewindowarea::childEvent(QChildEvent * e)
   {
      if (e->child()->isWindowType())
      {
         auto wnd_ptr = dynamic_cast<mdichildwindow *>(e->child());
         //generate one event via pplx
         //call childwindow on_create method
         if (wnd_ptr != nullptr)
         {
            if (dispatch_event_by_pplx(this, wnd_ptr->on_notify, this, wnd_ptr, (void *)e->type(), (void *)e))
            {
               e->ignore();
            }
            else
            {
               e->accept();
            }
         }
      }
   }
   //-----------------------------------------------------------------------------------------------//
   bool mdiframewindowarea::event(QEvent * e)
   {
      auto value_id = e->type();
      /**/
      if (value_id == QEvent::WindowActivate)
      {
         auto wnd_ptr = this->get_active_mdichildwindow();
         /**/
         if (wnd_ptr != nullptr)
         {
            if (dispatch_event_by_pplx(this, wnd_ptr->on_activate, wnd_ptr))
            {
               e->accept();
            }
            else
            {
               e->ignore();
            }
         }
         return e->isAccepted();
      }
      else if (value_id == QEvent::WindowDeactivate)
      {
         auto wnd_ptr = this->get_active_mdichildwindow();
         /**/
         if (wnd_ptr != nullptr)
         {
            if (dispatch_event_by_pplx(this, wnd_ptr->on_deactivate, wnd_ptr))
            {
               e->accept();
            }
            else
            {
               e->ignore();
            }
         }
         return e->isAccepted();
      }
      else if (value_id == QEvent::WindowBlocked ||
               value_id == QEvent::WindowChangeInternal ||
               value_id == QEvent::WindowIconChange ||
               value_id == QEvent::WindowStateChange ||
               value_id == QEvent::WindowTitleChange ||
               value_id == QEvent::WindowUnblocked)
      {
         auto wnd_ptr = this->get_active_mdichildwindow();
         //
         if (wnd_ptr != nullptr)
         {
            if (dispatch_event_by_pplx(this, wnd_ptr->on_notify, this, wnd_ptr, (void *)&value_id, (void *)e))
            {
               e->accept();
            }
            else
            {
               e->ignore();
            }
            return e->isAccepted();
         }
      }
      return QMdiArea::event(e);
   }
   //-----------------------------------------------------------------------------------------------//
   QList<QMdiSubWindow *> mdiframewindowarea::get_list_mdichildwindow() const
   {
      return subWindowList();
   }
   //-----------------------------------------------------------------------------------------------//
   mdichildwindow * mdiframewindowarea::get_active_mdichildwindow() const
   {
      return static_cast<mdichildwindow *>(currentSubWindow());
   }
   //-----------------------------------------------------------------------------------------------//
   mdiframewindowarea * mdiframewindowarea::add_scrollbar(QWidget * scroll_bar, Qt::Alignment align)
   {
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   mdichildwindow * mdiframewindowarea::operator [](uint index)
   {
      auto sub_window_list = subWindowList();
      //
      if (index < uint(sub_window_list.count()))
      {
         return static_cast<mdichildwindow *>(sub_window_list.operator[](index));
      }
      return nullptr;
   }
   //-----------------------------------------------------------------------------------------------//
   mdichildwindow * mdiframewindowarea::operator [](unicodestring const & name)
   {
      auto queue = subWindowList();
      auto result = find_if(queue.cbegin(), queue.cend(), [=](QMdiSubWindow * child)
      {
         return(child->objectName().compare(name) == 0);
      });
      return static_cast<mdichildwindow *>(*result);
   }
   //-----------------------------------------------------------------------------------------------//
}