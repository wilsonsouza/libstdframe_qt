//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012, 2013
// For many platform
//
// 2WW Engenharia de Sistemas
// (c) 2012, 2026, 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.defs.hpp>
//-----------------------------------------------------------------------------------------------//
#if defined(Q_OS_WIN)
namespace std
{
   /* lock work station */
   struct Q_DECL_EXPORT lockwindows
   {
   public:
      lockwindows ( ) = default;
      virtual ~lockwindows ( ) = default;
      virtual bool lock()
      {
         return LockWorkStation();
      }
   };
}
#endif