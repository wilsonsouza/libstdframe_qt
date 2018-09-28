/**************************************************************************************************
*
* Copyright (c) 2013 Dedalus Prime. All Rights Reserveds
* DEDALUS PRIME PROPRIETARY
*
* Created by Wilson.Souza
*
*
*
*
*
*
*
* stl c++ interface jni
* Used to authentication by SSPI API
*/
#include <std.sspi.hpp>
//-----------------------------------------------------------------------------------------------//
#if defined(Q_OS_WIN)
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   sspi::sspi()
   {
      m_hToken = nullptr;
      m_hModule = nullptr;
   }
   //-----------------------------------------------------------------------------------------------//
   sspi::~sspi()
   {
      if (m_hToken != nullptr)
      {
         CloseHandle(m_hToken);
      }
      if (m_hModule)
      {
         FreeLibrary(m_hModule);
         m_hModule = nullptr;
      }

      m_AcceptSecurityContext = nullptr;
      m_AcquireCredentialsHandle = nullptr;
      m_CompleteAuthToken = nullptr;
      m_DeleteSecurityContext = nullptr;
      m_FreeContextBuffer = nullptr;
      m_FreeCredentialsHandle = nullptr;
      m_InitializeSecurityContext = nullptr;
      m_QuerySecurityPackageInfo = nullptr;
      m_QuerySecurityContextToken = nullptr;
   }
   //-----------------------------------------------------------------------------------------------//
   LPVOID sspi::RetrieveTokenInformationClass(TOKEN_INFORMATION_CLASS InfoClass, LPDWORD lpdwSize)
   {
      LPVOID pInfo = nullptr;
      BOOL bSuccess = FALSE;

      try
      {
         *lpdwSize = 0;
         /* determine the size of the buffer needed */
         GetTokenInformation(m_hToken, InfoClass, nullptr, *lpdwSize, lpdwSize);
         /**/
         if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
         {
            throw exception("GetTokenInformation insuficient buffer!");
         }
         /* allocate a buffer for getting token information */
         if ((pInfo = LocalAlloc(LPTR, *lpdwSize)) == nullptr)
         {
            throw exception("LocalAlloc failed!");
         }
         if (!GetTokenInformation(m_hToken, InfoClass, pInfo, *lpdwSize, lpdwSize))
         {
            throw exception("GetTokenInformation failed!");
         }
      }
      catch (exception const & e)
      {
         this->check_localfree(pInfo);
         return nullptr;
      }
      return pInfo;
   }
   //-----------------------------------------------------------------------------------------------//
   PSID sspi::GetUserSidFromWellKnownRid(DWORD Rid)
   {
      PUSER_MODALS_INFO_2 umi2;
      NET_API_STATUS nas;
      UCHAR ucSubAuthorityCount;
      PSID pSid = nullptr;
      BOOL bSuccess = FALSE; /* assume failure */
      /**/
      if ((nas = NetUserModalsGet(nullptr, 2, (LPBYTE *)&umi2)) != NERR_Success)
      {
         SetLastError(nas);
         return nullptr;
      }

      ucSubAuthorityCount = *GetSidSubAuthorityCount(umi2->usrmod2_domain_id);
      /* Allocate storage for new Sid. account domain Sid + account Rid */
      if ((pSid = (PSID)LocalAlloc(LPTR, GetSidLengthRequired((UCHAR)(ucSubAuthorityCount + 1)))) != nullptr)
      {
         if (InitializeSid(pSid,
             GetSidIdentifierAuthority(umi2->usrmod2_domain_id), (BYTE)(ucSubAuthorityCount + 1)))
         {
            DWORD dwSubAuthIndex = 0;

            /* Copy existing subauthorities from account domain Sid into new Sid */
            for (; dwSubAuthIndex < ucSubAuthorityCount; dwSubAuthIndex++)
            {
               *GetSidSubAuthority(pSid, dwSubAuthIndex) = *GetSidSubAuthority(umi2->usrmod2_domain_id, dwSubAuthIndex);
            }

            /* append Rid to new Sid */
            *GetSidSubAuthority(pSid, ucSubAuthorityCount) = Rid;
         }
      }

      NetApiBufferFree(umi2);
      return pSid;
   }
   //-----------------------------------------------------------------------------------------------//
   BOOL sspi::is_guest()
   {
      BOOL bGuest = FALSE;
      PSID pGuestSid = nullptr;
      PSID pUserSid = nullptr;
      TOKEN_USER *pUserInfo = nullptr;
      DWORD dwSize = 0;

      /* test if guest user */
      if ((pGuestSid = GetUserSidFromWellKnownRid(DOMAIN_USER_RID_GUEST)) == nullptr)
      {
         return bGuest;
      }
      /* get user information */
      if ((pUserInfo = reinterpret_cast<TOKEN_USER *>(RetrieveTokenInformationClass(TokenUser, &dwSize)))
          != nullptr)
      {
         if (EqualSid(pGuestSid, pUserInfo->User.Sid))
         {
            bGuest = TRUE;
         }
      }
      /* free objects in use */
      this->check_localfree(pUserInfo);
      this->check_localfree(pGuestSid);
      return bGuest;
   }
   //-----------------------------------------------------------------------------------------------//
   HMODULE sspi::LoadSecurityDynamicLibrary()
   {
      HMODULE hModule = nullptr;
      TCHAR   lpszDLL[MAX_PATH];
      OSVERSIONINFO hVerInfo;

      /*
      //  Find out which security DLL to use, depending on
      //  whether we are on Windows NT or Windows 95, Windows 2000, Windows XP, or Windows Server 2003
      //  We have to use security.dll on Windows NT 4.0.
      //  All other operating systems, we have to use Secur32.dll
      */
      hVerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
      /* If this fails, something has gone wrong */
      if (!GetVersionEx(&hVerInfo))
      {
         return FALSE;
      }
      /* define dynamic library to load */
      if (hVerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT &&
          hVerInfo.dwMajorVersion == 4 &&
          hVerInfo.dwMinorVersion == 0)
      {
         lstrcpy(lpszDLL, _T("security.dll"));
      }
      else
      {
         lstrcpy(lpszDLL, _T("secur32.dll"));
      }
      /* load dll */
      if ((hModule = LoadLibrary(lpszDLL)) == nullptr)
      {
         return nullptr;
      }

      try
      {
         m_AcceptSecurityContext = reinterpret_cast<ACCEPT_SECURITY_CONTEXT_FN>(
            GetProcAddress(hModule, "AcceptSecurityContext"));
         if (!m_AcceptSecurityContext)
         {
            throw exception("Function AcceptSecutiryContext not found!");
         }
      #if defined(UNICODE)
         m_AcquireCredentialsHandle = reinterpret_cast<ACQUIRE_CREDENTIALS_HANDLE_FN>(
            GetProcAddress(hModule, "AcquireCredentialsHandleW"));
      #else
         m_AcquireCredentialsHandle = reinterpret_cast<ACQUIRE_CREDENTIALS_HANDLE_FN>(
            GetProcAddress(hModule, "AcquireCredentialsHandleA"));
      #endif
         if (!m_AcquireCredentialsHandle)
         {
            throw exception{};
         }
         /* CompleteAuthToken is not present on Windows 9x Secur32.dll */
         /* Do not check for the availablity of the function if it is nullptr; */
         m_CompleteAuthToken = reinterpret_cast<COMPLETE_AUTH_TOKEN_FN>(
            GetProcAddress(hModule, "CompleteAuthToken"));

         m_DeleteSecurityContext = reinterpret_cast<DELETE_SECURITY_CONTEXT_FN>(
            GetProcAddress(hModule, "DeleteSecurityContext"));
         if (!m_DeleteSecurityContext)
         {
            throw exception{ "Function DeleteSecutiryContext not found!" };
         }
         m_FreeContextBuffer = reinterpret_cast<FREE_CONTEXT_BUFFER_FN>(
            GetProcAddress(hModule, "FreeContextBuffer"));
         if (!m_FreeContextBuffer)
         {
            throw exception{ "Function FreeContextBuffer not found!" };
         }
         m_FreeCredentialsHandle = reinterpret_cast<FREE_CREDENTIALS_HANDLE_FN>(
            GetProcAddress(hModule, "FreeCredentialsHandle"));
         if (!m_FreeCredentialsHandle)
         {
            throw exception{ "Function FreeCredentialsHandle not found!" };
         }
      #if defined(UNICODE)
         m_InitializeSecurityContext = reinterpret_cast<INITIALIZE_SECURITY_CONTEXT_FN>(
            GetProcAddress(hModule, "InitializeSecurityContextW"));
      #else
         m_InitializeSecurityContext = reinterpret_cast<INITIALIZE_SECURITY_CONTEXT_FN>(
            GetProcAddress(hModule, "InitializeSecurityContextA"));
      #endif
         if (!m_InitializeSecurityContext)
         {
            throw exception{ "Function InitializeSecutiryContext not found!" };
         }
      #if defined(UNICODE)
         m_QuerySecurityPackageInfo = reinterpret_cast<QUERY_SECURITY_PACKAGE_INFO_FN>(
            GetProcAddress(hModule, "QuerySecurityPackageInfoW"));
      #else
         m_QuerySecurityPackageInfo = reinterpret_cast<QUERY_SECURITY_PACKAGE_INFO_FN>(
            GetProcAddress(hModule, "QuerySecurityPackageInfoA"));
      #endif
         if (!m_QuerySecurityPackageInfo)
         {
            throw exception{ "Function QuerySecurityPackageInfo not found!" };
         }

         m_QuerySecurityContextToken = reinterpret_cast<QUERY_SECURITY_CONTEXT_TOKEN_FN>(
            GetProcAddress(hModule, "QuerySecurityContextToken"));
         if (!m_QuerySecurityContextToken)
         {
            throw exception{ "Function QuerySecurityContextToken not found!" };
         }
      }
      catch (exception const & e)
      {
         /* store handle */
         m_hModule = hModule;

         /* error ocurred finalize process */
         sspi::~sspi();
      }
      return hModule;
   }
   //-----------------------------------------------------------------------------------------------//
   BOOL sspi::GenClientContext(PAUTH_SEQ pAS, PSEC_WINNT_AUTH_IDENTITY pAuthIdentity,
                               PVOID pIn, DWORD cbIn, PVOID pOut, PDWORD pcbOut, PBOOL pfDone)
   {
      /*++

       Routine Description:

       Optionally takes an input buffer coming from the server and returns
       a buffer of information to send back to the server.  Also returns
       an indication of whether or not the context is complete.

       Return Value:

       Returns TRUE if successful; otherwise FALSE.

       --*/
      SECURITY_STATUS ss;
      TimeStamp       tsExpiry;
      SecBufferDesc   sbdOut;
      SecBuffer       sbOut;
      SecBufferDesc   sbdIn;
      SecBuffer       sbIn;
      ULONG           fContextAttr;
      /**/
      if (!pAS->bInitialized)
      {
         ss = m_AcquireCredentialsHandle(nullptr,
                                         _T("NTLM"),
                                         SECPKG_CRED_OUTBOUND,
                                         nullptr,
                                         pAuthIdentity,
                                         nullptr,
                                         nullptr,
                                         &pAS->hcred,
                                         &tsExpiry);
         /**/
         if (ss < 0)
         {
            return FALSE;
         }
         /**/
         pAS->bHaveCredHandle = TRUE;
      }

      // Prepare output buffer
      sbdOut.ulVersion = 0;
      sbdOut.cBuffers = 1;
      sbdOut.pBuffers = &sbOut;

      sbOut.cbBuffer = *pcbOut;
      sbOut.BufferType = SECBUFFER_TOKEN;
      sbOut.pvBuffer = pOut;

      // Prepare input buffer
      if (pAS->bInitialized)
      {
         sbdIn.ulVersion = 0;
         sbdIn.cBuffers = 1;
         sbdIn.pBuffers = &sbIn;

         sbIn.cbBuffer = cbIn;
         sbIn.BufferType = SECBUFFER_TOKEN;
         sbIn.pvBuffer = pIn;
      }

      ss = m_InitializeSecurityContext(&pAS->hcred,
                                       pAS->bInitialized ? &pAS->hctxt : nullptr,
                                       nullptr,
                                       0,
                                       0,
                                       SECURITY_NATIVE_DREP,
                                       pAS->bInitialized ? &sbdIn : nullptr,
                                       0,
                                       &pAS->hctxt,
                                       &sbdOut,
                                       &fContextAttr,
                                       &tsExpiry);
      /**/
      if (ss < 0)
      {
         return FALSE;
      }
      /**/
      pAS->bHaveCtxtHandle = TRUE;

      /* If necessary, complete token */
      if (ss == SEC_I_COMPLETE_NEEDED || ss == SEC_I_COMPLETE_AND_CONTINUE)
      {
         if (m_CompleteAuthToken)
         {
            if ((ss = m_CompleteAuthToken(&pAS->hctxt, &sbdOut)) < 0)
            {
               return FALSE;
            }
         }
         else
         {
            return FALSE;
         }
      }
      /**/
      *pcbOut = sbOut.cbBuffer;

      if (!pAS->bInitialized)
      {
         pAS->bInitialized = TRUE;
      }
      //
      *pfDone = !(ss == SEC_I_CONTINUE_NEEDED || ss == SEC_I_COMPLETE_AND_CONTINUE);
      return TRUE;
   }
   //-----------------------------------------------------------------------------------------------//
   BOOL sspi::GenServerContext(PAUTH_SEQ pAS,
                               PVOID pIn, DWORD cbIn, PVOID pOut, PDWORD pcbOut, PBOOL pfDone)
   {
      /*++

       Routine Description:

       Takes an input buffer coming from the client and returns a buffer
       to be sent to the client.  Also returns an indication of whether or
       not the context is complete.

       Return Value:

       Returns TRUE if successful; otherwise FALSE.

       --*/
      SECURITY_STATUS ss;
      TimeStamp       tsExpiry;
      SecBufferDesc   sbdOut;
      SecBuffer       sbOut;
      SecBufferDesc   sbdIn;
      SecBuffer       sbIn;
      ULONG           fContextAttr;

      if (!pAS->bInitialized)
      {
         if ((ss = m_AcquireCredentialsHandle(nullptr, _T("NTLM"),
             SECPKG_CRED_INBOUND, nullptr, nullptr, nullptr, nullptr, &pAS->hcred,
             &tsExpiry)) < 0)
         {
            return FALSE;
         }
         /**/
         pAS->bHaveCredHandle = TRUE;
      }
      /* Prepare output buffer */
      sbdOut.ulVersion = 0;
      sbdOut.cBuffers = 1;
      sbdOut.pBuffers = &sbOut;

      sbOut.cbBuffer = *pcbOut;
      sbOut.BufferType = SECBUFFER_TOKEN;
      sbOut.pvBuffer = pOut;

      /* Prepare input buffer */
      sbdIn.ulVersion = 0;
      sbdIn.cBuffers = 1;
      sbdIn.pBuffers = &sbIn;

      sbIn.cbBuffer = cbIn;
      sbIn.BufferType = SECBUFFER_TOKEN;
      sbIn.pvBuffer = pIn;

      if ((ss = m_AcceptSecurityContext(&pAS->hcred,
          pAS->bInitialized ? &pAS->hctxt : nullptr, &sbdIn, 0,
          SECURITY_NATIVE_DREP, &pAS->hctxt, &sbdOut, &fContextAttr,
          &tsExpiry)) < 0)
      {
         return FALSE;
      }
      /**/
      pAS->bHaveCtxtHandle = TRUE;

      /* If necessary, complete token */
      if (ss == SEC_I_COMPLETE_NEEDED || ss == SEC_I_COMPLETE_AND_CONTINUE)
      {
         if (m_CompleteAuthToken)
         {
            if ((ss = m_CompleteAuthToken(&pAS->hctxt, &sbdOut)) < 0)
            {
               return FALSE;
            }
         }
         else
         {
            return FALSE;
         }
      }
      /**/
      *pcbOut = sbOut.cbBuffer;
      /**/
      if (!pAS->bInitialized)
      {
         pAS->bInitialized = TRUE;
      }
      /**/
      *pfDone = !(ss == SEC_I_CONTINUE_NEEDED || ss == SEC_I_COMPLETE_AND_CONTINUE);
      return TRUE;
   }
   //-----------------------------------------------------------------------------------------------//
   BOOL sspi::authenticate(wstring const & strDomain,
                           wstring const & strUser, wstring const & strPassword)
   {
      AUTH_SEQ    asServer = { 0 };
      AUTH_SEQ    asClient = { 0 };
      BOOL        bDone = FALSE;
      BOOL        bResult = FALSE;
      DWORD       cbOut = 0;
      DWORD       cbIn = 0;
      DWORD       cbMaxToken = 0;
      PVOID       pClientBuf = nullptr;
      PVOID       pServerBuf = nullptr;
      PSecPkgInfo pSPI = nullptr;
      HMODULE     hModule = nullptr;
      SEC_WINNT_AUTH_IDENTITY ai;

      __try
      {
         /* load sspi functions of ms windows kernel */
         if (LoadSecurityDynamicLibrary() == nullptr)
         {
            __leave;
         }
         /* Get max token size */
         m_QuerySecurityPackageInfo(_T("NTLM"), &pSPI);
         cbMaxToken = pSPI->cbMaxToken;
         m_FreeContextBuffer(pSPI);

         /* Allocate buffers for client and server messages */
         pClientBuf = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cbMaxToken);
         pServerBuf = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cbMaxToken);

         /* Initialize auth identity structure */
         FillWinNTAuthIdentify(&ai, strDomain, strUser, strPassword);

         /* Prepare client message (negotiate) . */
         cbOut = cbMaxToken;
         if (!GenClientContext(&asClient, &ai, nullptr, 0, pClientBuf, &cbOut, &bDone))
         {
            __leave;
         }
         /* Prepare server message (challenge) .*/
         cbIn = cbOut;
         cbOut = cbMaxToken;

         if (!GenServerContext(&asServer, pClientBuf, cbIn, pServerBuf, &cbOut, &bDone))
         {
            __leave;
         }
         /*
         // Most likely failure: AcceptServerContext fails with SEC_E_LOGON_DENIED
         // in the case of bad szUser or szPassword.
         // Unexpected Result: Logon will succeed if you pass in a bad szUser and
         // the guest account is enabled in the specified domain.
         */
         /* Prepare client message (authenticate) . */
         cbIn = cbOut;
         cbOut = cbMaxToken;
         /**/
         if (!GenClientContext(&asClient, &ai, pServerBuf, cbIn, pClientBuf, &cbOut, &bDone))
         {
            __leave;
         }
         /* Prepare server message (authentication) . */
         cbIn = cbOut;
         cbOut = cbMaxToken;
         /**/
         if (!GenServerContext(&asServer, pClientBuf, cbIn, pServerBuf, &cbOut, &bDone))
         {
            __leave;
         }
         bResult = TRUE;
         if (m_QuerySecurityContextToken(&asServer.hctxt, &m_hToken) == 0)
         {
            /* is guest user */
            if (is_guest())
            {
               bResult = FALSE;
            }
         }
      }
      __finally
      {
         /* Clean up resources */
         if (asClient.bHaveCtxtHandle)
         {
            m_DeleteSecurityContext(&asClient.hctxt);
         }
         if (asClient.bHaveCredHandle)
         {
            m_FreeCredentialsHandle(&asClient.hcred);
         }
         if (asServer.bHaveCtxtHandle)
         {
            m_DeleteSecurityContext(&asServer.hctxt);
         }
         if (asServer.bHaveCredHandle)
         {
            m_FreeCredentialsHandle(&asServer.hcred);
         }
         /* free library */
         sspi::~sspi();
         /* free heap memory */
         HeapFree(GetProcessHeap(), 0, pClientBuf);
         HeapFree(GetProcessHeap(), 0, pServerBuf);
      }
      return bResult;
   }
   //-----------------------------------------------------------------------------------------------//
   DNS_DEVICE_INFO sspi::GetComputerDomain()
   {
      DNS_DEVICE_INFO ddi = { sizeof(DNS_DEVICE_INFO), PATHLEN };
      std::shared_ptr<WCHAR> lpBuffer(new WCHAR[ddi.dwLength]);

      ZeroMemory(ddi.bMode, sizeof(ddi.bMode));
      ZeroMemory(ddi.szName, sizeof(ddi.szName));
      /* get domain or workgroup name in netbios */
      for (int i = 0; i < ComputerNameMax; i++)
      {
         DWORD dwLength = PATHLEN;

         ZeroMemory(lpBuffer.operator->(), dwLength);

         if (GetComputerNameEx((COMPUTER_NAME_FORMAT)i, lpBuffer.operator->(), &dwLength))
         {
            wsprintf(ddi.szName[i], L"%s", lpBuffer.operator->());
            ddi.bMode[i] = BOOL(lstrlen(ddi.szName[i]) != 0);
         }
      }
      /* auto free buffer with std::shared_ptr<T>*/
      return ddi;
   }
   //-----------------------------------------------------------------------------------------------//
   void const sspi::FillWinNTAuthIdentify(_Out_ SEC_WINNT_AUTH_IDENTITY * psai,
                                          wstring const & strDomain,
                                          wstring const & strUser,
                                          wstring const & strPassword)
   {
      SEC_WINNT_AUTH_IDENTITY ai;
      /* initialize structure */
      ZeroMemory(&ai, sizeof(ai));
      /* fill */
      ai.Domain = reinterpret_cast<unsigned short *>(const_cast<LPWSTR>(strDomain.c_str()));
      ai.DomainLength = strDomain.length();
      ai.User = reinterpret_cast<unsigned short *>(const_cast<LPWSTR>(strUser.c_str()));
      ai.UserLength = strUser.length();
      ai.Password = reinterpret_cast<unsigned short *>(const_cast<LPWSTR>(strPassword.c_str()));
      ai.PasswordLength = strPassword.length();
      ai.Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;

      /* assign out */
      *psai = ai;
   }
   //-----------------------------------------------------------------------------------------------//
}
#endif