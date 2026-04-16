//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012, 2013, 2018
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
   class Q_DECL_EXPORT logoffuser
   {
   public:
      logoffuser() = default;
      virtual ~logoffuser() = default;
      virtual bool const exit() const
      {
         return ExitWindowsEx(EWX_LOGOFF, 0);
      }
   };
}
#endif