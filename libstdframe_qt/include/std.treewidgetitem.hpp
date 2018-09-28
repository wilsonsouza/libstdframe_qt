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
#include <std.defs.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT treewidgetitem : private QTreeWidgetItem, private QObject
   {
   public:
      template<typename param_0, typename param_1, typename param_2, typename param_3>
      treewidgetitem(param_0 && p0, param_1 && p1, param_2 && p2, param_3 && p3) :
         QTreeWidgetItem{ forward<param_0>(p0), forward<param_1>(p1), forward<param_2>(p2), forward<param_3>(p3) }
      {
      }
      treewidgetitem(treewidgetitem const & item) :QTreeWidgetItem{ item }
      {
      }
      ~treewidgetitem() override = default;
      //propertys
      virtual treewidgetitem * set_text(int column, unicodestring const & value)
      {
         setText(column, value);
         return this;
      }
      virtual treewidgetitem * set_icon(int column, QIcon const & icon)
      {
         setIcon(column, icon);
         return this;
      }
   };
}
