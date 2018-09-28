//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//
// Last updated by wilson.souza 4-16-2015 modified table operations and events
//-----------------------------------------------------------------------------------------------//
#include <std.table.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   table::table(QWidget * owner, uint const & rows, uint const & cols, std::unicodestring const & name) :
      QTableWidget{ owner }
   {
      m_table_menu = new menu{ this, captions::table{}.POPUPMENU_NAME };
      m_table_menu->create(&tablewidget_menuitems{}, nullptr);
      setObjectName(name);
      /**/
      if (rows != 0 && cols != 0)
      {
         this->setColumnCount(cols);
         this->setRowCount(rows);
      }

      //Update columns
      this->resizeColumnsToContents();
      this->setContextMenuPolicy(Qt::DefaultContextMenu);
      //register all signals
      this->set_notify_everything();
   }
   //-----------------------------------------------------------------------------------------------//
   table * table::set_notify_everything()
   {
      this->connect(this, &QTableWidget::cellActivated, [=](int x, int y)
      {
         dispatch_event(on_cell_activated, x, y, this);
      });
      this->connect(this, &QTableWidget::cellChanged, [=](int x, int y)
      {
         dispatch_event(on_cell_changed, x, y, this);
      });
      this->connect(this, &QTableWidget::cellClicked, [=](int x, int y)
      {
         dispatch_event(on_cell_clicked, x, y, this);
      });
      this->connect(this, &QTableWidget::cellDoubleClicked, [=](int x, int y)
      {
         dispatch_event(on_cell_double_clicked, x, y, this);
      });
      this->connect(this, &QTableWidget::cellEntered, [=](int x, int y)
      {
         dispatch_event(on_cell_entered, x, y, this);
      });
      this->connect(this, &QTableWidget::cellPressed, [=](int x, int y)
      {
         dispatch_event(on_cell_pressed, x, y, this);
      });
      this->connect(this, &QTableWidget::cellWidget, [=](int x, int y)
      {
         dispatch_event(on_cell_widget, x, y, this);
      });
      this->connect(this, &QTableWidget::currentCellChanged, [=](int x, int y, int oldx, int oldy)
      {
         dispatch_event(on_current_cell_changed, x, y, oldx, oldy, this);
      });
      this->connect(this, &QTableWidget::currentItemChanged, [=](QTableWidgetItem * c, QTableWidgetItem * p)
      {
         dispatch_event(on_current_item_changed, c, p, this);
      });
      this->connect(this, &QTableWidget::itemActivated, [=](QTableWidgetItem * p)
      {
         dispatch_event(on_item_activated, p, this);
      });
      this->connect(this, &QTableWidget::itemChanged, [=](QTableWidgetItem * p)
      {
         dispatch_event(on_item_changed, p, this);
      });
      this->connect(this, &QTableWidget::itemClicked, [=](QTableWidgetItem * p)
      {
         dispatch_event(on_item_clicked, p, this);
      });
      this->connect(this, &QTableWidget::itemDoubleClicked, [=](QTableWidgetItem * p)
      {
         dispatch_event(on_item_double_clicked, p, this);
      });
      this->connect(this, &QTableWidget::itemEntered, [=](QTableWidgetItem * p)
      {
         dispatch_event(on_item_entered, p, this);
      });
      this->connect(this, &QTableWidget::itemPressed, [=](QTableWidgetItem * p)
      {
         dispatch_event(on_item_pressed, p, this);
      });
      this->connect(this, &QTableWidget::itemSelectionChanged, [=]()
      {
         dispatch_event(on_item_selection_changed, this);
      });
      return this;
   }
}