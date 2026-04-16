//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012, 2013
// For many platform
//
// 2WW Engenharia de Sistemas
// (c) 2012, 2026, 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)

#include <std.dialog_impl.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT dialog : public dialog_impl
   {
      Q_OBJECT
   public:
      explicit dialog(QWidget * qwner, Qt::WindowFlags wf, unicodestring const & name = unicodestring{});
      ~dialog() override;
      bool create(dialog * dlg) override;
      virtual int  const do_modal();
      virtual void show();
      /**/
   protected:
      bool event(QEvent * e) override;
      void closeEvent(QCloseEvent * e) override;
      void timerEvent(QTimerEvent * e) override;
   };
}
//-----------------------------------------------------------------------------------------------//