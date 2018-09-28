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
namespace std
{
   class Q_DECL_EXPORT widget_icon : public widget, public QIcon
   {
   public:
      widget_icon() = default;
      template<typename Source, typename Icon, typename Size = QSize, typename Name = unicodestring>
      explicit widget_icon(Source *& owner,
                           Icon && icon,
                           Size && size = QSize{ 0x20, 0x20 },
                           Name && name = unicodestring{});
      ~widget_icon() override = default;
      //
      template<typename IconFileName> widget_icon * set_icon_filename(IconFileName const && icon_filename);
      template<typename Icon> widget_icon * set_icon(Icon const && icon_value);
      virtual widget_icon * set_pressed(bool const & pressed)
      {
         m_pressed = pressed;
         return this;
      }
      virtual QSize set_icon_size(QSize const & icon_size)
      {
         return dynamic_cast<QIcon &>(*this).actualSize(icon_size);
      }
      virtual bool const & get_pressed() const
      {
         return m_pressed;
      }
      //
   public:
      function<bool(QMouseEvent * mouse_event, widget_icon * sender, bool const & pressed)> on_clicked{ nullptr };
      function<bool(widget_icon * sender)> on_paint{ nullptr };
      //
   protected:
      void paintEvent(QPaintEvent * paint_event) override;
      void mousePressEvent(QMouseEvent * mouse_event) override;
      //
   protected:
      bool m_pressed{ false };
      QPoint m_size{};
   };
}