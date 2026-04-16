//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012
// For many platform
//
// 2WW Engenharia de Sistemas
// (c) 2012, 2026
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.defs.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std::icons
{
   //-----------------------------------------------------------------------------------------------//
   using icons = QIcon;
   struct initial_directory : public QObject
   {
      using pointer = unique_ptr<initial_directory>;
      using value_type = QObject;
      initial_directory() = default;
      unicodestring m_path{ static_cast<QGuiApplication*>(QCoreApplication::instance())->libraryPaths()[0] };
   };

   struct file : public initial_directory
   {
      icons NEW{ m_path + "Action-File-new.ico" };
      icons OPEN{ m_path + "Action-edit.ico" };
      icons CLOSE{ m_path + "App-restart.ico" };
      icons SAVE{ m_path + "App-write.ico" };
      icons PRINT{ m_path + "Action-File-print.ico" };
      icons PRINT_VIEW{ m_path + "Action-frame-print.ico" };
      icons CHANGE_USER{ m_path + "App-user.ico" };
      icons LOGOFF{ m_path + "App-logout.ico" };
      icons EXIT{ m_path + "Action-exit.ico" };
      icons SAVE_AS{ m_path + "Device-zip-mount.ico" };
      icons PRINT_SETUP{ m_path + "Device-print-class.ico" };
      icons PRINT_PAGE_SETUP{ m_path + "Filesystem-folder-print.ico" };
      icons RECENT_FILES{ m_path + "Action-history.ico" };
      file() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct Q_DECL_EXPORT edit : public initial_directory
   {
      icons UNDO{ m_path + "Action-reload.ico" };
      icons CUT{ m_path + "Action-cut.ico" };
      icons PASTE{ m_path + "Action-paste.ico" };
      icons COPY{ m_path + "Action-copy.ico" };
      icons REMOVE{ m_path + "Action-delete.ico" };
      icons FIND_REPLACE{ m_path + "Action-find.ico" };
      icons GOTO{ m_path + "goto.ico" };
      edit() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct window : public initial_directory
   {
      icons CLOSEALL{ m_path + "Action-view-remove.ico" };
      icons CLOSE{ m_path + "Action-remove.ico" };
      icons PREVIOUS{ m_path + "Fleche gauche bleue.ico" };
      icons NEXT{ m_path + "Fleche droite bleue.ico" };
      icons TILE{ m_path + "Action-view-left-right.ico" };
      icons TABBED{ m_path + "Action-tab.ico" };
      icons REFRESH{ m_path + "Actualiser.ico" };
      icons HIDE{ m_path + "Action-tab-remove.ico" };
      icons MAXIMIZE{ m_path + "Action-window-fullscreen.ico" };
      icons MINIMIZE{ m_path + "Action-window-no-fullscreen.ico" };
      icons DOCUMENT{ m_path + "App-knode.ico" };
      window() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct style : public initial_directory
   {
      icons MACINTOSH{ m_path + "mac_colored.ico" };
      icons WINDOWS{ m_path + "windows.ico" };
      icons MOTIF{ m_path + "App-x.ico" };
      style() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct common : public initial_directory
   {
      icons FONTS{ m_path + "App-fonts.ico" };
      icons OK{ m_path + "ok.png" };
      icons APPLOGINMANAGER{ m_path + "App-login-manager.ico" };
      icons PASSWORD{ m_path + "password.png" };
      icons LOGINMANAGER{ m_path + "Login Manager.png" };
      icons HELPINDEX{ m_path + "App-help-index.ico" };
      icons BACK{ m_path + "back.png" };
      icons FAIL{ m_path + "error.png" };
      icons CONTACTS{ m_path + "evolution-contacts.png" };
      icons LOGOUT{ m_path + "logout.png" };
      icons MAIL{ m_path + "mail.png" };
      icons MYDOCUMENTS{ m_path + "mydocuments.png" };
      icons RELOAD{ m_path + "Actualiser.ico" };
      icons DENIED{ m_path + "Ad Aware.ico" };
      icons CANCEL{ m_path + "Action-cancel.ico" };
      icons EXCLAMATION{ m_path + "Exclamation.ico" };
      icons FAQ{ m_path + "faq.ico" };
      icons DOWN{ m_path + "Fleche bas bleue.ico" };
      icons UP{ m_path + "Fleche haut bleue.ico" };
      icons LEFT{ m_path + "Fleche gauche bleue.ico" };
      icons RIGHT{ m_path + "Fleche droite bleue.ico" };
      icons INFORMATION{ m_path + "Information.ico" };
      icons PUBLIC{ m_path + "Information.ico" };
      icons QUESTION{ m_path + "Information.ico" };
      icons WORKING{ m_path + "Travaux.ico" };
      icons VALID{ m_path + "Valid�.ico" };
      icons UPDATECACHE{ m_path + "App-cache.ico" };
      icons STATISTICS{ m_path + "App-chart.ico" };
      icons COINS{ m_path + "coins.ico" };
      icons MEDICO{ m_path + "App-virussafe-injection.ico" };
      /**/
      icons MINUS{ m_path + "action-remove.ico" };
      icons PLUS{ m_path + "action-edit-add.ico" };
      /**/
      icons DBSTATUS{ m_path + "Action-db-status.ico" };
      /**/
      icons INSERT{ m_path + "insertdoc.png" };
      icons CHANGE{ m_path + "App-write.ico" };
      icons VIEW{ m_path + "App-xeyes.ico" };
      icons IMPORT{ m_path + "App-warehause.ico" };
      icons EXPORT{ m_path + "App-navigator.ico" };
      icons PRINT{ m_path + "App-kjobviewer-printer.ico" };
      icons PRINTPREVIEW{ m_path + "App-kde-print-fax.ico" };
      icons PRINTSETUP{ m_path + "Action-file-quick-print.ico" };
      icons PRINTPAGE{ m_path + "Action-frame-print.ico" };
      /**/
      icons CUT{ m_path + "Blue-Scissors.ico" };
      common() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct Q_DECL_EXPORT user : public initial_directory
   {
      icons PASSWORD{ m_path + "password.png" }; //Common::PASSWORD;
      icons MANAGER{ m_path + "login manager.png" }; //Common::LOGINMANAGER;
      user() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct Q_DECL_EXPORT tools : public initial_directory
   {
      icons PREFERENCES{ m_path + "App-package-utilities.ico" };
      tools() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct Q_DECL_EXPORT help : public initial_directory
   {
      icons INDEX{ m_path + "App-help-index.ico" };
      icons HELPINDEX{ m_path + "help_index.png" };
      help() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   template <typename base_t>
      requires derived_from<base_t, initial_directory>
   struct icons_impl : public base_t
   {
      using value_type = base_t;
      using pointer = unique_ptr<icons_impl<value_type>>;
      template<typename icon_t> concept is_filename = requires(icon_t const&& filename)
      {
         {
            is_same_v<icon_t, unicodestring> || is_same_v<icon_t, string>
         };
      };
      constexpr icons_impl() :base_t{}
      {
      }
      icons const load(is_filename const&& filename)
      {
         return icons{ unicodestring{"1%/%2"}
         .arg(value_type::m_path)
            .arg(std::forward<icon_t>(filename)) };
      }
   };
   //-----------------------------------------------------------------------------------------------//
   using iconsfile_impl = icons_impl<file>;
   using iconsedit_impl = icons_impl<edit>;
   using iconscommon_impl = icons_impl<common>;
   using iconshelp_impl = icons_impl<help>;
   using iconsstyle_impl = icons_impl<style>;
   using iconstools_impl = icons_impl<tools>;
   using iconsuser_impl = icons_impl<user>;
   using iconswindow_impl = icons_impl<window>;
   //-----------------------------------------------------------------------------------------------//
}