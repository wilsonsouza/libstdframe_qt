//-----------------------------------------------------------------------------------------------//
// stdx.frame.x86 for Windows
// Dynamic library for QTxx
// Created by Wilson.Souza 2012, 2018
//
// WR Devinfo
// (c) 2016, 2018
//-----------------------------------------------------------------------------------------------//
#include <std.tabbedmenuitems.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   tabbedmenuitems::tabbedmenuitems() :menuitems{ captions::tabbed{}.NAME }
   {
      auto p = new menuitemdata{ captions::tabbed{}.POSITION };
      auto s = new menuitemdata{ captions::tabbed{}.SHAPE };

      p->operator+(new menuitemdata{ captions::tabbed{}.POSITION_EAST, *EAST, true });
      p->operator+(new menuitemdata{ captions::tabbed{}.POSITION_EAST, *EAST, true });
      p->operator+(new menuitemdata{ captions::tabbed{}.POSITION_NORTH, *NORTH, true });
      p->operator+(new menuitemdata{ captions::tabbed{}.POSITION_SOUTH, *SOUTH, true });
      p->operator+(new menuitemdata{ captions::tabbed{}.POSITION_WEST, *WESTH, true });

      s->operator+(new menuitemdata{ captions::tabbed{}.SHAPE_ROUNDED, QIcon{}, true });
      s->operator+(new menuitemdata{ captions::tabbed{}.SHAPE_TRIANGULAR, QIcon{}, true });

      operator+(p);
      operator+(s);
      operator+(new menuitemdata{ captions::tokens{}.SEPARATOR });
      operator+(new menuitemdata{ captions::tabbed{}.NEXT, *NEXT, true });
      operator+(new menuitemdata{ captions::tabbed{}.PREVIEW, *PREVIEW, true });
      operator+(new menuitemdata{ captions::tokens{}.SEPARATOR });
      operator+(new menuitemdata{ captions::tabbed{}.PROPERTYS, *PROPERTYS, true });
      operator+(new menuitemdata{ captions::tabbed{}.CLOSE, *CLOSE, true });
   }
}