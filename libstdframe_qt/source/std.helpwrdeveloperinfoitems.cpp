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
   helpwrdeveloperinfoitems::helpwrdeveloperinfoitems() :menuitems{ captions::help{}.NAME }, icons::help{}
   {
      operator+(new menuitemdata{ captions::help{}.INDEX, INDEX }).
         separator().
         operator+(new menuitemdata{ captions::help{}.WRDEVINFO }).
         separator().
         operator+(new menuitemdata{ captions::help{}.ABOUT });
   }
}