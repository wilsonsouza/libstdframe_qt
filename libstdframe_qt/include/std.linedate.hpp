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
#include <std.lineedit.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   static unicodestring const IDSDATEFORMAT{ "DD/MM/YYYY" };
   static unicodestring const IDSDATEMASK{ "99/99/9999" };
   //-----------------------------------------------------------------------------------------------//
   class Q_DECL_EXPORT linedate : public lineedit
   {
      Q_OBJECT
   public:
      explicit linedate(QDate const & obj_date,
                        QWidget * owner,
                        unicodestring const & date_format = IDSDATEMASK,
                        unicodestring const & name = unicodestring{}) :
         lineedit{ owner, obj_date.toString(IDSDATEFORMAT), 0xA, 0x64, name }
      {
         set_inputmask(date_format);
      }
      virtual ~linedate() override = default;
   };
}
//-----------------------------------------------------------------------------------------------//

