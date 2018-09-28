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
#include <std.mdichildwindow_impl.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT timer;
   class Q_DECL_EXPORT mdichildwindow : public mdichildwindow_impl
   {
   public:
      friend class mdiframewindow;
      friend class menubar;
      friend class menu;
      friend class toolbar;
      friend class action;
   public:
      explicit mdichildwindow(QWidget * owner,
                              unicodestring const & name = unicodestring{},
                              Qt::WindowFlags wfflags = 0);
      ~mdichildwindow() override;
      virtual mdichildwindow * update();
      virtual mdichildwindow * show(uint umode = window::mode{}.MAXIMIZED);
      bool close() override;
      virtual mdichildwindow * set_widget(QWidget * owner = nullptr);
      //
   protected: //reimplement events method
      bool event(QEvent * e) override;
      void timerEvent(QTimerEvent * e) override;
      void closeEvent(QCloseEvent * e) override;
      void contextMenuEvent(QContextMenuEvent * e) override;
      void showEvent(QShowEvent * e) override;
      /**/
   protected:
      shared_ptr<sql::query> & get_sqlhandle() const;
      /**/
   protected:
      mdiframewindow * m_framewindow{ nullptr };
      uint m_mode{ window::mode{}.NORMAL };
      bool m_terminated{ false };
      widget_impl<vertical_box> * m_verticalbox{ nullptr };
      widget_impl<horizontal_box> * m_horizontalbox{ nullptr };
      widget_impl<formbox> * m_formbox{ nullptr };
      widget_impl<gridbox> * m_gridbox{ nullptr };
      shared_ptr<timer> m_timer{ nullptr };
   };
}