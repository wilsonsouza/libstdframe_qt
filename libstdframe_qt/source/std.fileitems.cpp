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
   fileitems::fileitems() :menuitems{ captions::file{}.NAME }, icons::file{}
   {
      operator+(new menuitemdata{ captions::file{}.NEW, NEW }).
         operator+(new menuitemdata{ captions::file{}.OPEN, OPEN }).
         operator+(new menuitemdata{ captions::file{}.CLOSE, CLOSE }).
         separator().
         operator+(new menuitemdata{ captions::file{}.SAVE, SAVE }).
         operator+(new menuitemdata{ captions::file{}.SAVE_AS, SAVE_AS }).
         separator().
         operator+(new menuitemdata{ captions::file{}.PRINT, PRINT }).
         operator+(new menuitemdata{ captions::file{}.PRINT_VIEW, PRINT_VIEW }).
         operator+(new menuitemdata{ captions::file{}.PRINT_SETUP, PRINT_SETUP }).
         operator+(new menuitemdata{ captions::file{}.PRINT_PAGE_SETUP, PRINT_PAGE_SETUP }).
         separator().
         operator+(new menuitemdata{ captions::file{}.RECENT_FILES }).
         separator().
         operator+(new menuitemdata{ captions::file{}.IMPORT }).
         operator+(new menuitemdata{ captions::file{}.EXPORT }).
         separator().
         operator+(new menuitemdata{ captions::file{}.CHANGE_USER, CHANGE_USER }).
         operator+(new menuitemdata{ captions::file{}.LOGOFF, LOGOFF }).
         separator().
         operator+(new menuitemdata{ captions::file{}.EXIT, EXIT, true });
   }
}