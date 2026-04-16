//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012
// For many platform
//
// 2WW Engenharia de Sistemas
// (c) 2012, 2026
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.defs.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT label : public QLabel
   {
      Q_OBJECT
   public:
      label() = default;
      explicit label(QWidget* owner,
                     unicodestring const& title,
                     unicodestring const& name = std::unicodestring(),
                     Qt::WindowFlags wf = Qt::WindowFlags{});
      virtual ~label() = default;
      /**/
   public:
      function<bool(unicodestring const & link, label * sender)> on_link_activated{ nullptr };
      function<bool(unicodestring const & link, label * sender)> on_link_hovered{ nullptr };
      /**/
   protected:
      void set_notify_everthing();
   };
}
//-----------------------------------------------------------------------------------------------//

