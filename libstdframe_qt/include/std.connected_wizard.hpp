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
//-----------------------------------------------------------------------------------------------//
#if defined(_WIN32) || defined(_WIN64)
typedef 
HRESULT (WINAPI *_FN_CreateVPNConnection)(
    _In_      const HWND hWndParent,
    _In_      const DWORD dwWizardType,
    _In_      const DWORD dwContextFlags,
    _In_      const DWORD dwUserFlags,
    _In_      const HANDLE hUserContext,
    _In_opt_  LPWSTR pszCommandLine
    );
typedef
HRESULT (WINAPI *_FN_GetInternetConnected)(
    _In_      const HWND hwndParent,
    _In_      const DWORD dwWizardType,
    _In_      const DWORD dwContextFlags,
    _In_      const DWORD dwUserFlags,
    _In_      const HANDLE hUserContext,
    _In_opt_  LPWSTR pszCommandLine
  );
typedef
HRESULT (WINAPI *_FN_GetNetworkConnected)(
    _In_      const HWND hwndParent,
    _In_      const DWORD dwWizardType,
    _In_      const DWORD dwContextFlags,
    _In_      const DWORD dwUserFlags,
    _In_      const HANDLE hUserContext,
    _In_opt_  LPWSTR pszCommandLine
  );
typedef
HRESULT (WINAPI *_FN_GetVPNConnected)(
    _In_      const HWND hwndParent,
    _In_      const DWORD dwWizardType,
    _In_      const DWORD dwContextFlags,
    _In_      const DWORD dwUserFlags,
    _In_      const HANDLE hUserContext,
    _In_opt_  LPWSTR pszCommandLine
  );
typedef
HRESULT (WINAPI *_FN_IsInternetConnected)(void);
typedef
HRESULT (WINAPI *_FN_RegisterPageWithPage)(
    const GUID *pguidParentPage,
    const GUID *pguidChildPage,
    _In_opt_  const LPWSTR pszChildModuleFileName,
    _In_opt_  const LPWSTR pszFriendlyName,
    _In_      const DWORD dwBehaviorFlags,
    _In_      const DWORD dwUserFlags,
    _In_opt_  LPWSTR pszCommandLine
  );
typedef
HRESULT (WINAPI *_FN_UnregisterPage)(
    _In_  const GUID *pguidPage,
    _In_  const BOOL fUnregisterFromCOM
  );
typedef
HRESULT (WINAPI *_FN_UnregisterPagesLink)(
    _In_  const GUID *pguidParentPage,
    _In_  const GUID *pguidChildPage
  );

namespace std
{
   namespace Connect
   {
      static wstring const CreateVPNConnection = L"CreateVPNConnectionW";
      static wstring const GetInternetConnected = L"GetInternetConnectedW";
      static wstring const GetNetworkConnected = L"GetNetworkConnectedW";
      static wstring const IsInternetConnected = L"IsInternetConnectedW";
      static wstring const RegisterPageWithPage = L"RegisterPageWithPage";
      static wstring const UnregisterPage = L"UnregisterPage";
      static wstring const UnregisterPagesLink = L"UnregisterPagesLink";
      /**/
      static wstring const DLLName = L"connect.dll";
   };
   /**/
   class Q_DECL_EXPORT ConnectedWizard
   {
   public:
      ConnectedWizard();
      explicit ConnectedWizard(HWND const hParentWnd,
         wstring const & strCommandLine,
         DWORD const dwUserFlags,
         HANDLE const hUserContext);
      virtual ~ConnectedWizard();
      /**/
      virtual void SetParentWnd(HWND const hParentWnd);
      virtual void SetCommandLine(wstring const & strCommandLine);
      virtual void SetUserFlags(DWORD const & dwUserFlags);
      virtual void SetUserContext(HANDLE const hUserContext);
      virtual void SetWizardType(DWORD const & dwWizardType);
      virtual void SetContextFlags(DWORD const & dwContextFlags);
      /**/
      virtual HWND const GetParentWnd() const;
      virtual wstring const & GetCommandLine() const;
      virtual DWORD const & GetUserFlags() const;
      virtual HANDLE const GetUserContext() const;
      virtual DWORD const & GetWizardType() const;
      virtual DWORD const & GetContextFlags() const;
      /* connect wizard api overwrite */
      virtual HRESULT CreateVPNConnection();
      virtual HRESULT GetInternetConnected();
      virtual HRESULT GetNetworkConnected();
      virtual HRESULT GetVirtualPrivateNetworkConnected();
      virtual HRESULT IsInternetConnected() const;
      virtual HRESULT RegisterPageWithPage(const GUID *pguidParentPage,
         const GUID *pguidChildPage,
         _In_opt_  const LPWSTR pszChildModuleFileName,
         _In_opt_  const LPWSTR pszFriendlyName,
         _In_      const DWORD dwBehaviorFlags);
      virtual HRESULT UnregisterPage(_In_  const GUID *pguidPage, 
         _In_  const BOOL fUnregisterFromCOM);
      virtual HRESULT UnregisterPagesLink(_In_  const GUID *pguidParentPage,
         _In_  const GUID *pguidChildPage);

   protected:
      virtual BOOL const LoadDynamicLibraryLinkConnectDLL();

   protected:
      HWND m_hParentWnd;
      wstring m_strCommandLine;
      DWORD m_dwUserFlags;
      HANDLE m_hUserContext;
      DWORD m_dwWizardType;
      DWORD m_dwContextFlags;
      /* pointer function  */
      _FN_CreateVPNConnection m_CreateVPNConnection;
      _FN_GetInternetConnected m_GetInternetConnected;
      _FN_GetNetworkConnected m_GetNetwotkConnected;
      _FN_GetVPNConnected m_GetVPNConnected;
      _FN_IsInternetConnected m_IsInternetConnected;
      _FN_RegisterPageWithPage m_RegisterPageWithPage;
      _FN_UnregisterPage m_UnregisterPage;
      _FN_UnregisterPagesLink m_UnregisterPagesLink;
   };
};
#endif


