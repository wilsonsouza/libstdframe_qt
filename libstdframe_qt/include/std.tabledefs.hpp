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
#include <std.menuitems.hpp>
#include <std.menuitemdata.hpp>
#include <std.submenuitemdata.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   namespace captions
   {
      struct table
      {
         unicodestring const POPUPMENU_NAME{ "Table_PopupMenu" };
         unicodestring const INCLUIR{ "&Incluir" };
         unicodestring const ALTERAR{ "A&lterar" };
         unicodestring const EXCLUIR{ "&Excluir" };
         unicodestring const CANCELAR{ "&Cancelar" };
         unicodestring const PESQUISAR{ "Pesquisar" };
         unicodestring const IMPRIMIR{ "Im&primir" };
         unicodestring const VISUALIZAR_IMPRESSAO{ "&Visualizar Impressão" };
         unicodestring const CONFIGURAR_PAGINA{ "Con&figurar Pagina" };
         unicodestring const CONFIGURAR_IMPRESSORA{ "Confi&gurar Impressora" };
         unicodestring const IMPORTAR{ "Importar" };
         unicodestring const EXPORTAR{ "Exportar" };
         unicodestring const PROPERTYS{ "Propriedades" };
         table() = default;
      };
   }
   //-----------------------------------------------------------------------------------------------//
   namespace icons
   {
      struct Q_DECL_EXPORT table
      {
         using pointer = shared_ptr<QIcon>;

         pointer INCLUIR{ new QIcon{"Action-edit-add.ico" } };
         pointer ALTERAR{ new QIcon{"Action-edit.ico"} };
         pointer CANCELAR{ new QIcon{"Action-delete.ico"} };
         pointer PESQUISAR{ new QIcon{"Action-find.ico"} };
         pointer IMPRIMIR{ new QIcon{"Action-File-print.ico"} };
         pointer PROPERTYS{ new QIcon{"App-win-settings.ico"} };
         table() = default;
      };
   };
   //-----------------------------------------------------------------------------------------------//
   class Q_DECL_EXPORT tablewidget_menuitems : public menuitems, public icons::table
   {
   public:
      tablewidget_menuitems();
   };
   //-----------------------------------------------------------------------------------------------//
   class Q_DECL_EXPORT tablewidget_selectionrange : public QTableWidgetSelectionRange, public QObject
   {
   public:
      tablewidget_selectionrange() = default;
      tablewidget_selectionrange(int top, int left, int bottom, int right) : 
         QTableWidgetSelectionRange{ top, left, bottom, right }
      {
      }
      tablewidget_selectionrange(QTableWidgetSelectionRange const & rhs) : 
         QTableWidgetSelectionRange{ rhs }
      {
      }
   };
}