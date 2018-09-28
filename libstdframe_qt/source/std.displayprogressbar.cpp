//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.layouts.hpp>
#include <std.mdichildwindow.hpp>
#include <std.mdiframewindow.hpp>
#include <std.mdiframewindowarea.hpp>
#include <std.display_progressbar.hpp>
#include <std.statusbar.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   display_progressbar::display_progressbar(mdiframewindow * frame, mdichildwindow * child) :
      panel{ this, unicodestring{} },
      m_child{child},
      m_frame{frame},
      m_caption{new label{this, "Aguarde..."}},
      m_sub_caption{ new label{this, unicodestring{}} },
      m_progress{new progressbar{this}},
      m_cancel{ new button{this, captions::common{}.CANCEL, m_iconlist->CANCEL} }
   {
      auto hboxbtn = new horizontal_box{ this, frame->objectName() };
      {
         hboxbtn->addWidget(m_cancel);
         hboxbtn->addStretch();
      }
      //
      box()->addWidget(m_caption);
      box()->addWidget(m_sub_caption);
      box()->addWidget(m_progress);
      box()->addLayout(hboxbtn);
      m_progress->set_maximum(0x64)->set_minimum(0);
      m_cancel->setEnabled(child != nullptr);
      /**/
      m_cancel->on_clicked = [=](bool const & checked, button * sender)
      {
         return dispatch_event(m_child->on_notify, this, child, (void *)WM_CLOSE, (void *)sender);
      };
      /**/
      m_cancel->setEnabled(false);
      QWidget::update();
   }
   //-----------------------------------------------------------------------------------------------//
   display_progressbar::~display_progressbar()
   {
      remove();
   }
   //-----------------------------------------------------------------------------------------------//
   bool display_progressbar::create(uint const & offset, unicodestring const & caption)
   {
      QWidget::setObjectName(caption);
      /**/
      if (m_frame->statusBar()->findChild<QWidget *>(caption))
      {
         remove();
      }
      /**/
      m_frame->statusBar()->addWidget(this);
      set_maximum(offset);
      m_progress->set_maximum(0x64)->set_minimum(0);
      show();
      /**/
      m_cancel->setToolTip(unicodestring{ "Clique aqui para <b>finalizar<\b> o processo!" });
      m_frame->statusBar()->update();
      m_caption->setText(caption);
      m_caption->update();
      /**/
      QWidget::update();
      return true;
   }
   //-----------------------------------------------------------------------------------------------//
   display_progressbar * display_progressbar::remove()
   {
      m_frame->statusBar()->removeWidget(this);
      reset()->QWidget::update();
      m_frame->statusBar()->update();
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   display_progressbar * display_progressbar::set_maximum(uint const & max_value)
   {
      reset()->m_total = max_value;
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   display_progressbar * display_progressbar::update(unicodestring const & message)
   {
      auto n = ++m_counter;
      auto result = uint(uint(n * 0x64) / m_total);
      /**/
      if (!message.empty())
      {
         m_progress->setValue(result);
         auto fmt = unicodestring().sprintf("%d %", m_progress->value());
         /**/
         m_progress->setFormat(fmt);
         m_progress->setToolTip(unicodestring("Operação em andamento.\n"
                              "Para finalizar clique no botão <b>Cancelar<\b>.\n"
                              "%1").arg(fmt));
         m_caption->setText(message);
      }
      else
      {
         m_progress->setValue(result);
      }
      //process all events on queue and exclude user input events
      m_frame->statusBar()->update();
      m_progress->update();
      m_caption->update();
      m_sub_caption->update();
      QWidget::update();
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   display_progressbar * display_progressbar::reset()
   {
      m_progress->reset();
      m_counter = m_total = 0;
      m_frame->statusBar()->update();
      QWidget::update();
      return this;
   }
}