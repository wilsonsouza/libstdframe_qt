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
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.captions.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   using object = QObject;
   using icon = QIcon;
   //
   class Q_DECL_EXPORT action;
   class Q_DECL_EXPORT submenuitemdata;
   class Q_DECL_EXPORT menuitemdata : public QObject
   {
   public:
      using pointer = unique_ptr<menuitemdata>;
      /**/
      menuitemdata() = delete;
      explicit menuitemdata(unicodestring const&& name,
                            icon const&& icon_obj = icon{},
                            bool const&& enabled = false,
                            bool const&& checked = false);
      virtual ~menuitemdata() override = default;
      virtual bool const is_separator() const;
      virtual bool const is_action() const;
      virtual bool const is_submenu() const;
      virtual menuitemdata& operator[](menuitemdata* d);
      virtual menuitemdata& operator+(menuitemdata* d);
      submenuitemdata* get_submenuitemdata() const;
      menuitemdata* operator=(menuitemdata const& item);
      action* get_actionitem();
      menuitemdata* set_actionitem(action const* value);
      menuitemdata* set_icon(icon const& icon);
      unique_ptr<icon> const& get_icon() const;
      bool get_enabled();
      bool get_checked();
      menuitemdata* set_enabled(bool const& enabled);
      menuitemdata* set_checked(bool const& checked);
      menuitemdata* set_caption(unicodestring const& caption);
      unicodestring const get_caption() const;
      long const get_id() const;
      menuitemdata* set_id(long const& id);
      /**/
   protected:
      unique_ptr<icon> m_icon{ nullptr };
      action* m_actionitem{ nullptr };
      unique_ptr<submenuitemdata> m_subitemdata{ nullptr };
      long m_id{ 0l };
      bool m_enabled{ false };
      bool m_checked{ false };
   };
};