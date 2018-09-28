//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//
// Last update 5-2015
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <std.hiperlink.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   hiperlink::hiperlink(QWidget * owner,
                        unicodestring const & url,
                        unicodestring const & caption,
                        unicodestring const & name) :label{ owner, caption, name }
   {
      auto palette = shared_ptr<QPalette>{ new QPalette{} };
      auto color = shared_ptr<QColor>{ new QColor{Qt::blue} };
      /**/
      setAutoFillBackground(true);
      palette->setColor(QPalette::Foreground, *color);
      setPalette(*palette);
      setText(unicodestring{ "<a href=\"%1\">%2</a>" }.arg(url).arg(caption));
   }
   //-----------------------------------------------------------------------------------------------//
   void hiperlink::mouseMoveEvent(QMouseEvent * e)
   {
      if (childAt(e->pos()) == this)
      {
         setCursor(Qt::PointingHandCursor);
         e->accept();
      }
      else
      {
         setCursor(Qt::ArrowCursor);
         label::mouseMoveEvent(e);
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void hiperlink::mouseDoubleClickEvent(QMouseEvent * e)
   {
   }
   //-----------------------------------------------------------------------------------------------//
   void hiperlink::mousePressEvent(QMouseEvent * e)
   {
   }
   //-----------------------------------------------------------------------------------------------//
   void hiperlink::mouseReleaseEvent(QMouseEvent * e)
   {
   }
   //-----------------------------------------------------------------------------------------------//
}