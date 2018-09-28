//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.defs.hpp>
#if defined(Q_OS_WIN)
#include <Ras.h>
#include <RasDlg.h>
#include <RasError.h>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT ras: public QObject
   {
   public:
      ras();
      ~ras() override = default;
      virtual bool const is_ras_connected();
      /**/
   protected:
      shared_ptr<RASCONN> m_connection{ nullptr };
      shared_ptr<RASCONNSTATUS> m_connection_status{ nullptr };
   };
}
#endif
