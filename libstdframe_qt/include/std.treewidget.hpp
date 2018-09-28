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
   class Q_DECL_EXPORT menu;
   class Q_DECL_EXPORT treewidget : public QTreeWidget
   {
      Q_OBJECT
   public:
      typedef shared_ptr<QList<QTreeWidgetItem *>> treeitem_list_pointer;
      //
   public:
      explicit treewidget(QWidget * owner = nullptr, unicodestring const & name = unicodestring{});
      ~treewidget() override;

      /* find */
      virtual QTreeWidgetItem * findchild(unicodestring const & data,
                                          uint const & index = 0,
                                          bool const & exactly_match = true);
      virtual QTreeWidgetItem * finddata(unicodestring const & data,
                                         uint const & index,
                                         bool const & exactly_match = true);
      virtual treeitem_list_pointer finditems(unicodestring const & text,
                                              Qt::MatchFlags flags,
                                              uint const & column = 0);
      /**/
      virtual treewidget * updatecolumns(stringlist const columns = stringlist{});
      virtual treewidget * updatecolumns_byheadercount();
      //propertys
   private:
      virtual treewidget * set_notify_everything();
      //
   public:
      function<bool(QTreeWidgetItem * current, QTreeWidgetItem * previous, treewidget * sender)>on_current_item_changed{ nullptr };
      function<bool(QTreeWidgetItem * item, int const & column, treewidget * sender)> on_item_activated{ nullptr };
      function<bool(QTreeWidgetItem * item, int const & column, treewidget * sender)> on_item_changed{ nullptr };
      function<bool(QTreeWidgetItem * item, int const & column, treewidget * sender)> on_item_clicked{ nullptr };
      function<bool(QTreeWidgetItem * item, treewidget * sender)> on_item_collapsed{ nullptr };
      function<bool(QTreeWidgetItem * item, int const & column, treewidget * sender)> on_item_double_clicked{ nullptr };
      function<bool(QTreeWidgetItem * item, int const & column, treewidget * sender)> on_item_entered{ nullptr };
      function<bool(QTreeWidgetItem * item, treewidget * sender)> on_item_expanded{ nullptr };
      function<bool(QTreeWidgetItem * item, int const & column, treewidget * sender)> on_item_pressed{ nullptr };
      function<bool(treewidget * sender)> on_item_selection_changed{ nullptr };
      function<bool(treewidget * sender, long const & id, void const * data)> on_notify{ nullptr };
      //
   public:
      menu * m_menu_context{ nullptr };
      QWidget * m_attached_window{ nullptr };
   };
}
