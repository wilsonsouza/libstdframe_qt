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
   toolsitems::toolsitems() :menuitems{ captions::tools{}.NAME }, icons::tools{}
   {
      operator+(new menuitemdata{ captions::tools{}.PREFERENCES, PREFERENCES });
   }
}
