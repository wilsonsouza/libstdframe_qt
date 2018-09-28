//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//-----------------------------------------------------------------------------------------------//
#include <std.dialog_login.hpp>
#include <std.label.hpp>
#include <std.button.hpp>
#include <std.linedate.hpp>
#include <std.combobox.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   dialog_login::dialog_login(QWidget * owner, unicodestring const & caption) :
      dialog{ owner, 0, caption },
      m_user{ new lineedit{this, captions::login_titles{}.USERNAME} },
      m_password{ new lineedit{this, captions::login_titles{}.PASSWORD} },
      m_domainlist{ new combobox{this, captions::login_titles{}.DOMAINID} }
   {
      setWindowIcon(m_iconslist->PASSWORD);
      /**/
   #if defined(Q_OS_WIN)
      m_authenticate = shared_ptr<sspi>(new sspi());
   #endif
      m_user->on_textchanged = [=](unicodestring const & value, lineedit * sender)->auto
      {
         m_ok->setEnabled(!value.trimmed().isEmpty() && !m_password->text().trimmed().isEmpty());
         return true;
      };
      m_password->on_textchanged = m_user->on_textchanged;
   }
   //-----------------------------------------------------------------------------------------------//
   bool dialog_login::create(dialog * dlg)
   {
      auto items_list = set<unicodestring>{};
      /* call super and create buttons */
      dialog::create(this);
      //
      auto fb = new formbox{};
      {
         /**/
         fb->addRow(new label{ this, captions::login_titles{}.USERNAME }, m_user);
         fb->addRow(new label{ this, captions::login_titles{}.PASSWORD }, m_password);
         fb->addRow(new label{ this, captions::login_titles{}.DOMAINID }, m_domainlist);
         /**/
         vbox()->addLayout(fb);
         vbox()->addLayout(vbuttons());
      };
      //
   #if defined(Q_OS_WIN)
      m_dns_deviceinfo = make_shared<DNS_DEVICE_INFO>(m_authenticate->GetComputerDomain());
      /**/
      for (int i = 0; i < ComputerNameMax; ++i)
      {
         auto s = unicodestring::fromStdWString(m_dns_deviceinfo->szName[i]);
         /**/
         if (!s.isEmpty())
         {
            items_list.insert(s);
         }
      }
   #endif
      /**/
      m_domainlist->operator+(items_list);
      //process ok button
      m_ok->on_clicked = [&](bool const & checked, button * sender)->auto
      {
         auto domain = unicodestring{};
         /**/
         if (m_domainlist->currentText().isEmpty())
         {
            if (wstring(m_dns_deviceinfo->szName[m_dns_deviceinfo->DNS_DOMAIN]).empty())
            {
               domain = unicodestring::fromStdWString(m_dns_deviceinfo->szName[m_dns_deviceinfo->NETBIOS]);
            }
            else
            {
               domain = unicodestring::fromStdWString(m_dns_deviceinfo->szName[m_dns_deviceinfo->DNS_DOMAIN]);
            }
         }
         else
         {
            domain = m_domainlist->currentText();
         }
         /**/
      #if defined(Q_OS_WIN)
         if (m_authenticate->authenticate(domain, unicodestring{ m_user->text() }, unicodestring{ m_password->text() }))
         {
            accept();
            return close();
         }
      #endif
         return false;
      };
      m_cancel->on_clicked = [&](bool const & checked, button * sender)->auto
      {
         reject();
         return close();
      };
      return true;
   }
}