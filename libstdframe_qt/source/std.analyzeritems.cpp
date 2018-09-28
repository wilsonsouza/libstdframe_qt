//-----------------------------------------------------------------------------------------------//
// stdx.frame.x86 for Windows
// Dynamic library for QTxx
// Created by Wilson.Souza 2012, 2018
//
// WR Devinfo
// (c) 2016
//-----------------------------------------------------------------------------------------------//
#include <std.defsx.hpp>
#include <std.menuitemdata.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   analyzeritems::analyzeritems() :menuitems{ captions::analyzer{}.NAME }
   {
      operator+(new menuitemdata{ captions::analyzer{}.PAGE });
   }
}
