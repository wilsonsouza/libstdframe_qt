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
   useritems::useritems() :menuitems{ captions::user{}.NAME }, icons::user{}
   {
      operator+(new menuitemdata{ captions::user{}.PASSWORD, PASSWORD }).
         operator+(new menuitemdata{ captions::user{}.PERMISSION }).
         separator().
         operator+(new menuitemdata{ captions::user{}.MANAGER, MANAGER });
   }
}
