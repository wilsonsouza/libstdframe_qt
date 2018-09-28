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
   windowitems::windowitems() :menuitems{ captions::window{}.NAME }, icons::window{}
   {
      operator+(new menuitemdata{ captions::window{}.MAXIMIZE, MAXIMIZE }).
         operator+(new menuitemdata{ captions::window{}.MINIMIZE, MINIMIZE }).
         operator+(new menuitemdata{ captions::window{}.NEXT, NEXT }).
         operator+(new menuitemdata{ captions::window{}.PREVIOUS, PREVIOUS }).
         operator+(new menuitemdata{ captions::window{}.REFRESH, REFRESH }).
         separator().
         operator+(new menuitemdata{ captions::window{}.CLOSE, CLOSE }).
         operator+(new menuitemdata{ captions::window{}.CLOSEALL, CLOSEALL }).
         separator().
         operator+(new menuitemdata{ captions::window{}.CASCADE }).
         operator+(new menuitemdata{ captions::window{}.TILE, TILE }).
         operator+(new menuitemdata{ captions::window{}.HIDE, HIDE }).
         operator+(new menuitemdata{ captions::window{}.SHOW }).
         separator().
         operator+(new menuitemdata{ captions::window{}.TABBED, TABBED }).
         operator+(new menuitemdata{ captions::window{}.DOCUMENT, DOCUMENT });
   }
}