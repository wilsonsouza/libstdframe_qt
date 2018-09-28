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
#include <std.menuitems.hpp>
#include <std.action.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT menubar;
   class Q_DECL_EXPORT submenuitemdata;
   class Q_DECL_EXPORT menuitemdata;
   class Q_DECL_EXPORT menu : public QMenu
   {
      Q_OBJECT
   public:
      using menulist_value = list<menuitemdata *>;
      /**/
   public:
      menu() = default;
      explicit menu(QWidget * owner,
                    unicodestring const & caption,
                    unicodestring const & name = unicodestring{});
      ~menu() override;
      action * __fastcall operator [](unicodestring const & id);
      menuitems & getitems();
      virtual menu * create(menuitems * items, action * sender);
      virtual action * execute(QPoint const * point = nullptr, action * sender = nullptr);
      /**/
   public:
      function<bool(menu * sender)> on_about_to_hide{ nullptr };
      function<bool(menu * sender)> on_about_to_show{ nullptr };
      function<bool(action * source, menu * sender)> on_hovered{ nullptr };
      function<bool(action * source, menu * sender)> on_command{ nullptr };
      function<bool(action * source, menu * sender, menuitemdata * data)> on_insert{ nullptr };
      /**/
   protected:
      virtual menu * createsub(menulist_value * items, action * sender);
      /**/
   protected:
      virtual menu * set_notify_everthing();
      /**/
   private:
      menuitems m_items;
   };
}
