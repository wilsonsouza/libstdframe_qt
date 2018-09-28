//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.ras.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   ras::ras() : QObject{}
   {
      m_connection = shared_ptr<RASCONN>{ new RASCONN };
      m_connection_status = shared_ptr<RASCONNSTATUS>{ new RASCONNSTATUS };
      /**/
      m_connection->dwSize = sizeof(RASCONN);
      m_connection_status->dwSize = sizeof(RASCONNSTATUS);
   }
   //-----------------------------------------------------------------------------------------------//
   bool const std::ras::is_ras_connected()
   {
      auto dwCb = m_connection->dwSize;
      auto dwConnectionsCount = DWORD{ 1L };
      /**/
      DWORD dwSuccess = RasEnumConnections(m_connection.operator->(),
                                           &dwCb,
                                           &dwConnectionsCount);
      /**/
      if (dwSuccess == ERROR_SUCCESS)
      {
         if ((dwSuccess = RasGetConnectStatus(m_connection->hrasconn,
             m_connection_status.operator->())) == ERROR_SUCCESS)
         {
            if (m_connection_status->rasconnstate == RASCS_Connected)
            {
               return true;
            }
         }
      }
      return false;
   }
}