//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.menuitemdata.hpp>
#include <std.submenuitemdata.hpp>
#include <std.menuitems.hpp>
#include <std.menu.hpp>
#include <std.action.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   menu::menu(QWidget * owner, unicodestring const & caption, unicodestring const & name) :
      QMenu{ caption, owner }
   {
      set_notify_everthing()->setObjectName(name);
   }
   //-----------------------------------------------------------------------------------------------//
   menu::~menu()
   {
      this->disconnect();
   }
   //-----------------------------------------------------------------------------------------------//
   action * __fastcall menu::operator [](unicodestring const & id)
   {
      return this->findChild<action *>(id);
   }
   //-----------------------------------------------------------------------------------------------//
   menuitems & menu::getitems()
   {
      return m_items;
   }
   //-----------------------------------------------------------------------------------------------//
   menu * menu::create(menuitems * items, action * sender)
   {
      for_each(items->begin(), items->end(), [=](menuitemdata * d)->auto
      {
         if (d->is_separator())
         {
            addSeparator();
         }
         else
         {
            auto cmd = new action(d->get_caption(), this);
            //
            if (!d->get_icon()->isNull())
            {
               cmd->setIcon(*d->get_icon());
            }
            //
            cmd->setText(d->get_caption());
            cmd->setEnabled(d->get_enabled());
            cmd->setChecked(d->get_checked());
            //
            if (!d->is_submenu())
            {
               addMenu(createsub(d->get_submenu_itemdata(), sender));
            }
            else
            {
               cmd->on_command = [=](bool const & checked, action * sender)
               {
                  return dispatch_event(on_command, cmd, this);
               };
               //Update Action
               d->set_actionitem(cmd);
               *items->finditem(d->get_caption()) = *d;
               dispatch_event(on_insert, cmd, this, d);
            }
         }
      });
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   action * menu::execute(QPoint const * point, action * sender)
   {
      return reinterpret_cast<action *>(this->exec());
   }
   //-----------------------------------------------------------------------------------------------//
   menu * menu::createsub(menulist_value * sub_items, action * sender)
   {
      auto p = new menu{ this, objectName() };
      //
      for_each(sub_items->begin(), sub_items->end(), [=](menuitemdata * d)
      {
         if (d->is_separator())
         {
            p->addSeparator();
         }
         else
         {
            auto cmd = new action{ d->get_caption(), this };
            //
            if (!d->get_icon()->isNull())
            {
               cmd->setIcon(*d->get_icon());
            }
            //
            cmd->setText(d->get_caption());
            cmd->setEnabled(d->get_enabled());
            cmd->setChecked(d->get_checked());
            //
            if (d->is_submenu())
            {
               p->addMenu(createsub(d->get_submenu_itemdata(), cmd));
            }
            else
            {
               cmd->on_command = [=](bool const & checked, action * sender)
               {
                  return dispatch_event(on_command, sender, this);
               };
               //
               d->set_actionitem(cmd);
               dispatch_event(on_insert, cmd, this, d);
            }
         }
      });
      return p;
   }
   //-----------------------------------------------------------------------------------------------//
   menu * menu::set_notify_everthing()
   {
      connect(this, &QMenu::aboutToHide, [=]()
      {
         dispatch_event(on_about_to_hide, this);
      });
      connect(this, &QMenu::aboutToShow, [=]()
      {
         dispatch_event(on_about_to_show, this);
      });
      connect(this, &QMenu::hovered, [=](QAction * sender)
      {
         dispatch_event(on_hovered, reinterpret_cast<action *>(sender), this);
      });
      connect(this, &QMenu::triggered, [=](QAction * sender)
      {
         dispatch_event(on_command, reinterpret_cast<action *>(sender), this);
      });
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
}
