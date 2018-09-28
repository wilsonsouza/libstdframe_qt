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
#include <std.icons.hpp>
#include <std.groupbox_top_button_control.hpp>
#include <std.widget_impl.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT combobox;
   class Q_DECL_EXPORT lineedit;
   class Q_DECL_EXPORT button;
   class Q_DECL_EXPORT search_widget_control : public widget
   {
   public:
      using LookInMapper = list < pair<unicodestring, unicodestring>>;
      using FindWhatMaskMapper = list < pair<unicodestring, unicodestring>>;
      //
   public:
      enum class search_idd : uint
      {
         IDDMATCHCASE = 1,
         IDDMATCHWHOLEWORD = 2,
         IDDUSE = 4
      };
      //
   public:
      explicit search_widget_control(QWidget * owner, unicodestring const & name = unicodestring{});
      ~search_widget_control()override = default;
      search_widget_control * set_lookinmapper(search_widget_control::LookInMapper const & lm);
      search_widget_control * set_findwhat_listmask(search_widget_control::FindWhatMaskMapper const & fm);
      widget * create() override;
      //
   public:
      function<bool(search_widget_control * sender) > on_findwhat{ nullptr };
      //
   protected:
      shared_ptr<search_widget_control::LookInMapper> m_lookinhasher{ new LookInMapper{} };
      button * m_ok{ nullptr };
      button * m_cancel{ nullptr };
      button * m_help{ nullptr };
      groupbox_top_button_control * m_options{ nullptr };
      lineedit * m_findwhat{ nullptr };
      combobox * m_lookin{ nullptr };
      combobox * m_regularexpressions{ nullptr };
      unicodestring m_filterselectedname{};
      search_idd m_state{ search_idd::IDDMATCHCASE };
      shared_ptr<search_widget_control::FindWhatMaskMapper> m_findwhatmaskhasher{ new FindWhatMaskMapper{} };
      shared_ptr<icons_impl<icons::common>> m_iconslist{ new icons_impl<icons::common>{} };
   };
}
//-----------------------------------------------------------------------------------------------//
