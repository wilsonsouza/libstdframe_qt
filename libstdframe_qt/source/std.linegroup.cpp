//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//-----------------------------------------------------------------------------------------------//
#include <std.linegroup.hpp>
#include <std.lineedit.hpp>
#include <std.linedate.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   linegroup::linegroup()
   {
      clear();
   }
   //-----------------------------------------------------------------------------------------------//
   linegroup::linegroup(QWidget * owner, stringlist const & queue)
   {
      for_each(queue.begin(), queue.end(), [=](auto const & value)
      {
         emplace(value, new lineedit{ owner, unicodestring{}, 0xff, 0x64, value });
      });
   }
   //-----------------------------------------------------------------------------------------------//
   linegroup::linegroup(QWidget * owner, linegroup::linegroup_map_value const & queue)
   {
      for_each(queue.begin(), queue.end(), [=](auto value)->auto
      {
         emplace(value.first, new lineedit{ owner, unicodestring{}, 0xff, 0x64, value.first });
      });
   }
   //-----------------------------------------------------------------------------------------------//
   linegroup::~linegroup()
   {
      clear();
   }
   //-----------------------------------------------------------------------------------------------//
}
