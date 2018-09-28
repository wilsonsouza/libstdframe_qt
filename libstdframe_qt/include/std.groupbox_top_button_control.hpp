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

#include <std.defsx.hpp>
#include <std.widget.hpp>
#include <std.icons.hpp>
#include <std.label.hpp>
#include <std.toolbutton.hpp>
#include <std.groupbox_impl.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT groupbox_top_button_control : public widget
   {
      Q_OBJECT
   public:
      groupbox_top_button_control();
      explicit groupbox_top_button_control(unicodestring const & caption,
                                           unicodestring const & name = unicodestring{});
      virtual ~groupbox_top_button_control() = default;
      widget * create() override;
      groupbox_impl<vertical_box> * get_group();
      label * get_caption();
      toolbutton * get_topplus();
      //
   protected:
      groupbox_impl<vertical_box> * m_group{ nullptr };
      label * m_caption{ nullptr };
      toolbutton * m_topplus{ nullptr };
      shared_ptr<icons_impl<icons::common>> m_iconlist{ new icons_impl<icons::common>{} };
   };
}

