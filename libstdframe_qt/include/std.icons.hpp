//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012
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
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   namespace icons
   {
      struct Q_DECL_EXPORT initial_directory : public QObject
      {
         using pointer = shared_ptr<initial_directory>;
         using value_type = QObject;
         initial_directory() = default;
         unicodestring m_path{ static_cast<QGuiApplication *>(QCoreApplication::instance())->libraryPaths()[0] };
      };

      struct Q_DECL_EXPORT file : public initial_directory
      {
         QIcon NEW{ m_path + "Action-File-new.ico" };
         QIcon OPEN{ m_path + "Action-edit.ico" };
         QIcon CLOSE{ m_path + "App-restart.ico" };
         QIcon SAVE{ m_path + "App-write.ico" };
         QIcon PRINT{ m_path + "Action-File-print.ico" };
         QIcon PRINT_VIEW{ m_path + "Action-frame-print.ico" };
         QIcon CHANGE_USER{ m_path + "App-user.ico" };
         QIcon LOGOFF{ m_path + "App-logout.ico" };
         QIcon EXIT{ m_path + "Action-exit.ico" };
         QIcon SAVE_AS{ m_path + "Device-zip-mount.ico" };
         QIcon PRINT_SETUP{ m_path + "Device-print-class.ico" };
         QIcon PRINT_PAGE_SETUP{ m_path + "Filesystem-folder-print.ico" };
         QIcon RECENT_FILES{ m_path + "Action-history.ico" };
         file() = default;
      };
      //-----------------------------------------------------------------------------------------------//
      struct Q_DECL_EXPORT edit : public initial_directory
      {
         QIcon UNDO{ m_path + "Action-reload.ico" };
         QIcon CUT{ m_path + "Action-cut.ico" };
         QIcon PASTE{ m_path + "Action-paste.ico" };
         QIcon COPY{ m_path + "Action-copy.ico" };
         QIcon REMOVE{ m_path + "Action-delete.ico" };
         QIcon FIND_REPLACE{ m_path + "Action-find.ico" };
         QIcon GOTO{ m_path + "goto.ico" };
         edit() = default;
      };
      //-----------------------------------------------------------------------------------------------//
      struct Q_DECL_EXPORT window : public initial_directory
      {
         QIcon CLOSEALL{ m_path + "Action-view-remove.ico" };
         QIcon CLOSE{ m_path + "Action-remove.ico" };
         QIcon PREVIOUS{ m_path + "Fleche gauche bleue.ico" };
         QIcon NEXT{ m_path + "Fleche droite bleue.ico" };
         QIcon TILE{ m_path + "Action-view-left-right.ico" };
         QIcon TABBED{ m_path + "Action-tab.ico" };
         QIcon REFRESH{ m_path + "Actualiser.ico" };
         QIcon HIDE{ m_path + "Action-tab-remove.ico" };
         QIcon MAXIMIZE{ m_path + "Action-window-fullscreen.ico" };
         QIcon MINIMIZE{ m_path + "Action-window-no-fullscreen.ico" };
         QIcon DOCUMENT{ m_path + "App-knode.ico" };
         window() = default;
      };
      //-----------------------------------------------------------------------------------------------//
      struct Q_DECL_EXPORT style : public initial_directory
      {
         QIcon MACINTOSH{ m_path + "mac_colored.ico" };
         QIcon WINDOWS{ m_path + "windows.ico" };
         QIcon MOTIF{ m_path + "App-x.ico" };
         style() = default;
      };
      //-----------------------------------------------------------------------------------------------//
      struct Q_DECL_EXPORT common : public initial_directory
      {
         QIcon FONTS{ m_path + "App-fonts.ico" };
         QIcon OK{ m_path + "ok.png" };
         QIcon APPLOGINMANAGER{ m_path + "App-login-manager.ico" };
         QIcon PASSWORD{ m_path + "password.png" };
         QIcon LOGINMANAGER{ m_path + "Login Manager.png" };
         QIcon HELPINDEX{ m_path + "App-help-index.ico" };
         QIcon BACK{ m_path + "back.png" };
         QIcon FAIL{ m_path + "error.png" };
         QIcon CONTACTS{ m_path + "evolution-contacts.png" };
         QIcon LOGOUT{ m_path + "logout.png" };
         QIcon MAIL{ m_path + "mail.png" };
         QIcon MYDOCUMENTS{ m_path + "mydocuments.png" };
         QIcon RELOAD{ m_path + "Actualiser.ico" };
         QIcon DENIED{ m_path + "Ad Aware.ico" };
         QIcon CANCEL{ m_path + "Action-cancel.ico" };
         QIcon EXCLAMATION{ m_path + "Exclamation.ico" };
         QIcon FAQ{ m_path + "faq.ico" };
         QIcon DOWN{ m_path + "Fleche bas bleue.ico" };
         QIcon UP{ m_path + "Fleche haut bleue.ico" };
         QIcon LEFT{ m_path + "Fleche gauche bleue.ico" };
         QIcon RIGHT{ m_path + "Fleche droite bleue.ico" };
         QIcon INFORMATION{ m_path + "Information.ico" };
         QIcon PUBLIC{ m_path + "Information.ico" };
         QIcon QUESTION{ m_path + "Information.ico" };
         QIcon WORKING{ m_path + "Travaux.ico" };
         QIcon VALID{ m_path + "Validé.ico" };
         QIcon UPDATECACHE{ m_path + "App-cache.ico" };
         QIcon STATISTICS{ m_path + "App-chart.ico" };
         QIcon COINS{ m_path + "coins.ico" };
         QIcon MEDICO{ m_path + "App-virussafe-injection.ico" };
         /**/
         QIcon MINUS{ m_path + "action-remove.ico" };
         QIcon PLUS{ m_path + "action-edit-add.ico" };
         /**/
         QIcon DBSTATUS{ m_path + "Action-db-status.ico" };
         /**/
         QIcon INSERT{ m_path + "insertdoc.png" };
         QIcon CHANGE{ m_path + "App-write.ico" };
         QIcon VIEW{ m_path + "App-xeyes.ico" };
         QIcon IMPORT{ m_path + "App-warehause.ico" };
         QIcon EXPORT{ m_path + "App-navigator.ico" };
         QIcon PRINT{ m_path + "App-kjobviewer-printer.ico" };
         QIcon PRINTPREVIEW{ m_path + "App-kde-print-fax.ico" };
         QIcon PRINTSETUP{ m_path + "Action-file-quick-print.ico" };
         QIcon PRINTPAGE{ m_path + "Action-frame-print.ico" };
         /**/
         QIcon CUT{ m_path + "Blue-Scissors.ico" };
         common() = default;
      };
      //-----------------------------------------------------------------------------------------------//
      struct Q_DECL_EXPORT user : public initial_directory
      {
         QIcon PASSWORD{ m_path + "password.png" }; //Common::PASSWORD;
         QIcon MANAGER{ m_path + "login manager.png" }; //Common::LOGINMANAGER;
         user() = default;
      };
      //-----------------------------------------------------------------------------------------------//
      struct Q_DECL_EXPORT tools : public initial_directory
      {
         QIcon PREFERENCES{ m_path + "App-package-utilities.ico" };
         tools() = default;
      };
      //-----------------------------------------------------------------------------------------------//
      struct Q_DECL_EXPORT help : public initial_directory
      {
         QIcon INDEX{ m_path + "App-help-index.ico" };
         QIcon HELPINDEX{ m_path + "help_index.png" };
         help() = default;
      };
   }; //Icons
   //-----------------------------------------------------------------------------------------------//
   template <typename Object>
   struct Q_DECL_EXPORT icons_impl : public Object
   {
      using value_type = Object;
      using pointer = shared_ptr<icons_impl<value_type>>;
      constexpr icons_impl() :value_type{}
      {
      }
      template <typename IconFileName> QIcon const load(IconFileName const && filename)
      {
         return QIcon{ unicodestring{"1%/%2"}.arg(m_path).arg(std::forward<icon_name_t>(filename)) };
      }
   };
   //-----------------------------------------------------------------------------------------------//
   typedef icons_impl<icons::file> iconsfile_impl;
   typedef icons_impl<icons::edit> iconsedit_impl;
   typedef icons_impl<icons::common> iconscommon_impl;
   typedef icons_impl<icons::help> iconshelp_impl;
   typedef icons_impl<icons::style> iconsstyle_impl;
   typedef icons_impl<icons::tools> iconstools_impl;
   typedef icons_impl<icons::user>  iconsuser_impl;
   typedef icons_impl<icons::window> iconswindow_impl;
   //-----------------------------------------------------------------------------------------------//
}