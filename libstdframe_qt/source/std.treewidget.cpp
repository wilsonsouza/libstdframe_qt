//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.defs.hpp>
#include <std.application.hpp>
#include <std.menu.hpp>
#include <std.controls.hpp>
#include <std.treewidget.hpp>
#include <std.mdiframewindow.hpp>
#include <std.mdichildwindow.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   treewidget::treewidget(QWidget * owner, unicodestring const & name) :
      QTreeWidget{ owner },
      m_attached_window{ owner }
   {
      set_notify_everything()->setObjectName(name);
   }
   //-----------------------------------------------------------------------------------------------//
   treewidget::~treewidget()
   {
      disconnect();
   }
   //-----------------------------------------------------------------------------------------------//
   treewidget::treeitem_list_pointer treewidget::finditems(unicodestring const & text,
                                                           Qt::MatchFlags flags,
                                                           uint const & column)
   {
      auto itemslist = treeitem_list_pointer{ new QList<QTreeWidgetItem *>{} };
      auto out = unicodestring{ "Coluna %1 objeto com identificacão invalida!" }.arg(column);
      //
      static_exception(bool{ int(column) > columnCount() }, out);
      itemslist->append(findItems(text, flags, column));
      static_exception(itemslist->size() == 0, unicodestring{ "item %1 não encontrado" }.arg(text));
      return itemslist;
   }
   //-----------------------------------------------------------------------------------------------//
   treewidget * treewidget::updatecolumns(stringlist const columns)
   {
      parallel_for(0, columnCount(), [=](int i)
      {
         resizeColumnToContents(i);
      });
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   treewidget * treewidget::updatecolumns_byheadercount()
   {
      parallel_for(0, header()->count(), [&](int i)
      {
         resizeColumnToContents(i);
      });
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   QTreeWidgetItem * treewidget::findchild(unicodestring const & data,
                                           uint const & index,
                                           bool const & exactly_match)
   {
      int nCount = topLevelItemCount();
      QTreeWidgetItem * out_item = nullptr;
      /* internal sub function only compatible with CX11 version */
      auto findchild_item = [this, &out_item](QTreeWidgetItem * item,
                                              unicodestring const & data,
                                              uint const & index,
                                              bool exactly)-> auto
      {
         parallel_for(0, item->childCount(), [&](int i)
         {
            auto child = item->child(i);
            /**/
            if (child != nullptr)
            {
               auto str = child->text(index);
               //
               if (exactly)
               {
                  str = str.left(data.length());
               }
               //
               if (str.compare(data) == 0)
               {
                  out_item = child;
                  return;
               }
            }
         });
         return out_item;
      };
      /**/
      parallel_for(0, topLevelItemCount(), [=, &out_item](int row)
      {
         auto top = topLevelItem(row);
         /**/
         if (top != nullptr)
         {
            auto buffer = top->text(index);
            //
            if (exactly_match)
            {
               buffer = buffer.left(data.length());
            }
            //
            if (buffer.compare(data) == 0)
            {
               out_item = top;
               return;
            }
            /* find subchild */
            do
            {
               if ((out_item = findchild_item(top, buffer, row, exactly_match)) == nullptr)
               {
                  break;
               }
               else
               {
                  out_item = top;
                  return;
               }
            }
            while (true);
         }
      });
      return out_item;
   }
   //-----------------------------------------------------------------------------------------------//
   QTreeWidgetItem * treewidget::finddata(unicodestring const & data,
                                          uint const & index,
                                          bool const & exactly_match)
   {
      QTreeWidgetItem * out_top = nullptr;
      //
      parallel_for(0, topLevelItemCount(), [=, &out_top](int row)
      {
         auto top = topLevelItem(row);
         /**/
         if (top != nullptr)
         {
            auto buffer = top->data(index, Qt::UserRole).toString();
            /**/
            if (!exactly_match)
            {
               buffer = buffer.left(data.length());
            }
            /**/
            if (buffer.compare(data) == 0)
            {
               out_top = top;
               return;
            }
         }
      });
      return out_top;
   }
   //-----------------------------------------------------------------------------------------------//
   treewidget * treewidget::set_notify_everything()
   {
      connect(this, &QTreeWidget::currentItemChanged, [=](QTreeWidgetItem * cur, QTreeWidgetItem * prev)
      {
         dispatch_event(on_current_item_changed, cur, prev, this);
      });
      connect(this, &QTreeWidget::itemActivated, [=](QTreeWidgetItem * cur, int column)
      {
         dispatch_event(on_item_activated, cur, column, this);
      });
      connect(this, &QTreeWidget::itemChanged, [=](QTreeWidgetItem * item, int column)
      {
         dispatch_event(on_item_changed, item, column, this);
      });
      connect(this, &QTreeWidget::itemClicked, [=](QTreeWidgetItem * item, int column)
      {
         dispatch_event(on_item_clicked, item, column, this);
      });
      connect(this, &QTreeWidget::itemCollapsed, [=](QTreeWidgetItem * item)
      {
         dispatch_event(on_item_collapsed, item, this);
      });
      connect(this, &QTreeWidget::itemDoubleClicked, [=](QTreeWidgetItem * item, int column)
      {
         dispatch_event(on_item_double_clicked, item, column, this);
      });
      connect(this, &QTreeWidget::itemEntered, [=](QTreeWidgetItem * cur, int column)
      {
         dispatch_event(on_item_entered, cur, column, this);
      });
      connect(this, &QTreeWidget::itemExpanded, [=](QTreeWidgetItem * cur)
      {
         dispatch_event(on_item_expanded, cur, this);
      });
      connect(this, &QTreeWidget::itemPressed, [=](QTreeWidgetItem * cur, int column)
      {
         dispatch_event(on_item_pressed, cur, column, this);
      });
      connect(this, &QTreeWidget::itemSelectionChanged, [=]()
      {
         dispatch_event(on_item_selection_changed, this);
      });
      return this;
   }
}