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
      };
   public:
      explicit combobox(QWidget * owner, unicodestring const & caption, bool const & enabled = true) :
         QComboBox{ owner }
      {
         QComboBox::connect(this,
                            SIGNAL(combobox::currentIndexChanged(int)),
                            this,
                            SLOT(slot_currentindexchanged(int)));
         QComboBox::connect(this,
                            SIGNAL(combobox::editTextChanged(unicodestring const &)),
                            this,
                            SLOT(slot_edittextchanged(unicodestring const &)));
         QComboBox::connect(this,
                            SIGNAL(combobox::activated(int)),
                            this,
                            SLOT(slot_activated(int)));
         this->setEditable(false);
         this->setEnabled(enabled);
         this->setObjectName(caption);
         this->setWindowTitle(caption);
      }
      virtual ~combobox()
      {
         disconnect();
      }
      combobox & operator + (combobox::items const & iten)
      {
         if (iten.icon.isNull())
         {
            addItem(iten.name, iten.data);
         }
         if (!iten.icon.isNull())
         {
            addItem(iten.icon, iten.name, iten.data);
         }
         return *this;
      }
      combobox & operator + (stringlist const & list_items)
      {
         addItems(list_items);
         return *this;
      }
      combobox & operator + (set<unicodestring> const & set_items)
      {
         auto out_items = stringlist{};
         copy(set_items.begin(), set_items.end(), back_inserter(out_items));
         return operator+(out_items);
      }
      combobox::items const operator[](uint index)
      {
         if (index < count())
         {
            return items{};
         }
         return items{ itemText(index), itemData(index), itemIcon(index) };
      }
      /*
      * receive signals events
      */
   public:
      function<bool(int const & index, combobox * sender)> on_current_index_changed{ nullptr };
      function<bool(unicodestring const & text, combobox * sender)> on_edittext_changed{ nullptr };
      function<bool(int const & index, combobox * sender)> on_activated{ nullptr };
      function<bool(QWidget * sender, unicodestring const & value)> on_update_current_data{ nullptr };
      /**/
   protected:
      void slot_currentindexchanged(int index)
      {
         dispatch_event(on_current_index_changed, index, this);
      }
      void slot_edittextchanged(unicodestring const & data)
      {
         dispatch_event(on_edittext_changed, data, this);
      }

      void slot_activated(int index)
      {
         dispatch_event(on_activated, index, this);
      }
      /**/
   private:
      int m_index{ -1 };
      unicodestring m_data{};
   };
}

