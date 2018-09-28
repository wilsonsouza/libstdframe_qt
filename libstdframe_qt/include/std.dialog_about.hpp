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
#include <std.dialog.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT dialog_about : public dialog
   {
      Q_OBJECT
   public:
      using pointer = shared_ptr<dialog_about>;
      /**/
   public:
      explicit dialog_about(QWidget * owner, unicodestring const & caption);
      ~dialog_about() override = default;
      bool create(dialog * dlg) override;
   };
}