//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012, 2018, 2026
// For many platform
//
// 2WW Engenharia de Sistemas
// (c) 2012, 2026
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <std.submenuitemdata.hpp>
#include <std.menuitemdata.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   menuitemdata::menuitemdata(unicodestring const&& name,
                              icon const&& icon_obj,
                              bool const&& enabled,
                              bool const&& checked) :
      QObject{},
      m_subitemdata{ make_unique<submenuitemdata>() },
      m_icon{ unique_ptr<icon>{ new icon{ icon(icon_obj) } } },
      m_enabled{ enabled },
      m_checked{ checked }
   {
      set_caption(name);
   }
   //-----------------------------------------------------------------------------------------------//
   bool const menuitemdata::is_separator() const
   {
      return get_caption().contains(captions::tokens{}.SEPARATOR);
   }
   //-----------------------------------------------------------------------------------------------//
   bool const menuitemdata::is_action() const
   {
      return m_actionitem != nullptr;
   }
   //-----------------------------------------------------------------------------------------------//
   bool const menuitemdata::is_submenu() const
   {
      return m_subitemdata->empty();
   }
   //-----------------------------------------------------------------------------------------------//
   menuitemdata& menuitemdata::operator[](menuitemdata* d)
   {
      if (d)
      {
         m_subitemdata->push_back(d);
      }
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   menuitemdata& menuitemdata::operator+(menuitemdata* d)
   {
      if (d)
      {
         m_subitemdata->push_back(d);
      }
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   submenuitemdata* menuitemdata::get_submenuitemdata() const
   {
      return m_subitemdata.operator->();
   }
   //-----------------------------------------------------------------------------------------------//
   menuitemdata* menuitemdata::operator=(menuitemdata const& item)
   {
      m_actionitem = move(item.m_actionitem);
      set_caption(item.objectName());
      m_checked = item.m_checked;
      m_enabled = item.m_enabled;
      m_icon = make_unique<QIcon>(*item.m_icon);
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   action* menuitemdata::get_actionitem()
   {
      return m_actionitem;
   }
   //-----------------------------------------------------------------------------------------------//
   menuitemdata* menuitemdata::set_actionitem(action const* value)
   {
      m_actionitem = const_cast<action*>(value);
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   menuitemdata* menuitemdata::set_icon(icon const& icon)
   {
      m_icon->operator=(icon);
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   unique_ptr<icon> const& menuitemdata::get_icon() const
   {
      return m_icon;
   }
   //-----------------------------------------------------------------------------------------------//
   bool menuitemdata::get_enabled()
   {
      return m_enabled;
   }
   //-----------------------------------------------------------------------------------------------//
   bool menuitemdata::get_checked()
   {
      return m_checked;
   }
   //-----------------------------------------------------------------------------------------------//
   menuitemdata* menuitemdata::set_enabled(bool const& enabled)
   {
      m_enabled = enabled;
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   menuitemdata* menuitemdata::set_checked(bool const& checked)
   {
      m_checked = checked;
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   menuitemdata* menuitemdata::set_caption(unicodestring const& caption)
   {
      setObjectName(caption);
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   unicodestring const menuitemdata::get_caption() const
   {
      return objectName();
   }
   //-----------------------------------------------------------------------------------------------//
   long const menuitemdata::get_id() const
   {
      return m_id;
   }
   //-----------------------------------------------------------------------------------------------//
   menuitemdata* menuitemdata::set_id(long const& id)
   {
      m_id = id;
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
}
