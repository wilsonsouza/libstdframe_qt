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
   class Q_DECL_EXPORT action;
   namespace implement
   {
      class action : public QAction
      {
      public:
         using type_action = QAction;
         using type_object = QObject;
         using type_icon = QIcon;
         /**/
      public:
         explicit action(type_object* object,
                         unicodestring const&& name = unicodestring{"q_action"},
                         type_icon const&& icon = type_icon{}) :
            QAction{ object }
         {
            setIcon(icon);
            setText(name);
            setObjectName(name);
         }
         virtual ~action() override = default;
         //
      public:
         function<bool const(std::action* sender)> on_changed{ nullptr };
         function<bool const(std::action* sender)> on_hovered{ nullptr };
         function<bool const(bool const& checked, std::action* sender)> on_toggled{ nullptr };
         function<bool const(bool const& checked, std::action* sender)> on_command{ nullptr };
         function<bool const(std::action* sender, bool const& value, uint const& value_id)> on_update_ui{ nullptr };
         //
      protected:
         virtual void const set_notify_everything() = 0;
         /**/
      protected:
         bool m_isleftpressed;
      };
   }
   //-----------------------------------------------------------------------------------------------//
   class Q_DECL_EXPORT menu;
   class Q_DECL_EXPORT menubar;
   class Q_DECL_EXPORT mdiframewindow;
   class Q_DECL_EXPORT mainwindow;
   class Q_DECL_EXPORT action : public implement::action
   {
      Q_OBJECT
   public:
      friend class menu;
      friend class menubar;
      friend class mdiframewindow;
      friend class mainwindow;
      //
   public:
      enum class state : uint
      {
         OFF,
         ENABLED = 1,
         CHECKED
      };
      using states = set<state>;
      //
   public:
      explicit action(type_object* object,
                      unicodestring const&& name = unicodestring{},
                      type_icon const&& icon = type_icon{});
      virtual ~action() override
      {
         this->disconnect();
      }
      auto operator->()
      {
         return dynamic_cast<type_action*>(this);
      }
      /**/
   protected:
      void const set_notify_everything() override;
   };
}