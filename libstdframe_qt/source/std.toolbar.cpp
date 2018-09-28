//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.menu.hpp>
#include <std.menuitemdata.hpp>
#include <std.menuitems.hpp>
#include <std.toolbar.hpp>
#include <std.toolbaritems.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   toolbar::toolbar(unicodestring const & caption, QWidget * owner, unicodestring const & name) :
      qtoolbar{ caption, owner }
   {
      setObjectName(name);
   }
   //-----------------------------------------------------------------------------------------------//
   toolbar * toolbar::create(toolbaritems * items)
   {
      for_each(items->cbegin(), items->cend(), [&](menuitemdata * d)
      {
         if (d->is_separator())
         {
            addSeparator();
         }
         else
         {
            if (d->is_action())
            {
               addAction(d->get_actionitem());
            }
         }
      });
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   toolbar * toolbar::set_enabled(unicodestring const & buttonname, bool const enabled)
   {
      auto p = QObject::findChild<action *>(buttonname);
      /**/
      if (p != nullptr)
      {
         p->setEnabled(enabled);
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   bool const toolbar::is_enabled(unicodestring const & buttonname)
   {
      auto * p = QObject::findChild<action *>(buttonname);
      /**/
      if (p != nullptr)
      {
         return p->isEnabled();
      }
      return false;
   }
   //-----------------------------------------------------------------------------------------------//
   toolbar * toolbar::set_notify_everthing()
   {
      connect(this, &qtoolbar::actionTriggered, [=](QAction * sender)
      {
         dispatch_event(on_command, reinterpret_cast<action *>(sender), this);
      });
      connect(this, &qtoolbar::allowedAreasChanged, [=](Qt::ToolBarAreas tbaflags)
      {
         dispatch_event(on_allowedareaschanged, tbaflags, this);
      });
      connect(this, &qtoolbar::iconSizeChanged, [=](QSize const & icon)
      {
         dispatch_event(on_iconsizechanged, icon, this);
      });
      connect(this, &qtoolbar::movableChanged, [=](bool movable)
      {
         dispatch_event(on_movablechanged, movable, this);
      });
      connect(this, &QToolBar::orientationChanged, [=](Qt::Orientation oMode)
      {
         dispatch_event(on_orientationchanged, oMode, this);
      });
      connect(this, &qtoolbar::toolButtonStyleChanged, [=](Qt::ToolButtonStyle mode)
      {
         dispatch_event(on_toolbuttonstylechanged, mode, this);
      });
      connect(this, &qtoolbar::topLevelChanged, [=](bool toplevel)
      {
         dispatch_event(on_toplevelchanged, toplevel, this);
      });
      connect(this, &qtoolbar::visibilityChanged, [=](bool visible)
      {
         dispatch_event(on_visibilitychanged, visible, this);
      });
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
}