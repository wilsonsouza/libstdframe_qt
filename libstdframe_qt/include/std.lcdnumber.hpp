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

#include <std.defs.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT lcdnumber : public QLCDNumber
   {
      Q_OBJECT
   public:
      explicit lcdnumber(QWidget * owner,
                         int const & digits,
                         unicodestring const & name = unicodestring{}) :
         QLCDNumber{ digits, owner }
      {
         connect(this, &lcdnumber::overflow, [=]
         {
            if (on_overflow != nullptr)
            {
               emit on_overflow(this);
            }
         });
      }
      ~lcdnumber() override
      {
         disconnect();
      }
      //
   public:
      function<bool(lcdnumber * sender)> on_overflow{ nullptr };
   };
}
//-----------------------------------------------------------------------------------------------//
