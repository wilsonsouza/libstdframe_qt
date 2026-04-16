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
   class Q_DECL_EXPORT combobox : public QComboBox
   {
      Q_OBJECT
   public:
      struct items
      {
         unicodestring name{};
         QVariant data{};
         QIcon icon{};
         items() = default;
         explicit items(unicodestring const& name, QVariant const& data, QIcon const& icon) :
            name{ name }, data{ data }, icon{ icon }
         {
         }
      };
   public:
      explicit combobox(QWidget* owner, unicodestring const& caption, bool const& enabled = true);
      virtual ~combobox();
      combobox& operator + (combobox::items const& iten);
      combobox& operator + (stringlist const& list_items);
      combobox& operator + (set<unicodestring> const& set_items);
      combobox::items const operator[](uint index);
      /*
      * receive signals events
      */
   public:
      function<bool(int const& index, combobox* sender)> on_current_index_changed{ nullptr };
      function<bool(unicodestring const& text, combobox* sender)> on_edittext_changed{ nullptr };
      function<bool(int const& index, combobox* sender)> on_activated{ nullptr };
      function<bool(QWidget* sender, unicodestring const& value)> on_update_current_data{ nullptr };
      /**/
   protected:
      void slot_currentindexchanged(int const index);
      void slot_edittextchanged(unicodestring const& data);
      void slot_activated(int const index);
      /**/
   private:
      int m_index{ -1 };
      unicodestring m_data{};
   };
}

