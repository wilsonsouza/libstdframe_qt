//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
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
      explicit label(QWidget * owner,
                     unicodestring const & title,
                     unicodestring const & name = std::unicodestring(),
                     Qt::WindowFlags wf = 0) :QLabel{ owner, wf }
      {
         this->setText(title);
         this->setObjectName(name);
      }
      virtual ~label() = default;
      /**/
   public:
      function<bool(unicodestring const & link, label * sender)> on_link_activated{ nullptr };
      function<bool(unicodestring const & link, label * sender)> on_link_hovered{ nullptr };
      /**/
   protected:
      void set_notify_everthing()
      {
         connect(this, &QLabel::linkActivated, [=](unicodestring const & link)
         {
            if (on_link_activated != nullptr)
            {
               emit on_link_activated(link, this);
            }
         });
         connect(this, &QLabel::linkHovered, [=](unicodestring const & link)
         {
            if (on_link_hovered != nullptr)
            {
               emit on_link_hovered(link, this);
            }
         });
      }
   };
}
//-----------------------------------------------------------------------------------------------//

