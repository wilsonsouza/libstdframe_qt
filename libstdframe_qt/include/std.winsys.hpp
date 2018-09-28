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

namespace std
{
#if defined(Q_OS_WIN)
   typedef struct tag_LISTPROCESSORINFO
   {
      using pointer = shared_ptr<tag_LISTPROCESSORINFO>;
      //
      DWORD id{ 0 };
      unicodestring name{};
   }LISTPROCESSORINFO;

   static LISTPROCESSORINFO const s_processor_list[] =
   {
      { PROCESSOR_ARCHITECTURE_AMD64, "x64 AMD or Intel." },
      { PROCESSOR_ARCHITECTURE_ARM, "ARM." },
      { PROCESSOR_ARCHITECTURE_IA64, "Intel Itanium." },
      { PROCESSOR_ARCHITECTURE_INTEL, "Intel." },
      { PROCESSOR_ARCHITECTURE_UNKNOWN, "Unknow." }
   };

   static LISTPROCESSORINFO const s_processor_feature_list[] =
   {
      /*     { PF_ARM_64BIT_LOADSTORE_ATOMIC,
           "The 64-bit load/store atomic instructions are available." },*/
           /*     { PF_ARM_DIVIDE_INSTRUCTION_AVAILABLE,
                "The divide instructions are available." },*/
                /*     { PF_ARM_EXTERNAL_CACHE_AVAILABLE, "The external cache is available." },*/
                //*     { PF_ARM_FMAC_INSTRUCTIONS_AVAILABLE,
                //     "The floating-point multiply-accumulate instruction is available." },
                //     { PF_ARM_VFP_32_REGISTERS_AVAILABLE, */
                //     "The VFP/Neon: 32 x 64bit register bank is present." },
                { PF_3DNOW_INSTRUCTIONS_AVAILABLE, "The 3D-Now instruction set is available." },
                { PF_CHANNELS_ENABLED, "The processor channels are enabled." },
                { PF_COMPARE_EXCHANGE_DOUBLE,
                "The atomic compare and exchange operation (cmpxchg) is available. " },
                { PF_COMPARE_EXCHANGE128,
                "The atomic compare and exchange 128-bit operation (cmpxchg16b) is available. " },
                { PF_COMPARE64_EXCHANGE128,
                "The atomic compare 64 and exchange 128-bit operation (cmp8xchg16) is available." },
                /*     { PF_FASTFAIL_AVAILABLE, "_fastfail() is available." },*/
                { PF_FLOATING_POINT_EMULATED,
                "Floating-point operations are emulated using a software emulator." },
                { PF_FLOATING_POINT_PRECISION_ERRATA,
                "On a Pentium, a floating-point precision error can occur in rare circumstances." },
                { PF_MMX_INSTRUCTIONS_AVAILABLE, "The MMX instruction set is available." },
                { PF_NX_ENABLED, "Data execution prevention is enabled." },
                { PF_PAE_ENABLED, "The processor is PAE-enabled. \n"
                "For more information, see Physical Address Extension." },
                { PF_RDTSC_INSTRUCTION_AVAILABLE, "The RDTSC instruction is available." },
      //{ PF_RDWRFSGSBASE_AVAILABLE, 
      //"RDFSBASE, RDGSBASE, WRFSBASE, and WRGSBASE instructions are available." },
      //{ PF_SECOND_LEVEL_ADDRESS_TRANSLATION, 
      //"Second Level Address Translation is supported by the hardware." },
      //{ PF_SSE3_INSTRUCTIONS_AVAILABLE, "The SSE3 instruction set is available." },
      //{ PF_VIRT_FIRMWARE_ENABLED, "Virtualization is enabled in the firmware." },
      { PF_XMMI_INSTRUCTIONS_AVAILABLE, "The SSE instruction set is available." },
      { PF_XMMI64_INSTRUCTIONS_AVAILABLE, "The SSE2 instruction set is available." },
      { PF_XSAVE_ENABLED,
      "The processor implements the XSAVE and XRSTOR instructions.\n"
      "Windows Server 2008, Windows Vista, Windows Server 2003, and Windows XP/2000:\n"
      "This feature is not supported until Windows 7 and Windows Server 2008 R2."
      }
   };

   typedef struct tag_WINSYSINFO
   {
      using pointer = shared_ptr<tag_WINSYSINFO>;

      unicodestring      m_os_name{};
      unicodestring      m_service_pack_name{};
      unicodestring      m_processor_name{};
      unicodestring      m_user_name{};
      unicodestring      m_domain_name{};
      unicodestring      m_computer_name{};
      shared_ptr<OSVERSIONINFO> m_version{ new OSVERSIONINFO{} };
      shared_ptr<SYSTEM_INFO> m_system{ new SYSTEM_INFO{} };
      shared_ptr<HW_PROFILE_INFO> m_hardware{ new HW_PROFILE_INFO{} };
   }WINSYSINFO;
   //
   class Q_DECL_EXPORT winsys : public WINSYSINFO, public QObject
   {
   public:
      winsys();
      ~winsys() override = default;

      virtual WINSYSINFO & get_current_userinfo();
      virtual WINSYSINFO & get_current_computerinfo();
      virtual WINSYSINFO & get_current_osinfo();
      //
   protected:
      list<LISTPROCESSORINFO> m_processor_list{};
      list<LISTPROCESSORINFO> m_processor_feature_list{};
   };
#endif
}