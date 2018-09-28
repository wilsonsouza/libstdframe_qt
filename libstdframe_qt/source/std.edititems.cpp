//-----------------------------------------------------------------------------------------------//
// stdx.frame.x86 for Windows
// Dynamic library for QTxx
// Created by Wilson.Souza 2012, 2018
//
// WR Devinfo
// (c) 2016, 2018
//-----------------------------------------------------------------------------------------------//
#include <std.defsx.hpp>
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   edititems::edititems() :menuitems(captions::edit{}.NAME), icons::edit{}
   {
      operator+(new menuitemdata{captions::edit{}.UNDO, UNDO}).
         operator+(new menuitemdata{ captions::edit{}.REDO }).
         separator().
         operator+(new menuitemdata{captions::edit{}.CUT, CUT}).
         operator+(new menuitemdata{captions::edit{}.PASTE, PASTE}).
         operator+(new menuitemdata{captions::edit{}.COPY, COPY}).
         operator+(new menuitemdata{captions::edit{}.REMOVE, REMOVE}).
         separator().
         operator+(new menuitemdata{captions::edit{}.SELECT_ALL}).
         operator+(new menuitemdata{captions::edit{}.FIND_REPLACE, FIND_REPLACE}).
         operator+(new menuitemdata{ captions::edit{}.GOTO, GOTO });
   }
   //-----------------------------------------------------------------------------------------------//
}