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
   class Q_DECL_EXPORT action;
   class action_impl : public QAction
   {
   public:
      using action_type = QAction;
      using object_value = QObject;
      /**/
   public:
      explicit action_impl(QObject * owner_ptr) :action_type{ owner_ptr }
      {
         setObjectName("action_impl");
      }
      explicit action_impl(unicodestring const & caption_name, object_value * owner_ptr) :
         action_type{ caption_name, owner_ptr }
      {
         setObjectName(caption_name);
      }
      explicit action_impl(QIcon const & icon_object, 
                           unicodestring const & caption_name, 
                           object_value * owner_ptr) :
         action_type{ icon_object, caption_name, owner_ptr }
      {
         setObjectName(caption_name);
      }
      ~action_impl() override = default;
      operator const action_type * () const
      {
         return this;
      }
      //
   public:
      function<bool const(action * sender)> on_changed{ nullptr };
      function<bool const(action * sender)> on_hovered{ nullptr };
      function<bool const(bool const & checked_value, action * sender)> on_toggled{ nullptr };
      function<bool const(bool const & checked_value, action * sender)> on_command{ nullptr };
      function<bool const(action * sender, bool const & value, uint const & value_id)> on_update_ui{ nullptr };
      //
   protected:
      virtual void const set_notify_everything() = 0;
      /**/
   protected:
      bool m_isleftpressed;
   };
   //-----------------------------------------------------------------------------------------------//
   class Q_DECL_EXPORT menu;
   class Q_DECL_EXPORT menubar;
   class Q_DECL_EXPORT mdiframewindow;
   class Q_DECL_EXPORT mainwindow;
   class Q_DECL_EXPORT action : public action_impl
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
         UNDEFINED,
         ENABLED = 1,
         CHECKED
      };
      //
   public:
      explicit action(QObject * owner_ptr) : action_impl{ owner_ptr }
      {
         set_notify_everything();
      }
      explicit action(unicodestring const & caption_name, object_value * owner_ptr) :
         action_impl{ caption_name, owner_ptr }
      {
         set_notify_everything();
      }
      explicit action(QIcon const & icon_object, 
                      unicodestring const & caption_name, 
                      object_value * owner_ptr) :
         action_impl{ icon_object, caption_name, owner_ptr }
      {
         set_notify_everything();
      }
      ~action() override
      {
         this->disconnect();
      }
      operator const action_type *() const
      {
         return this;
      }
      /**/
   protected:
      void const set_notify_everything() override;
   };
   //-----------------------------------------------------------------------------------------------//
}