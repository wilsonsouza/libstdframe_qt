//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.widget_icon.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   template<typename Source, typename Icon, typename Size, typename Name>
   widget_icon::widget_icon(Source *& owner, Icon && icon, Size && size, Name && name) :
      widget{ forward<Source>(owner), forward<Name>(name), 0 },
      QIcon{ forward<Icon>(icon) },
      m_pressed{ false },
      m_size{ forward<Size>(size) }
   {
   }
   //-----------------------------------------------------------------------------------------------//
   template<typename IconFileName>
   widget_icon * widget_icon::set_icon_filename(IconFileName const && icon_filename)
   {
      dynamic_cast<QIcon &>(*this) = QIcon{ forward<IconFileName>(icon_filename) };
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   template<typename Icon> widget_icon * widget_icon::set_icon(Icon const && icon_value)
   {
      dynamic_cast<QIcon &>(*this) = forward<Icon>(icon_value);
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   void widget_icon::paintEvent(QPaintEvent * paint_event)
   {
      QPainter painter(this);
      auto areapoint = paint_event->rect();
      auto brush = QBrush{ Qt::cyan };
      auto painter_pathicon = QPainterPath{ QPointF{qreal(m_size.x()), qreal(m_size.y())} };
      //
      painter.setPen(m_pressed ? Qt::red : Qt::black);
      painter_pathicon.addRect(0, 0, m_size.x(), m_size.y());
      painter.drawPath(painter_pathicon);
      painter.fillPath(painter_pathicon, brush);
   }
   //-----------------------------------------------------------------------------------------------//
   void widget_icon::mousePressEvent(QMouseEvent * mouse_event)
   {
      if (mouse_event->button() == QMouseEvent::MouseButtonPress)
      {
         m_pressed = true;
         QWidget::update();
         dispatch_event(on_clicked, mouse_event, this, m_pressed);
         mouse_event->accept();
         return;
      }
      else if(mouse_event->button() == QMouseEvent::MouseButtonRelease)
      {
         m_pressed = !m_pressed;
         QWidget::update();
         dispatch_event(on_clicked, mouse_event, this, m_pressed);
         mouse_event->accept();
         return;
      }
      QWidget::mousePressEvent(mouse_event);
   }
}