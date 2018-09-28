//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.winsys.hpp>
//-----------------------------------------------------------------------------------------------//
#if defined(Q_OS_WIN)
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   winsys::winsys() :WINSYSINFO{}
   {
      auto p = this;
      /**/
      p->m_hardware = shared_ptr<HW_PROFILE_INFO>(new HW_PROFILE_INFO);
      p->m_system = shared_ptr<SYSTEM_INFO>(new SYSTEM_INFO);
      p->m_version = shared_ptr<OSVERSIONINFOW>(new OSVERSIONINFOW);
      /* fill */
      m_processor_list.assign(s_processor_list + 0, s_processor_list + sizeof(s_processor_list));
      m_processor_feature_list.assign(s_processor_feature_list + 0, s_processor_feature_list + sizeof(s_processor_feature_list));
   }
   //-----------------------------------------------------------------------------------------------//
   WINSYSINFO & winsys::get_current_userinfo()
   {
      auto offset = DWORD{ MAX_PATH };
      auto buffer = new TCHAR[offset];
      //
      static_exception(GetUserName(buffer, &offset) != 0, "Failure to call GetUserName!");
      m_user_name.fromWCharArray(buffer);
      delete[]buffer;
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   WINSYSINFO & winsys::get_current_computerinfo()
   {
      GetSystemInfo(m_system.get());
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   WINSYSINFO & winsys::get_current_osinfo()
   {
      m_version->dwOSVersionInfoSize = sizeof(m_version.operator*());
      static_exception(GetVersionEx(m_version.get()) == FALSE, "Failure to call GetVersionEx!");
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
}
#endif