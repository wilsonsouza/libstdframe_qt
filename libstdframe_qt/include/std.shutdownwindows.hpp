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
#include <std.defs.hpp>
//-----------------------------------------------------------------------------------------------//
#if defined(Q_OS_WIN)
namespace std
{
   class Q_DECL_EXPORT shutdownwindows
   {
   public:
      shutdownwindows() = default;
      ~shutdownwindows() = default;
      virtual bool const make();
      virtual bool const abort();
      virtual bool const display(unicodestring const & message);
      /**/
   protected:
      virtual bool const open_process();
      /**/
   protected:
      HANDLE m_token;
      TOKEN_PRIVILEGES m_tkp;
      HRESULT m_result;
   };
   //-----------------------------------------------------------------------------------------------//
   __inline bool const shutdownwindows::make()
   {
      ZeroMemory(&m_tkp, 0, sizeof(m_tkp));
      /**/
      if (!open_process())
      {
         return false;
      }
      /* Get the LUID for the shutdown privilege.  */
      LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &m_tkp.Privileges[0].Luid);
      /* one privilege to set */
      m_tkp.PrivilegeCount = 1;
      m_tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

      /* Get the shutdown privilege for this process.  */
      AdjustTokenPrivileges(m_token, FALSE, &m_tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

      if (GetLastError() != ERROR_SUCCESS)
      {
         return false;
      }
      /* Shut down the system and force all applications to close. */
      if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE,
          SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_MINOR_UPGRADE |
          SHTDN_REASON_FLAG_PLANNED))
      {
         return false;
      }
      /* shutdown was successful */
      return true;
   }
   //-----------------------------------------------------------------------------------------------//
   __inline bool const shutdownwindows::open_process()
   {
      /* check if token already is use */
      if (m_token != nullptr)
      {
         return true;
      }
      /* Get a token for this process.  */
      if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &m_token))
      {
         return false;
      }
      return true;
   }
   //-----------------------------------------------------------------------------------------------//
   __inline bool const shutdownwindows::abort()
   {
      ZeroMemory(&m_tkp, 0, sizeof(m_tkp));
      /**/
      if (!open_process())
      {
         return false;
      }
      LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &m_tkp.Privileges[0].Luid);
      m_tkp.PrivilegeCount = 1;  // one privilege to set    
      m_tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

      // Get shutdown privilege for this process. 

      AdjustTokenPrivileges(m_token, FALSE, &m_tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

      if (GetLastError() != ERROR_SUCCESS)
      {
         return false;
      }
      // Prevent the system from shutting down. 

      if (!AbortSystemShutdown(NULL))
      {
         return false;
      }
      // Disable shutdown privilege. 

      m_tkp.Privileges[0].Attributes = 0;
      AdjustTokenPrivileges(m_token, FALSE, &m_tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
      return true;
   }
   //-----------------------------------------------------------------------------------------------//
   __inline bool const shutdownwindows::display(unicodestring const & message)
   {
      ZeroMemory(&m_tkp, 0, sizeof(m_tkp));
      /**/
      if (!OpenProcess())
         return false;

      // Get the LUID for shutdown privilege. 
      LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &m_tkp.Privileges[0].Luid);
      m_tkp.PrivilegeCount = 1;  // one privilege to set    
      m_tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

      // Get shutdown privilege for this process. 
      AdjustTokenPrivileges(m_token, FALSE, &m_tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

      // Cannot test the return value of AdjustTokenPrivileges. 
      if (GetLastError() != ERROR_SUCCESS)
         return false;

   #if defined(UNICODE) || defined(_UNICODE)
      LPCWSTR lpMsg = message.to_wstring().c_str();
   #else
      LPCTSTR lpMsg = strMsg.to_string().c_str();
   #endif

      // Display the shutdown dialog box and start the countdown. 
      m_result = InitiateSystemShutdown(NULL,    // shut down local computer 
                                        LPWSTR(lpMsg),   // message for user
                                        0x3c,    // time-out period, in seconds 
                                        FALSE,   // ask user to close apps 
                                        TRUE);   // reboot after shutdown 

      if (!m_result)
      {
         return false;
      }
      // Disable shutdown privilege. 
      m_tkp.Privileges[0].Attributes = 0;
      AdjustTokenPrivileges(m_token, FALSE, &m_tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
      return true;
   }
}
//-----------------------------------------------------------------------------------------------//
#endif