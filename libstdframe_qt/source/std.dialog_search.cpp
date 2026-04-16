//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012, 2013, 2018
// For many platform
//
// 2WW Engenharia de Sistemas
// (c) 2012, 2026, 2013
//-----------------------------------------------------------------------------------------------//
#include <std.dialog_search.hpp>
#include <std.button.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   dialog_search::dialog_search(QWidget * owner, unicodestring const & name) :
      dialog{ owner, 0, name }
   {
      setWindowIcon(icons_impl<icons::edit>{}.FIND_REPLACE);
   }
   //-----------------------------------------------------------------------------------------------//
   bool dialog_search::create(dialog * dlg)
   {
      //mount buttons on layout staker
      return dialog::create(dlg);
   }
}
