//-----------------------------------------------------------------------------------------------//
// stdx.frame.x86 for Windows
// Dynamic library for QTxx
// Created by Wilson.Souza 2012, 2018
//
// WR Devinfo
// (c) 2016, 2018
//-----------------------------------------------------------------------------------------------//
#include <std.defsx.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   styleitems::styleitems() :menuitems{ captions::style{}.NAME }, icons::style{}
   {
      operator+(new menuitemdata{ captions::style{}.CDE }).
         operator+(new menuitemdata{ captions::style{}.MACINTOSH, MACINTOSH }).
         operator+(new menuitemdata{ captions::style{}.MOTIF, captions::tokens{}.nullicon, true }).
         operator+(new menuitemdata{ captions::style{}.PLASTIQUE }).
         operator+(new menuitemdata{ captions::style{}.VISTA, captions::tokens{}.nullicon }).
         operator+(new menuitemdata{ captions::style{}.WINDOWS, WINDOWS, true }).
         operator+(new menuitemdata{ captions::style{}.XP, captions::tokens{}.nullicon, true }).
         operator+(new menuitemdata{ captions::style{}.FUSION, captions::tokens{}.nullicon, true });
   }
}