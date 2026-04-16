//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012, 2018, 2026
// For many platform
//
// 2WW Engenharia de Sistemas
// (c) 2012, 2026
//-----------------------------------------------------------------------------------------------//
#include <std.widget.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   widget::widget(QWidget * owner, unicodestring const & name, Qt::WindowFlags f) : 
      widget_impl<vertical_box>{ owner, name, f }
   {
      setContextMenuPolicy(Qt::CustomContextMenu);
      QObject::connect(this, &QWidget::customContextMenuRequested, [&](const QPoint & point)
      {
         dispatch_event(this->on_context_menu_requested, point, this);
      });
   }
   //-----------------------------------------------------------------------------------------------//
   bool widget::event(QEvent * e)
   {
      auto n = e->type();
      /**/
      if (n == QEvent::MouseButtonPress)
      {
         auto b = static_cast<QMouseEvent *>(e);
         /**/
         if (b->button() == Qt::RightButton && this->childAt(b->pos()) == this)
         {
            if (dispatch_event(on_context_menu_requested, b->pos(), this))
            {
               e->accept();
            }
            else
            {
               e->ignore();
            }
            return e->isAccepted();
         }
      }
      return QWidget::event(e);
   }
   //-----------------------------------------------------------------------------------------------//
}