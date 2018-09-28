//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.defs.hpp>
#include <std.application.hpp>
#include <std.menu.hpp>
#include <std.mainwindow.hpp>
#include <std.dialog.hpp>
#include <std.toolbar.hpp>
#include <std.menubar.hpp>
#include <std.statusbar.hpp>
#include <std.captions.hpp>
#include <std.dialog_about.hpp>
#include <std.popup.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   mainwindow::mainwindow(QWidget * owner,
                          unicodestring const & name,
                          Qt::WindowFlags wfflags) : mainwindow_impl(owner, name, wfflags)
   {
      this->m_application_handle = static_cast<application *>(QCoreApplication::instance());
      this->setObjectName(name);
      /**/
      if (m_application_handle->organizationName().isEmpty())
      {
         m_application_handle->setOrganizationName(company_names{}.COMPANY);
      }
      /**/
      m_application_handle->setOrganizationDomain(company_names{}.COPYRIGHT);
      m_settings = shared_ptr<settings>
      {
         new settings{m_application_handle->organizationName(), m_application_handle->applicationName(), this}
      };
      m_styles = styles_mapper_pointer{ new styles_mapper{} };
      /**/
      m_styles->emplace(captions::style{}.FUSION, captions::styles{}.FUSION);
      m_styles->emplace(captions::style{}.WINDOWS, captions::styles{}.WINDOWS);
      m_styles->emplace(captions::style{}.XP, captions::styles{}.WINDOWSXP);
      m_styles->emplace(captions::style{}.MACINTOSH, captions::styles{}.MACINTOSH);
      /**/
      m_style_name = m_settings->value(register_key{}.STYLES, captions::styles{}.WINDOWS).toString();
      /**/
      this->set_change_style(m_style_name);
      //
      this->on_close = [&](QWidget * sender)->auto
      {
         return close();
      };
   }
   //-----------------------------------------------------------------------------------------------//
   mainwindow::~mainwindow()
   {
      disconnect();
      cancel();
   }
   //-----------------------------------------------------------------------------------------------//
   mainwindow * mainwindow::create_dock(unicodestring const & dock_name, dockwindow * dock)
   {
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   mainwindow * mainwindow::create_toolbar(toolbaritems * items, unicodestring const & name)
   {
      static_exception(items == nullptr, "Parameter toolbaritems::items can´t be null!");
      m_toolbar_handle = new toolbar{ objectName(), this, name };
      m_toolbar_handle->setObjectName(name.empty() ? objectName() : name);
      addToolBar(m_toolbar_handle->create(items));
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   mainwindow * mainwindow::create_toolbar(popup * handle)
   {
      static_exception(handle == nullptr, "Parameter popup::handle can´t be null!");
      static_exception(handle->empty(), "popup can´t be empty!");
      //
      auto items = new toolbaritems{ handle->objectName() };
      //
      for_each(handle->begin(), handle->end(), [&](menuitems * m)
      {
         std::for_each(m->begin(), m->end(), [&](menuitemdata * d)
         {
            if (!d->get_icon()->isNull())
            {
               items->operator+(d);
            }
         });
      });
      //Create ToolBar
      return (items->size() ? create_toolbar(items, items->get_caption()) : this);
   }
   //-----------------------------------------------------------------------------------------------//
   QMenu * __stdcall mainwindow::create_popup(menuitems * items, QMenuBar * root_ptr)
   {
      static_exception(items == nullptr, "Parameter menuitems::items can´t be null!");
      static_exception(root_ptr == nullptr, "Parameter QMenuBar::root_ptr can´t be null!");
      static_exception(items->empty(), "menuitems can´t be empty!");
      //
      auto * menu_ptr = new QMenu(items->get_caption(), root_ptr);
      menu_ptr->setObjectName(items->get_caption());
      /**/
      std::for_each(items->begin(), items->end(), [&](menuitemdata * d)
      {
         if (d->is_separator())
         {
            d->set_actionitem(static_cast<action *>(menu_ptr->addSeparator()));
         }
         else
         {
            if (d->is_submenu())
            {
               auto sub = create_subpopup(d);

               if (sub)
               {
                  menu_ptr->addMenu(sub);
               }
            }
            else
            {
               set_popup_action(d, menu_ptr);
            }
         }
      });
      /**/
      root_ptr->addMenu(menu_ptr);
      return menu_ptr;
   }
   //-----------------------------------------------------------------------------------------------//
   QMenu * __stdcall mainwindow::create_subpopup(menuitemdata * itemdata)
   {
      static_exception(itemdata == nullptr, "Parameter itemdata can´t be null!");
      static_exception(itemdata->get_submenu_itemdata()->empty(), "List of item is empty!");
      /**/
      auto menu{ new QMenu{itemdata->get_caption()} };
      auto subm = itemdata->get_submenu_itemdata();
      /**/
      for_each(subm->begin(), subm->end(), [&](menuitemdata * d)
      {
         if (d->is_separator())
         {
            d->set_actionitem(static_cast<action *>(menu->addSeparator()));
         }
         else
         {
            if (d->get_submenu_itemdata()->size())
            {
               auto sub = create_subpopup(d);
               /**/
               if (sub)
               {
                  menu->addMenu(sub);
               }
            }
            else
            {
               set_popup_action(d, menu);
            }
         }
      });
      return menu;
   }
   //-----------------------------------------------------------------------------------------------//
   mainwindow * mainwindow::set_popup_action(menuitemdata * itemdata, QMenu * menu)
   {
      static_exception(itemdata == nullptr, "Parameter menuitemsdata::itemdata can´t be null!");
      static_exception(menu == nullptr, "Parameter QMenu::menu can´t be null!");

      auto d = itemdata;
      {
         auto p = menu->addAction(d->get_caption());
         {
            d->set_actionitem(static_cast<action *>(p));
         }
         /**/
         if (!d->get_icon()->isNull())
         {
            d->get_actionitem()->setIcon(d->get_icon().operator*());
         }
         /**/
         d->get_actionitem()->setChecked(d->get_checked());
         d->get_actionitem()->setEnabled(d->get_enabled());
         d->get_actionitem()->setText(d->get_caption());
         d->get_actionitem()->setIconVisibleInMenu(true);
         /**/
         QObject::connect(p, &QAction::triggered, [=](bool checked)
         {
            //call by pplx
            if (!process_on_command_event(checked, reinterpret_cast<action *>(p)))
            {
               dispatch_event_by_pplx(this, on_command, checked, reinterpret_cast<action *>(p));
            }
         });
         /**/
         if (d->get_caption().compare(captions::help{}.ABOUT) == 0)
         {
            d->get_actionitem()->setText(d->get_caption().arg(m_application_handle->applicationName()));
            d->get_actionitem()->setIcon(m_application_handle->windowIcon());
            d->get_icon()->swap(d->get_actionitem()->icon());
            d->get_actionitem()->setEnabled(true);
            return this;
         }
         /**/
         if (d->get_caption().compare(captions::view{}.STATUSBAR) == 0 ||
             d->get_caption().compare(captions::view{}.TOOLBAR) == 0)
         {
            d->get_actionitem()->setEnabled(true);
            return this;
         }
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   mainwindow * mainwindow::create_menubar(popup * handle,
                                           action * action_ptr,
                                           unicodestring const & name)
   {
      static_exception(handle == nullptr, "Parameter popup::handle can´t be null!");
      static_exception(handle->empty(), "List of items is empty!");
      auto root = new QMenuBar{ menuBar() };
      /* call by pplx */
      std::for_each(handle->begin(), handle->end(), [&](menuitems * p)
      {
         create_popup(p, root);
      });
      /**/
      setMenuBar(root);
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   shared_ptr<popup> & mainwindow::get_popup()
   {
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   mainwindow * mainwindow::update()
   {
      /* run in background mode */
      show(m_mode);
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   mainwindow * mainwindow::show(uint const & mode)
   {
      m_mode = mode;
      /**/
      switch (mode)
      {
      case window::mode{}.FULLSCREEN:
         this->showFullScreen();
         break;
      case window::mode{}.HIDE:
         this->hide();
         break;
      case window::mode{}.MAXIMIZED:
         this->showMaximized();
         break;
      case window::mode{}.MINIMIZED:
         this->showMinimized();
         break;
      case window::mode{}.NORMAL:
         this->showNormal();
         break;
      default:
         static_exception(window::mode{} != mode, "Invalid command to window mode!");
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   bool const mainwindow::close()
   {
      m_settings->setValue(register_key{}.STYLES, m_style_name);
      /*cancel all task in pplx running*/
      if (QMainWindow::close())
      {
         cancel();
         m_terminated = true;
      }
      return m_terminated;
   }
   //-----------------------------------------------------------------------------------------------//
   mainwindow * mainwindow::set_change_style(unicodestring const & style)
   {
      /**/
      auto p = m_styles->find(style);
      /**/
      if (p != m_styles->end())
      {
         QApplication::setStyle(p->second);
         m_style_name = p->first;
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   mainwindow * mainwindow::update_process()
   {
      static_cast<QGuiApplication *>(QCoreApplication::instance())->processEvents();
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   template <typename widget_t> widget_t * mainwindow::find_childwindow(unicodestring const & name)
   {
      auto * wnd = reinterpret_cast<widget_t *>(findChild<QWidget *>(name));
      return (wnd != nullptr ? wnd : nullptr);
   }
   //-----------------------------------------------------------------------------------------------//
   mainwindow * mainwindow::set_enable_menuitem(unicodestring const & name, bool const & enabled)
   {
      if (get_popup()->size())
      {
         auto p = get_popup()->finditem(name);
         //
         if (p)
         {
            p->get_actionitem()->setEnabled(enabled);
            dispatch_event_by_pplx(this, on_update_ui, this, p, enabled);
         }
      }
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   mainwindow * mainwindow::set_enable_menuitem(stringlist const & lnames, bool const & enabled)
   {
      for_each(lnames.begin(), lnames.end(), [&](unicodestring const & value)
      {
         set_enable_menuitem(value, enabled);
      });
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   bool const mainwindow::is_menuitem_enabled(unicodestring const & name) const
   {
      auto d = shared_ptr<popup>(*this)->operator[](name);
      static_exception(d == nullptr, unicodestring{ "MenuItem [%1] not found!" }.bind(name));
      return(d ? d->get_actionitem()->isEnabled() : false);
   }
   //-----------------------------------------------------------------------------------------------//
   action * mainwindow::operator[](unicodestring const & name) const
   {
      auto d = shared_ptr<popup>(*this)->operator[](name);
      static_exception(d == nullptr, unicodestring{ "MenuItem [%1] not found!" }.bind(name));
      return(d ? d->get_actionitem() : nullptr);
   }
   //-----------------------------------------------------------------------------------------------//
   mainwindow * mainwindow::dispatch_eventlooper(bool const & all)
   {
      auto app = static_cast<QGuiApplication *>(QCoreApplication::instance());
      app->processEvents(all ? QEventLoop::AllEvents : QEventLoop::ExcludeUserInputEvents);
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   bool mainwindow::event(QEvent * e)
   {
      auto n = e->type();
      /**/
      if (n == QEvent::WindowIconChange)
      {
         auto s = iconSize();
         /**/
         if (dispatch_event_by_pplx(this, on_notify, this, long{ WM_ICONSIZECHANGED }, addressof(s)))
         {
            e->accept();
         }
         else
         {
            e->ignore();
         }
         return e->isAccepted();
      }
      else if (n == QEvent::Polish)
      {
         function<bool(mainwindow *)> on_create = bind(&mainwindow::create, this, placeholders::_1);
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
      else if (n == QEvent::ApplicationWindowIconChange)
      {
         auto icon = static_cast<QGuiApplication *>(QCoreApplication::instance())->windowIcon();
         /**/
         if (dispatch_event_by_pplx(this, on_notify, this, WM_GETICON, addressof(icon)))
         {
            e->accept();
         }
         else
         {
            e->ignore();
         }
         return e->isAccepted();
      }
      else if (n == QEvent::Close)
      {
         if (dispatch_event_by_pplx(this, on_close, this))
         {
            e->accept();
         }
         else
         {
            e->ignore();
         }
         return e->isAccepted();
      }
      else if (n == QEvent::Show)
      {
         if (dispatch_event_by_pplx(this, on_show, this, m_mode))
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
   bool const mainwindow::process_on_command_event(bool const & checked, action * ac)
   {
      /**/
      if (ac->text().compare(captions::view{}.STATUSBAR) == 0)
      {
         auto s = statusBar();
         bool visible = s->isVisible();
         /**/
         s->setVisible(!visible);
         ac->setChecked(!visible);
         m_settings->setValue(register_key{}.STATUSBAR, !visible);
         return true;
      }
      /**/
      if (ac->text().compare(captions::view{}.TOOLBAR) == 0)
      {
         if (m_toolbar_handle != nullptr)
         {
            bool visible = m_toolbar_handle->isVisible();
            /**/
            m_toolbar_handle->setVisible(!visible);
            ac->setChecked(!visible);
            m_settings->setValue(register_key{}.TOOLBAR, !visible);
         }
         return true;
      }
      /**/
      if (ac->text().compare(captions::help{}.ABOUT) == 0)
      {
         /* new c++ supported */
         dialog_about::pointer
         {
            new dialog_about
            {
               this,
               static_cast<QGuiApplication *>(QCoreApplication::instance())->applicationDisplayName()
            }
         }->do_modal();
         return true;
      }
      /**/
      return false;
   }
   //-----------------------------------------------------------------------------------------------//
   action * mainwindow::find_menuitem(unicodestring const & name) const
   {
      auto d = mainwindow::operator[](name);
      static_exception(d == nullptr, unicodestring{ "MenuItem [%1] not found!" }.bind(name));
      return(d);
   }
   //-----------------------------------------------------------------------------------------------//
}