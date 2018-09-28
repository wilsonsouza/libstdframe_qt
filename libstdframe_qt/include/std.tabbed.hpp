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
#include <std.menu.hpp>
#include <std.tabbeddefs.hpp>
#include <std.tabbedmenuitems.hpp>
#include <std.tabbedindex.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   class Q_DECL_EXPORT widget;
   class Q_DECL_EXPORT tabbed : public QTabWidget
   {
      Q_OBJECT
   public:
      explicit tabbed(QWidget * owner = nullptr, unicodestring const & name = unicodestring{});
      virtual ~tabbed();
      virtual int get_count() const;
      QWidget * operator[](unicodestring const & name);
      QWidget * operator[](uint tab_index);
      template<typename Control, typename Object>
      typename enable_if<is_same<typename Object, QWidget>::value>::type * find(typename Control const && value);
      virtual tabbed * set_tab_enabled(int const & index, bool const & enabled);
      virtual tabbed * set_tab_enabled(bool const & enabled);
      virtual bool is_tab_enabled(int const index) const;
      virtual list<bool> is_tab_enabled() const;
      virtual tabbed * set_tabicon(QWidget * owner, QIcon const & object_icon);
      virtual tabbed * set_current_index(QWidget * owner);
      virtual tabbedindex * update() const;
      virtual bool const is_tab_enabled(tabbedindex * tabbed_index);
      virtual tabbedindex * set_tab_enabled(tabbedindex * tabbed_index);
      int get_index(QWidget * owner);
      //
   public:
      function<bool(int index, tabbed * sender) > on_current_changed{ nullptr };
      function<bool(int index, tabbed * sender) > on_tab_close_requested{ nullptr };
      function<bool(int const & from, int const & to, tabbed * sender) > on_tab_moved{ nullptr };
      function<bool(int const & index, bool const & enabled) > on_update_ui{ nullptr };
      function<bool(QObject * sender)> on_command{ nullptr };
      function<bool(tabbed * sender, QPoint const & point)> on_custom_context_menu_requested{ nullptr };
      //
   protected:
      void mousePressEvent(QMouseEvent * mouse) override;
      bool event(QEvent * event) override;
      tabbed * set_notify_everything();
      //
   private:
      tabbedindex * m_tabbed_index;
      shared_ptr<menu> m_context_menu;
   };
   //-----------------------------------------------------------------------------------------------//
}