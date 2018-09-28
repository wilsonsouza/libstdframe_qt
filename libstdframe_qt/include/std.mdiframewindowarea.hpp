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
#include <std.defsx.hpp>
//-----------------------------------------------------------------------------------------------//
namespace sql
{
   class Q_DECL_EXPORT query;
   class Q_DECL_EXPORT table;
};
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT mdichildwindow;
   class Q_DECL_EXPORT mdiframewindowarea : public QMdiArea, public task_group
   {
      Q_OBJECT
   public:
      mdiframewindowarea(QWidget * owner = nullptr, unicodestring const & name = unicodestring{});
      ~mdiframewindowarea() override = default;
      virtual mdiframewindowarea * add_scrollbar(QWidget * scroll_bar, Qt::Alignment align);
      //
      virtual QList<QMdiSubWindow *> get_list_mdichildwindow() const;
      virtual mdichildwindow *   get_active_mdichildwindow() const;
      //operators
      virtual mdichildwindow * operator[](uint index);
      virtual mdichildwindow * operator[](unicodestring const & name);
      //
   protected:
      bool event(QEvent * e) override;
      void childEvent(QChildEvent * e) override;
      //
   protected:
      mdiframewindow * m_framewindow{ nullptr };
   };
   //-----------------------------------------------------------------------------------------------//
};