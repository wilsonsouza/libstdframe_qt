//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012, 2018, 2026
// For many platform
//
// 2WW Engenharia de Sistemas
// (c) 2012, 2026
//-----------------------------------------------------------------------------------------------//
#include <std.combobox.hpp>
//-----------------------------------------------------------------------------------------------//
using namespace std;
//-----------------------------------------------------------------------------------------------//
combobox::combobox(QWidget* owner, unicodestring const& caption, bool const& enabled) :
   QComboBox{ owner }
{
   QComboBox::connect(this,
                      SIGNAL(combobox::currentIndexChanged(int)),
                      this,
                      SLOT(slot_currentindexchanged(int)));
   QComboBox::connect(this,
                      SIGNAL(combobox::editTextChanged(unicodestring const&)),
                      this,
                      SLOT(slot_edittextchanged(unicodestring const&)));
   QComboBox::connect(this,
                      SIGNAL(combobox::activated(int)),
                      this,
                      SLOT(slot_activated(int)));
   this->setEditable(false);
   this->setEnabled(enabled);
   this->setObjectName(caption);
   this->setWindowTitle(caption);
}
//-----------------------------------------------------------------------------------------------//
combobox::~combobox()
{
   disconnect();
}
//-----------------------------------------------------------------------------------------------//
combobox& combobox::operator + (combobox::items const& iten)
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
//-----------------------------------------------------------------------------------------------//
combobox& combobox::operator + (stringlist const& list_items)
{
   addItems(list_items);
   return *this;
}
//-----------------------------------------------------------------------------------------------//
combobox& combobox::operator + (set<unicodestring> const& set_items)
{
   auto out_items = stringlist{};
   copy(set_items.begin(), set_items.end(), back_inserter(out_items));
   return operator+(out_items);
}
//-----------------------------------------------------------------------------------------------//
combobox::items const combobox::operator[](uint index)
{
   if (index < count())
   {
      return items{};
   }
   return items{ itemText(index), itemData(index), itemIcon(index) };
}
//-----------------------------------------------------------------------------------------------//
void combobox::slot_currentindexchanged(int const index)
{
   dispatch_event(on_current_index_changed, index, this);
}
//-----------------------------------------------------------------------------------------------//
void combobox::slot_edittextchanged(unicodestring const& data)
{
   dispatch_event(on_edittext_changed, data, this);
}
//-----------------------------------------------------------------------------------------------//
void combobox::slot_activated(int const index)
{
   dispatch_event(on_activated, index, this);
}
