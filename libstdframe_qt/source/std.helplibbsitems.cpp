//-----------------------------------------------------------------------------------------------//
// stdx.frame.x86 for Windows
// Dynamic library for QTxx
// Created by Wilson.Souza 2012, 2018
//
// WR Devinfo
// (c) 2016
//-----------------------------------------------------------------------------------------------//
#include <std.defsx.hpp>
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   helplibbsitems::helplibbsitems() :menuitems{ captions::help{}.NAME }, icons::help{}
   {
      auto about_app = captions::help{}.ABOUT.arg(QApplication::instance()->applicationName());
      //
      operator+(new menuitemdata{ captions::help{}.INDEX, INDEX }).
         separator().
         operator+(new menuitemdata{ captions::help{}.LIBBS }).
         operator+(new menuitemdata{ captions::help{}.DEDALUS }).
         separator().
         operator+(new menuitemdata{ unicodestring{about_app} });
   }
}