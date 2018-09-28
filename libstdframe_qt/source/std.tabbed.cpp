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
#include <std.tabbed.hpp>
#include <std.tabbedindex.hpp>
#include <std.widget.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   tabbed::tabbed(QWidget * owner, unicodestring const & name) :QTabWidget{ owner }
   {
      m_tabbed_index = new tabbedindex{ this, 0 };
      setObjectName(name);
      /**/
      m_context_menu = shared_ptr<menu>{ new menu{this, captions::tabbed{}.NAME} };
      m_context_menu->create(&tabbedmenuitems{}, nullptr);
      m_context_menu->on_command = [this](action * cmd, menu * target)
      {
         auto name = target->objectName();
         auto tab = reinterpret_cast<tabbed *>(target->parent());
         //
         if (tab != nullptr)
         {
            if (name == captions::tabbed{}.POSITION_NORTH)
            {
               tab->setTabPosition(QTabWidget::North);
            }
            else if (name == captions::tabbed{}.POSITION_SOUTH)
            {
               tab->setTabPosition(QTabWidget::South);
            }
            else if (name == captions::tabbed{}.POSITION_EAST)
            {
               tab->setTabPosition(QTabWidget::East);
            }
            else if (name == captions::tabbed{}.POSITION_WEST)
            {
               tab->setTabPosition(QTabWidget::West);
            }
         }
         cmd->setChecked(!cmd->isChecked());
         return true;
      };
      /**/
      setTabsClosable(false);
      set_notify_everything();
   }
   //-----------------------------------------------------------------------------------------------//
   tabbed::~tabbed()
   {
      disconnect();
   }
   //-----------------------------------------------------------------------------------------------//
   int tabbed::get_count() const
   {
      return count();
   }
   //-----------------------------------------------------------------------------------------------//
   QWidget * tabbed::operator[](unicodestring const & name)
   {
      auto position = integral_find_if(0, count(), [&](int const & value)->auto
      {
         return(name.compare(widget(value)->objectName()));
      });
      return (position != count() ? widget(position) : nullptr);
   }
   //-----------------------------------------------------------------------------------------------//
   QWidget * tabbed::operator[](uint tab_index)
   {
      return widget(tab_index);
   }
   //-----------------------------------------------------------------------------------------------//
   tabbed * tabbed::set_tab_enabled(int const & index, bool const & enabled)
   {
      setTabEnabled(index, enabled);
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   tabbed * tabbed::set_tab_enabled(bool const & enabled)
   {
      for_each_integral(0, count(), [&](int const & value)
      {
         setTabEnabled(value, enabled);
      });
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   bool tabbed::is_tab_enabled(int const index) const
   {
      return isTabEnabled(index);
   }
   //-----------------------------------------------------------------------------------------------//
   list<bool> tabbed::is_tab_enabled() const
   {
      auto queue_out = list<bool>{};
      for_each_integral(0, count(), [&](int const & value)
      {
         queue_out.push_back(isTabEnabled(value));
      });
      return queue_out;
   }
   //-----------------------------------------------------------------------------------------------//
   tabbed * tabbed::set_tabicon(QWidget * owner, QIcon const & object_icon)
   {
      auto index = get_index(owner);
      static_exception(index == -1, unicodestring{ "invalid index" });
      static_exception(object_icon.isNull(), unicodestring{ "icon object is null!" });
      setTabIcon(index, object_icon);
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   tabbed * tabbed::set_current_index(QWidget * owner)
   {
      auto index = indexOf(owner);
      static_exception(index == -1, "invalid index!");
      setCurrentIndex(index);
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   tabbedindex * tabbed::update() const
   {
      return m_tabbed_index->update();
   }
   //-----------------------------------------------------------------------------------------------//
   void tabbed::mousePressEvent(QMouseEvent * mouse)
   {
      if (mouse->button() == Qt::RightButton)
      {
         dispatch_event(on_custom_context_menu_requested, this, mouse->pos());
         return;
      }
      QTabWidget::mousePressEvent(mouse);
   }
   //-----------------------------------------------------------------------------------------------//
   bool const tabbed::is_tab_enabled(tabbedindex * tabbed_index)
   {
      return isTabEnabled(tabbed_index->get_index());
   }
   //-----------------------------------------------------------------------------------------------//
   tabbedindex * tabbed::set_tab_enabled(tabbedindex * tabbed_index)
   {
      this->setTabEnabled(tabbed_index->get_index(), tabbed_index->is_enabled());
      return tabbed_index;
   }
   //-----------------------------------------------------------------------------------------------//
   int tabbed::get_index(QWidget * owner)
   {
      return indexOf(owner);
   }
   //-----------------------------------------------------------------------------------------------//
   bool tabbed::event(QEvent * event)
   {
      //for(int i; i < this->count(); ++i)
      //   setTabToolTip(i, std::unicodestring("Clique aqui para fechar..."));
      return QTabWidget::event(event);
   }
   //-----------------------------------------------------------------------------------------------//
   tabbed * tabbed::set_notify_everything()
   {
      connect(this, &QTabWidget::customContextMenuRequested, [=](QPoint const & point)
      {
         m_context_menu->execute(&point);
      });
      connect(this, &QTabWidget::currentChanged, [=](int index)
      {
         dispatch_event(on_current_changed, index, this);
      });
      connect(this, &QTabWidget::tabCloseRequested, [=](int index)
      {
         dispatch_event(on_tab_close_requested, index, this);
      });
      //
      auto tabbar = QTabWidget::tabBar();
      {
         connect(tabbar, &QTabBar::tabMoved, [=](int from, int to)
         {
            dispatch_event(on_tab_moved, from, to, this);
         });
      }
      return this;
   }
}
