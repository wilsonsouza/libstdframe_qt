//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.connected_wizard.hpp>
//-----------------------------------------------------------------------------------------------//
using namespace std;
//-----------------------------------------------------------------------------------------------//
std::ConnectedWizard::ConnectedWizard()
{
   m_hParentWnd = nullptr;
   m_strCommandLine = wstring();
   m_dwUserFlags = 0;
   m_hUserContext = nullptr;
}
//-----------------------------------------------------------------------------------------------//
std::ConnectedWizard::ConnectedWizard(HWND const hParentWnd,
         wstring const & strCommandLine,
         DWORD const dwUserFlags,
         HANDLE const hUserContext)
{
   m_hParentWnd = const_cast<HWND>(hParentWnd);
   m_strCommandLine = m_strCommandLine;
   m_dwUserFlags = dwUserFlags;
   m_hUserContext = const_cast<HANDLE>(hUserContext);
}
//-----------------------------------------------------------------------------------------------//
std::ConnectedWizard::~ConnectedWizard()
{
}
//-----------------------------------------------------------------------------------------------//
