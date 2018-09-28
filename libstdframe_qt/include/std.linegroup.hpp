//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.lineedit.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT linegroup: public map<unicodestring, lineedit *>, public QObject
   {
   public:
      using linegroup_map_value = map<unicodestring, lineedit *>;
      //
   public:
      linegroup();
      linegroup(QWidget * owner, stringlist const & queue);
      linegroup(QWidget * owner, linegroup::linegroup_map_value const & queue);
      ~linegroup() override;
   };
};
//-----------------------------------------------------------------------------------------------//

