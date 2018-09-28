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
#include <std.popup.hpp>
#include <std.mainwindow.hpp>
#include <std.action.hpp>
#include <std.mdiframewindow.hpp>
#include <std.mdiframewindowarea.hpp>
#include <std.menubar.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   menubar * menubar::create(popup const & owner, action * sender)
   {
      //for(auto && p: items)
      //{
      //   if(p->m_strName.contains(IDM_SEPARATOR))
      //      addSeparator();
      //   else
      //   {
      //      menu * ptr = new menu(nullptr, unicodestring(), p->m_strName);
      //      ptr->create(*p, Sender);
      //      addMenu(ptr);
      //   }
      //}
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   action * menubar::operator [](unicodestring menu_id)
   {
      return findChild<action *>(menu_id);
   }
   //-----------------------------------------------------------------------------------------------//
   menubar * menubar::set_enable(unicodestring const & menu_id, bool value_enabled)
   {
      auto value = (*this)[menu_id];
      /**/
      if (value != nullptr)
      {
         dispatch_event(on_update_ui, value, this, value_enabled);
         value->setEnabled(value_enabled);
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   bool menubar::get_enabled(unicodestring const & menu_id)
   {
      auto value = (*this)[menu_id];
      /**/
      if (value != nullptr)
      {
         return value->isEnabled();
      }
      return false;
   }
   //-----------------------------------------------------------------------------------------------//
   menubar * menubar::set_enabled_mdi_actions(mdiframewindow * frame)
   {
      auto items = shared_ptr<windowitems>{ new windowitems{} };
      /**/
      for(auto && value: *items)
      {
         if (!value->is_separator())
         {
            auto flags = frame->get_desktop()->get_list_mdichildwindow().empty();
            auto caption = value->get_caption();
            /**/
            if (caption.compare(captions::window{}.NEXT) == 0 ||
                caption.compare(captions::window{}.PREVIOUS) == 0 ||
                caption.compare(captions::window{}.CLOSEALL) == 0)
            {
               set_enable(caption, flags);
            }
            else
            {
               set_enable(caption, flags);
            }
         }
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   mainwindow * menubar::get_mainwindow() const
   {
      return reinterpret_cast<mainwindow *>(parent());
   }
   //-----------------------------------------------------------------------------------------------//
   void menubar::focusInEvent(QFocusEvent * e)
   {
      auto frame = dynamic_cast<mdiframewindow *>(parent());
      /**/
      if (frame != nullptr)
      {
         set_enabled_mdi_actions(frame);
      }
   }
   //-----------------------------------------------------------------------------------------------//
   menubar * menubar::set_notify_everything()
   {
      connect(this, &QMenuBar::hovered, [=](QAction * sender)
      {
         dispatch_event(on_hovered, reinterpret_cast<action *>(sender), this);
      });
      connect(this, &QMenuBar::triggered, [=](QAction * sender)
      {
         dispatch_event(on_command, reinterpret_cast<action *>(sender), this);
      });
      return this;
   }
}
