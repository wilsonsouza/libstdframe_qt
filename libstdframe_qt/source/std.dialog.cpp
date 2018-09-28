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
#include <std.dialog.hpp>
#include <std.application.hpp>
#include <std.timer.hpp>
#include <std.button.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   dialog::dialog(QWidget * owner, Qt::WindowFlags wf, unicodestring const & name) :
      dialog_impl{ owner, Qt::MSWindowsFixedSizeDialogHint, name }
   {
      m_ok = new button{ nullptr, captions::common{}.OK, m_iconslist->OK };
      m_cancel = new button{ nullptr, captions::common{}.CANCEL, m_iconslist->CANCEL, true };
      m_help = new button{ nullptr, captions::common{}.HELP, m_iconslist->HELPINDEX };
      m_timer = shared_ptr<std::timer>{ new timer{this, 0x64, name} };
      //set default cmd
      on_command = [&](dialog * dlg, long const & cmd, QObject * sender)->auto
      {
         return true;
      };
   }
   //-----------------------------------------------------------------------------------------------//
   dialog::~dialog()
   {
      cancel();
      disconnect();
   }
   //-----------------------------------------------------------------------------------------------//
   int  const  dialog::do_modal()
   {
      setModal(true);
      return exec();
   }
   //-----------------------------------------------------------------------------------------------//
   void dialog::show()
   {
      setModal(false);
      QDialog::show();
   }
   //-----------------------------------------------------------------------------------------------//
   bool dialog::create(dialog * dlg)
   {
      vbuttons()->addStretch();
      vbuttons()->addWidget(m_ok);
      vbuttons()->addWidget(m_cancel);
      vbuttons()->addWidget(m_help);
      /**/
      m_ok->on_clicked = [this](bool const &, button * sender)
      {
         setResult(Command::IDDOK);
         return dispatch_event_by_pplx(this, on_command, this, result(), sender);
      };
      m_cancel->on_clicked = [this](bool const &, button * sender)
      {
         setResult(Command::IDDCANCEL);
         return dispatch_event_by_pplx(this, on_command, this, result(), sender);
      };
      m_help->on_clicked = [this](bool const &, button * sender)
      {
         setResult(Command::IDDHELP);
         return dispatch_event_by_pplx(this, on_command, this, result(), sender);
      };
      /**/
      connect(m_timer.get(), &std::timer::timeout, [=]()
      {
         return dispatch_event_by_pplx(this, on_timer, this, m_timer);
      });
      return true;
   }
   //-----------------------------------------------------------------------------------------------//
   bool dialog::event(QEvent * e)
   {
      int id = e->type();

      if (id == QEvent::Polish)
      {
         function<bool(dialog * dlg)> on_create = bind(&dialog::create, this, placeholders::_1);
         if (dispatch_event_by_pplx(this, on_create, this))
         {
            e->accept();
            m_timer->start();
         }
         else
         {
            e->ignore();
         }
         return e->isAccepted();
      }
      return QDialog::event(e);
   }
   //-----------------------------------------------------------------------------------------------//
   void dialog::closeEvent(QCloseEvent * e)
   {
      if (dispatch_event_by_pplx(this, on_close, this))
      {
         e->accept();
         m_timer->stop();
      }
      else
      {
         e->ignore();
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void dialog::timerEvent(QTimerEvent * e)
   {
      if (e->timerId() == m_timer->timerId())
      {
         /*
         * call event via task
         */
         if (dispatch_event_by_pplx(this, on_timer, this, m_timer))
         {
            e->accept();
         }
         else
         {
            e->ignore();
         }
      }
   }
}
//-----------------------------------------------------------------------------------------------//
