//-----------------------------------------------------------------------------------------------//
// stdx qt abstraction library for cpluplus
// Dynamic library for QTxx
// Created by Wilson.Souza 2012, 2018, 2026
//
// WR Devinfo
// (c) 2016, 2018
//-----------------------------------------------------------------------------------------------//
#include <std.defsx.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   viewitems::viewitems() :menuitems{ captions::view{}.NAME }
   {
      operator+(new menuitemdata{ captions::view{}.TOOLBAR }).
         operator+(new menuitemdata{ captions::view{}.STATUSBAR });
   }
}
