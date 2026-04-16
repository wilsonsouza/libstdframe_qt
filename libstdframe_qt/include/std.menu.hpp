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
#include <std.menuitems.hpp>
#include <std.action.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT menubar;
   class Q_DECL_EXPORT menusubitemdata;
   class Q_DECL_EXPORT menuitemdata;
   class Q_DECL_EXPORT menu : public QMenu
   {
      Q_OBJECT
   public:
      using list_values = list<menuitemdata*>;
      using widget_parent = QWidget;
      /**/
   public:
      menu() = default;
      explicit menu(widget_parent* parent,
                    unicodestring const& caption,
                    unicodestring const& name = unicodestring{});
      ~menu() override;
      action* __fastcall operator [](unicodestring const& id);
      menuitems& get_items();
      virtual menu* create(menuitems* q_items, action* sender);
      virtual action* execute(QPoint const* point = nullptr, action* sender = nullptr);
      /**/
   public:
      function<bool(menu* sender)> on_about_to_hide{ nullptr };
      function<bool(menu* sender)> on_about_to_show{ nullptr };
      function<bool(action* source, menu* sender)> on_hovered{ nullptr };
      function<bool(action* source, menu* sender)> on_command{ nullptr };
      function<bool(action* source, menu* sender, menuitemdata* data)> on_insert{ nullptr };
      /**/
   protected:
      virtual menu* create_sub(list_values* items, action* sender);
      /**/
   protected:
      virtual menu* set_notify_everthing();
      /**/
   private:
      unique_ptr<menuitems> m_items{ nullptr };
   };
}
