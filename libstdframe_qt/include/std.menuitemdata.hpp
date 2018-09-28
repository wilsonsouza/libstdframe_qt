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
#include <std.captions.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT action;
   class Q_DECL_EXPORT submenuitemdata;
   class Q_DECL_EXPORT menuitemdata : public QObject
   {
   public:
      using pointer = shared_ptr<menuitemdata>;
      /**/
      template<typename Name, class Icon = QIcon, typename Enabled = bool, typename Checked = bool >
      explicit menuitemdata(typename Name && name,
                            typename Icon && icon_obj = QIcon{},
                            typename Enabled && enabled = false,
                            typename Checked && checked = false) :
         QObject{},
         m_submenu_itemdata{ new submenuitemdata{} },
         m_icon{ shared_ptr<QIcon>{ new QIcon{ forward<Icon>(icon_obj) } } },
         m_enabled{ forward<typename Enabled>(enabled) },
         m_checked{ forward<typename Checked>(checked) }
      {
         set_caption(forward<typename Name>(name));
      }
      ~menuitemdata() override = default;
      virtual bool const is_separator() const;
      virtual bool const is_action() const;
      virtual bool const is_submenu() const;
      virtual menuitemdata & operator[](menuitemdata * d);
      virtual menuitemdata & operator+(menuitemdata * d);
      submenuitemdata * get_submenu_itemdata() const;
      menuitemdata * operator=(menuitemdata const & item)
      {
         m_actionitem = move(item.m_actionitem);
         set_caption(item.objectName());
         m_checked = item.m_checked;
         m_enabled = item.m_enabled;
         m_icon = move(item.m_icon);
         return this;
      }
      action * get_actionitem()
      {
         return m_actionitem;
      }
      menuitemdata * set_actionitem(action const * value)
      {
         m_actionitem = const_cast<action *>(value);
         return this;
      }
      menuitemdata * set_icon(QIcon const & icon)
      {
         m_icon->operator=(icon);
         return this;
      }
      shared_ptr<QIcon> const & get_icon() const
      {
         return m_icon;
      }
      bool get_enabled()
      {
         return m_enabled;
      }
      bool get_checked()
      {
         return m_checked;
      }
      menuitemdata * set_enabled(bool const & enabled)
      {
         m_enabled = enabled;
         return this;
      }
      menuitemdata * set_checked(bool const & checked)
      {
         m_checked = checked;
         return this;
      }
      menuitemdata * set_caption(unicodestring const & caption)
      {
         setObjectName(caption);
         return this;
      }
      unicodestring const get_caption() const
      {
         return objectName();
      }
      long const get_id() const
      {
         return m_id;
      }
      menuitemdata * set_id(long const & id)
      {
         m_id = id;
         return this;
      }
      /**/
   protected:
      shared_ptr<QIcon> m_icon{ nullptr };
      action * m_actionitem{ nullptr };
      shared_ptr<submenuitemdata> m_submenu_itemdata{ nullptr };
      long m_id{ 0l };
      bool m_enabled{ false };
      bool m_checked{ false };
   };
};