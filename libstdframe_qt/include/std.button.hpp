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
#include <std.defs.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT button : public QPushButton
   {
      Q_OBJECT
   public:
      explicit button(QWidget * owner,
                      unicodestring const & caption,
                      QIcon const & icon_object,
                      unicodestring const & name = unicodestring{},
                      bool const enabled = false) :QPushButton{ icon_object, caption, owner }
      {
         setObjectName((name.empty()? caption: name));
         this->setEnabled(bool{ enabled });
         //
         connect(this, &QPushButton::clicked, [this](bool checked_value)
         {
            dispatch_event(on_clicked, checked_value, this);
         });
      }
      virtual ~button()
      {
         disconnect();
      }
      button * showmenu()
      {
         showMenu();
         return this;
      }
      /**/
   public:
      function<bool(bool const & checked, button * sender)> on_clicked{ nullptr };
   };
};
//-----------------------------------------------------------------------------------------------//

