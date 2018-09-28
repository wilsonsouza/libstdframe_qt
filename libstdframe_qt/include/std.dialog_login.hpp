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
#include <std.dialog.hpp>
#if defined(WIN32) || defined(WIN64)
#include <std.sspi.hpp>
#endif
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   namespace captions
   {
      struct login_titles
      {
         const unicodestring USERNAME{ unicodestring::fromLatin1("Usuário") };
         const unicodestring PASSWORD{ "Senha  " };
         const unicodestring DOMAINID{ "Dominio" };
         login_titles() = default;
      };
   }
   //-----------------------------------------------------------------------------------------------//
   class Q_DECL_EXPORT combobox;
   class Q_DECL_EXPORT lineedit;
   class Q_DECL_EXPORT dialog_login : public dialog
   {
      Q_OBJECT
   public:
      explicit dialog_login(QWidget * owner, unicodestring const & caption);
      ~dialog_login() override = default;
      bool create(dialog * dlg) override;
      //
   protected:
      lineedit * m_user{ nullptr };
      lineedit * m_password{ nullptr };
      combobox * m_domainlist{ nullptr };
   #if(defined(_WIN32) || defined(_WIN64))
      shared_ptr<sspi> m_authenticate{ nullptr };
      shared_ptr<DNS_DEVICE_INFO> m_dns_deviceinfo{ nullptr };
   #endif
   };
}