//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)

#include <std.dialog.hpp>
#include <std.lineedit.hpp>
#include <std.groupbox.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   namespace captions
   {
      struct dialog_search
      {
         const std::unicodestring SELECT_MODE{ "Selecione a chave de pesquisa" };
         const std::unicodestring PESQUISAR{ "Pesquisar" };
         const std::unicodestring NAME{ "Pesquisar" };
         const std::unicodestring ITEMS{ "items" };
         const std::unicodestring DATA{ "data" };
         const std::unicodestring TIMER{ "find_dlg_item_timer" };
         dialog_search() = default;
      };
   }
   //----------------------------------------------------------------------------------------------//
   class Q_DECL_EXPORT dialog_search : public dialog
   {
      Q_OBJECT
   public:
      explicit dialog_search(QWidget * owner, unicodestring const & name);
      ~dialog_search() override = default;
      bool create(dialog * dlg) override;
      //
   protected:
      lineedit m_find_what{ nullptr };
      groupbox * m_groupbox_options{ nullptr };
   };
};