//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012
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
   class Q_DECL_EXPORT treeview : public QTreeView
   {
      Q_OBJECT
   public:
      explicit treeview(QWidget * owner = nullptr,
                        unicodestring const & name = std::unicodestring{});
      virtual ~treeview() override;
      virtual treeview * update();
      //
   public:
      function<bool(QModelIndex const & model_index, treeview * sender)> on_collapsed{ nullptr };
      function<bool(QModelIndex const & model_index, treeview * sender)> on_expanded{ nullptr };
      function<bool(QModelIndex const & model_index, treeview * sender)> on_activated{ nullptr };
      function<bool(QModelIndex const & model_index, treeview * sender)> on_clicked{ nullptr };
      function<bool(QModelIndex const & model_index, treeview * sender)> on_double_clicked{ nullptr };
      function<bool(QModelIndex const & model_index, treeview * sender)> on_entered{ nullptr };
      function<bool(QModelIndex const & model_index, treeview * sender)> on_pressed{ nullptr };
      function<bool(treeview * sender)> on_viewport_entered{ nullptr };
      function<bool(QPoint const & point, treeview * sender)> on_custom_context_menu_requested{ nullptr };
      //
   protected:
      virtual treeview * set_notify_everything();
   };
};
//-----------------------------------------------------------------------------------------------//
