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
#include <std.menu.hpp>
#include <std.tabledefs.hpp>
#include <std.tabledelegate.hpp>
#include <std.tablewidgetitem.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   class Q_DECL_EXPORT table : public QTableWidget
   {
      Q_OBJECT
   public:
      explicit table(QWidget * owner,
                     uint const & rows = 0,
                     uint const & cols = 0,
                     unicodestring const & name = unicodestring{});
      ~table() override
      {
         this->disconnect();
      }
   public:
      function<bool(int row, int col, table * sender)> on_cell_activated{ nullptr };
      function<bool(int row, int col, table * sender)> on_cell_changed{ nullptr };
      function<bool(int row, int col, table * sender)> on_cell_clicked{ nullptr };
      function<bool(int row, int col, table * sender)> on_cell_double_clicked{ nullptr };
      function<bool(int row, int col, table * sender)> on_cell_entered{ nullptr };
      function<bool(int row, int col, table * sender)> on_cell_pressed{ nullptr };
      function<bool(int row, int col, table * sender)> on_cell_widget{ nullptr };
      function<bool(int row, 
                    int col, 
                    int previous_row, 
                    int previous_col, 
                    table * sender)> on_current_cell_changed{ nullptr };
      function<bool(QTableWidgetItem * current, 
                    QTableWidgetItem * previous, 
                    table * sender)> on_current_item_changed{ nullptr };
      function<bool(QTableWidgetItem * item, table * sender)> on_item_activated{ nullptr };
      function<bool(QTableWidgetItem * item, table * sender)> on_item_changed{ nullptr };
      function<bool(QTableWidgetItem * item, table * sender)> on_item_clicked{ nullptr };
      function<bool(QTableWidgetItem * item, table * sender)> on_item_double_clicked{ nullptr };
      function<bool(QTableWidgetItem * item, table * sender)> on_item_entered{ nullptr };
      function<bool(QTableWidgetItem * item, table * sender)> on_item_pressed{ nullptr };
      function<bool(table * sender)> on_item_selection_changed{ nullptr };
      function<bool(QPoint const & point, table * sender)> on_custom_context_menu_requested{ nullptr };
      //
   protected:
      QTableWidgetItem * m_current_item{ nullptr };
      menu * m_table_menu{ nullptr };
      shared_ptr<QMutex> m_table_mutex{ nullptr };
      //
   private:
      virtual table * set_notify_everything();
   };
   //-----------------------------------------------------------------------------------------------//
};
//-----------------------------------------------------------------------------------------------//