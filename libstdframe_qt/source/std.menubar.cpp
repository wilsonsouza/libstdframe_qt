//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012, 2018, 2026
// For many platform
//
// 2WW Engenharia de Sistemas
// (c) 2012, 2026
//-----------------------------------------------------------------------------------------------//
#include <std.defsx.hpp>
#include <std.popup.hpp>
#include <std.mainwindow.hpp>
#include <std.action.hpp>
#include <std.mdiframewindow.hpp>
#include <std.mdiframewindowarea.hpp>
#include <std.bar.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std::menu
{
   bar::bar(QWidget* owner, unicodestring const& name) :Qbar{ owner }
   {
      set_notify_everything()->setObjectName(name);
   }
   //-----------------------------------------------------------------------------------------------//
   bar::~bar() override
   {
      disconnect();
   }
   //-----------------------------------------------------------------------------------------------//
   bar* bar::create(popup const& owner, action* sender)
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
   action* bar::operator [](unicodestring menu_id)
   {
      return findChild<action*>(menu_id);
   }
   //-----------------------------------------------------------------------------------------------//
   bar* bar::set_enable(unicodestring const& menu_id, bool value_enabled)
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
   bool bar::get_enabled(unicodestring const& menu_id)
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
   bar* bar::set_enabled_mdi_actions(mdiframewindow* frame)
   {
      auto items = unique_ptr<windowitems>{ new windowitems{} };
      /**/
      for (auto&& value : *items)
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
   mainwindow* bar::get_mainwindow() const
   {
      return reinterpret_cast<mainwindow*>(parent());
   }
   //-----------------------------------------------------------------------------------------------//
   void bar::focusInEvent(QFocusEvent* e)
   {
      if (auto frame = dynamic_cast<mdiframewindow*>(parent()); frame != nullptr)
      {
         set_enabled_mdi_actions(frame);
      }
   }
   //-----------------------------------------------------------------------------------------------//
   bar* bar::set_notify_everything()
   {
      connect(this, &Qbar::hovered, [=](QAction* sender)
      {
         dispatch_event(on_hovered, reinterpret_cast<action*>(sender), this);
      });
      connect(this, &Qbar::triggered, [=](QAction* sender)
      {
         dispatch_event(on_command, reinterpret_cast<action*>(sender), this);
      });
      return this;
   }
}
