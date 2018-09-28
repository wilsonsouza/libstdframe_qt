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
#include <std.defs.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT mainwindow;
   class Q_DECL_EXPORT mdiframewindow;
   class Q_DECL_EXPORT popup;
   class Q_DECL_EXPORT action;
   class Q_DECL_EXPORT menu;
   class Q_DECL_EXPORT menubar : public QMenuBar
   {
      Q_OBJECT
   public:
      friend class mainwindow;
      friend class mdiframewindow;
      friend class menu;
   public:
      /**/
      explicit menubar(QWidget * owner, unicodestring const & name = unicodestring{}) :QMenuBar{ owner }
      {
         set_notify_everything()->setObjectName(name);
      }
      ~menubar() override
      {
         disconnect();
      }
      menubar * create(popup const & owner, action * sender);
      action * operator [](unicodestring menu_id);
      virtual menubar * set_enable(unicodestring const & menu_id, bool value_enabled);
      virtual bool get_enabled(unicodestring const & menu_id);
      virtual menubar * set_enabled_mdi_actions(mdiframewindow * frame);
      mainwindow * get_mainwindow() const;
      /**/
   public:
      function<bool(action * ptr, menubar * sender)> on_hovered{ nullptr };
      function<bool(action * ptr, menubar * sender)> on_command{ nullptr };
      function<bool(action * action_ptr, menubar * sender, bool & enabled_value)> on_update_ui{ nullptr };
      /**/
   protected:
      void focusInEvent(QFocusEvent * e) override;
      virtual menubar * set_notify_everything();
   };
}