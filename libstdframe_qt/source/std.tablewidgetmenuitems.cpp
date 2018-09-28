//-----------------------------------------------------------------------------------------------//
// stdx.frame.x86 for Windows
// Dynamic library for QTxx
// Created by Wilson.Souza 2012, 2018
//
// WR Devinfo
// (c) 2016, 2018
//-----------------------------------------------------------------------------------------------//
#include <std.tabledefs.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   tablewidget_menuitems::tablewidget_menuitems() :menuitems{ captions::table{}.POPUPMENU_NAME }
   {
      operator+(new menuitemdata{ captions::table{}.INCLUIR, *INCLUIR }).
         operator+(new menuitemdata{ captions::table{}.ALTERAR, *ALTERAR }).
         operator+(new menuitemdata{ captions::table{}.EXCLUIR }).
         operator+(new menuitemdata{ captions::table{}.CANCELAR, *CANCELAR }).
         operator+(new menuitemdata{ captions::table{}.PESQUISAR, *PESQUISAR }).
         separator().
         operator+(new menuitemdata{ captions::table{}.PROPERTYS, *PROPERTYS });
   }
}