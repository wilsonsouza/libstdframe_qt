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
#include <std.defsx.hpp>
#include <any>
#include <std.mainwindow_impl.hpp>
//-----------------------------------------------------------------------------------------------//
namespace sql
{
   class Q_DECL_EXPORT query;
};
//-----------------------------------------------------------------------------------------------//
namespace std
{
   struct company_names
   {
      unicodestring const COMPANY{ "WR Devinfo" };
      unicodestring const COPYRIGHT{ unicodestring{"Copyright (C) %1 %2" }.arg(QDate{}.year()).arg(COMPANY) };
      company_names() = default;
   };

   struct register_key
   {
      unicodestring const KEY{ "Widgets" };
      unicodestring const STATUSBAR{ KEY + "/StatusBar" };
      unicodestring const TOOLBAR{ KEY + "/ToolBar" };
      unicodestring const MenuBar{ KEY + "/MainMenuBar" };
      unicodestring const STYLES{ "Styles" };
      unicodestring const VIEWMODE{ KEY + "/ViewMode" };
      register_key() = default;
   };
   /**/
   using styles_mapper = map<unicodestring, unicodestring>; //alloc_mapper_styles->allocmapperstyles()
   //-----------------------------------------------------------------------------------------------//
   //class
   class Q_DECL_EXPORT application;
   class Q_DECL_EXPORT mdiframewindow;
   class Q_DECL_EXPORT mdichildwindow;
   class Q_DECL_EXPORT toolbar;
   class Q_DECL_EXPORT statusbar;
   class Q_DECL_EXPORT toolbaritems;
   class Q_DECL_EXPORT statusbaritems;
   class Q_DECL_EXPORT dockwindow;
   //-----------------------------------------------------------------------------------------------//
   class Q_DECL_EXPORT mainwindow : public implement::mainwindow
   {
      Q_OBJECT
   public:
      friend class mdichildwindow;
      friend class menubar;
      friend class statusbar;
      friend class toolbar;
      friend class menu;
      friend class application;
      //
      struct styledata
      {
         unicodestring style{};
         any style_ptr{ nullptr };

         styledata() = default;
         explicit styledata(unicodestring const& newstyle, std::any const& oldstyle) :
            style{ newstyle }, style_ptr{ oldstyle }
         {
         }
         virtual ~styledata() = default;
      };
      using type_window = mainwindow;
   public:
      explicit mainwindow(QWidget* owner = nullptr,
                      unicodestring const& name = unicodestring{},
                      Qt::WindowFlags wfflags = Qt::WindowFlags{});
      virtual ~mainwindow() override;
      /**/
      virtual mainwindow* create_dock(unicodestring const& dock_name = unicodestring{},
                                      dockwindow* dock = nullptr);
      virtual mainwindow* create_toolbar(toolbaritems* items,
                                         unicodestring const& name = unicodestring{});
      virtual mainwindow* create_toolbar(popup* handle);
      virtual mainwindow* create_menubar(popup* handle,
                                         action* sender,
                                         unicodestring const& name = unicodestring{});
      //process event on queue
      virtual mainwindow* update_process();

      //abstract method to sql handle
      virtual unique_ptr<sql::query>const& get_single_query_language_handle() = 0;

      // methods
      popup::pointer& get_popup();
      mainwindow* update() override;
      mainwindow* show(window::mode const& mode = window::mode::MAXIMIZED) override;
      bool const close();
      mainwindow* set_change_style(unicodestring const& style) override;
      template <typename widget_t> requires(derived_from<widget_t, QWidget>)
      widget_t* find_childwindow(unicodestring const& name);
      //to MenuBar
      virtual mainwindow* set_enable_menuitem(unicodestring const& name, bool const& enabled);
      virtual mainwindow* set_enable_menuitem(stringlist const& listnames, bool const& enabled);
      virtual bool const is_menuitem_enabled(unicodestring const& name) const;
      virtual action* operator[](unicodestring const& name) const;
      virtual action* find_menuitem(unicodestring const& name) const;
      virtual mainwindow* dispatch_eventlooper(bool const& all = false);
      virtual bool const process_on_command_event(bool const& checked, action* ac);
      /**/
   protected:
      bool event(QEvent* e) override;
      virtual QMenu* create_popup(menuitems* items, QMenuBar* root_ptr);
      virtual QMenu* create_subpopup(menuitemdata* itemdata);
      virtual mainwindow* set_popup_action(menuitemdata* itemdata, QMenu* menu_ptr);
      /**/
   public:
      function<bool const(QPageSetupDialog* dlg, mainwindow* sender)> on_page_setup{ nullptr };
      function<bool const(QPrintDialog* dlg, mainwindow* sender)> on_printer_setup{ nullptr };
      function<bool const(QPrintPreviewDialog* dlg, mainwindow* sender)> on_print_view{ nullptr };
      function<bool const(QPrintDialog* dlg, mainwindow* sender)> on_print{ nullptr };
      /**/
   protected:
      unique_ptr<settings> m_settings{ nullptr };
      toolbar* m_toolbar_handle{ nullptr };
      application* m_application_handle{ nullptr };
      bool m_terminated{ false };
      window::modes m_mode{ window::mode::NORMAL };
      QPrinter* m_printer{ new QPrinter{} };
      unique_ptr<styledata> m_styles{ nullptr };
      /**/
   private:
      unicodestring m_style_name{};
   };
};
//-----------------------------------------------------------------------------------------------//