//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.treeview.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   treeview::treeview(QWidget * owner, unicodestring const & name) :QTreeView{ owner }
   {
      set_notify_everything()->update()->setObjectName(name);
   }
   //-----------------------------------------------------------------------------------------------//
   treeview::~treeview()
   {
      disconnect();
   }
   //-----------------------------------------------------------------------------------------------//
   treeview * treeview::update()
   {
      this->show();
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   treeview * treeview::set_notify_everything()
   {
      connect(this, &QTreeView::collapsed, [=](QModelIndex const & index)
      {
         dispatch_event(on_collapsed, index, this);
      });
      connect(this, &QTreeView::expanded, [=](QModelIndex const & index)
      {
         dispatch_event(on_expanded, index, this);
      });
      connect(this, &QTreeView::activated, [=](QModelIndex const & index)
      {
         dispatch_event(on_activated, index, this);
      });
      connect(this, &QTreeView::clicked, [=](QModelIndex const & index)
      {
         dispatch_event(on_clicked, index, this);
      });
      connect(this, &QTreeView::entered, [=](QModelIndex const & index)
      {
         dispatch_event(on_entered, index, this);
      });
      connect(this, &QTreeView::pressed, [=](QModelIndex const & index)
      {
         dispatch_event(on_pressed, index, this);
      });
      connect(this, &QTreeView::viewportEntered, [=]()
      {
         dispatch_event(on_viewport_entered, this);
      });
      connect(this, &QTreeView::customContextMenuRequested, [=](QPoint const & point)
      {
         dispatch_event(on_custom_context_menu_requested, point, this);
      });
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
}