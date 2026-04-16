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
#include <std.defs.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT statusbar: public QStatusBar
   {
   public:
      explicit statusbar(QWidget * owner = nullptr, unicodestring const & name = unicodestring{});
      ~statusbar() override;
      /**/
      virtual statusbar * add_permanent(QWidget * owner, int strecth_value = 0);
      virtual statusbar * add(QWidget * owner, int strecth_value = 0);
      virtual statusbar * remove(QWidget * owner);
      virtual int  insert_permanent(int index, QWidget * owner, int strecth_value = 0);
      virtual int  insert(int index, QWidget * owner, int strecth_value = 0);
      //
   public:
      function<bool(unicodestring const & message, statusbar * sender)> on_message_changed{ nullptr };
      /**/
   protected:
      shared_ptr<QList<QWidget *>> m_list_widget;
   };
};