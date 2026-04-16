//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012, 2018, 2026
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
   class Q_DECL_EXPORT button : public QPushButton
   {
      Q_OBJECT
   public:
      explicit button(QWidget* owner,
                      unicodestring const& caption,
                      QIcon const& icon_object,
                      unicodestring const& name = unicodestring{},
                      bool const enabled = false);
      virtual ~button() override
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

