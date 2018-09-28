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
#include <std.label.hpp>
#include <std.progressbar.hpp>
#include <std.button.hpp>
#include <std.layouts.hpp>
#include <std.icons.hpp>
#include <std.panel.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   class Q_DECL_EXPORT mdichildwindow;
   class Q_DECL_EXPORT mdiframewindow;
   class Q_DECL_EXPORT display_progressbar : public panel
   {
      Q_OBJECT
   public:
      explicit display_progressbar(mdiframewindow * frame, mdichildwindow * child);
      ~display_progressbar() override;
      virtual bool create(uint const & offset, unicodestring const & caption);
      virtual display_progressbar * update(unicodestring const & message);
      virtual display_progressbar * remove();
      virtual display_progressbar * reset();
      virtual display_progressbar * set_maximum(uint const & max_value);
      /**/
   protected:
      button * m_cancel{ nullptr };
      progressbar * m_progress{ nullptr };
      label * m_caption{ nullptr };
      label * m_sub_caption{ nullptr };
      uint m_counter{ 0u };
      uint m_total{ 0u };
      mdiframewindow * m_frame{ nullptr };
      mdichildwindow * m_child{ nullptr };
      shared_ptr<icons_impl<icons::common>> m_iconlist{ new icons_impl<icons::common>{} };
   };
};