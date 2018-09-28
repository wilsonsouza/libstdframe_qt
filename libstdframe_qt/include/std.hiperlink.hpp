//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.label.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT hiperlink : public label
   {
   public:
      explicit hiperlink(QWidget * owner,
                         unicodestring const & url,
                         unicodestring const & caption,
                         unicodestring const & name = unicodestring{});
      ~hiperlink() override = default;
      //
   public:
      function<bool(hiperlink * sender)> on_link_url{ nullptr };
      function<bool(hiperlink *)> on_clicked{ nullptr };
      //
   protected:
      void mouseMoveEvent(QMouseEvent * e) override;
      void mouseDoubleClickEvent(QMouseEvent * e) override;
      void mousePressEvent(QMouseEvent * e) override;
      void mouseReleaseEvent(QMouseEvent * e) override;
   };
};
//-----------------------------------------------------------------------------------------------//

