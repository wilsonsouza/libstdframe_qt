//-----------------------------------------------------------------------------------------------//
// stdx.frame.x86 for Windows
//
// Created by Wilson.Souza 2012, 2018
// For 
//
// WR Developer
// (c) 2012, 2013, 2014, 2015, 2018
//
// Last updated: introduce new features of c++14
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <qtcore/qtcore>
#include <qtgui/qtgui>
#include <qtwidgets/qtwidgets>
#include <QtPrintSupport\qtprintsupport>
#include <typeinfo>
#include <functional>
#include <memory>
#include <ppl.h>
#include <exception>
#include <string>
#include <map>
#include <list>
#include <set>
#include <string>
//-----------------------------------------------------------------------------------------------//
#include <std.unicodestring.hpp>
using namespace Concurrency;
//-----------------------------------------------------------------------------------------------//
#define STD(s)   #s
#define _DISABLED 0
//-----------------------------------------------------------------------------------------------//
namespace std
{
   /**/
   enum class command : uint
   {
      IDDOK = 1,
      IDDCANCEL,
      IDDHELP
   };
   using commands = set<command>;
   //-----------------------------------------------------------------------------------------------//
   enum class wmessages : int
   {
      WM_ICONSIZECHANGED = 1,
      WM_TOOLBUTTONSTYLECHANGED,
      WM_STYLEMODIFIED,
      WM_TREEWIDGET_CURRENTITEMCHANGED,
      WM_TREEWIDGET_ITEMACTIVATED,
      WM_TREEWIDGET_ITEMCHANGED,
      WM_TREEWIDGET_ITEMCLICKED,
      WM_TREEWIDGET_ITEMCOLLAPSED,
      WM_TREEWIDGET_ITEMDOUBLECLICKED,
      WM_TREEWIDGET_ITEMENTERED,
      WM_TREEWIDGET_ITEMEXPANDED,
      WM_TREEWIDGET_ITEMPRESSED,
      WM_TREEWIDGET_ITEMSELECTIONCHANGED,
      WM_TREEWIDGET_UPDATEITEMS,
      WM_LOADDATA
   };
   using wmessages_queue = set<wmessages>;
   //-----------------------------------------------------------------------------------------------//
   namespace window
   {
      enum class mode : uint
      {
         NORMAL = 0x01af,
         MAXIMIZED = 0x02df,
         MINIMIZED = 0x04ef,
         HIDE = 0x08ab,
         FULLSCREEN = 0x8ac
      };
      using modes = set<mode>;
      template<class value_t = mode> requires(is_same_v<value_t, mode>)
         auto operator!= (value_t const& value, value_t const&)
      {
         return(value != mode::NORMAL ||
                value != mode::MAXIMIZED ||
                value != mode::MINIMIZED ||
                value != mode::HIDE ||
                value != mode::FULLSCREEN);
      }

      //window states
      enum class state :uint
      {
         NOSTATE = 0x00000000,
         MINIMIZED = 0x00000001,
         MAXIMIZED = 0x00000002,
         FULLSCREEN = 0x00000004,
         ACTIVE = 0x00000008
      };
      using states = set<state>;
      template<class states_t = state> requires(is_same_v<states_t, state>)
         auto operator!= (states_t const& value, states_t const&)
      {
         return(value != state::NOSTATE ||
                value != state::MINIMIZED ||
                value != state::MAXIMIZED ||
                value != state::FULLSCREEN ||
                value != state::ACTIVE);
      }
      //window Modality
      enum class modality : uint
      {
         NONMODAL = Qt::NonModal,
         WINDOW_MODAL = Qt::WindowModal,
         APPLICATION_MODAL = Qt::ApplicationModal
      };
      using modalities = set<modality>;
      template<class modality_t = modality> requires(is_same_v<modality_t, modality>)
         auto operator!= (modality_t const& value, modality_t const&)
      {
         return(value != modality::NONMODAL ||
                value != modality::WINDOW_MODAL ||
                value != modality::APPLICATION_MODAL);
      }
   }
   //-----------------------------------------------------------------------------------------------//
   namespace version
   {
      Q_DECL_EXPORT unicodestring const __cdecl get_string_version();
      Q_DECL_EXPORT uint32_t const __cdecl get_version();
   };
   //-----------------------------------------------------------------------------------------------//   
   struct settings : public QSettings
   {
      explicit settings(const unicodestring& organization,
                        const unicodestring& application = {},
                        QObject* parent = nullptr) :
         QSettings{ organization, application, parent }
      {
      }
      settings(Scope scope,
               const unicodestring& organization,
               const unicodestring& application = {},
               QObject* parent = nullptr) :
         QSettings{ scope, organization, application, parent }
      {
      }
      settings(Format format,
               Scope scope,
               const unicodestring& organization,
               const unicodestring& application = {},
               QObject* parent = nullptr) :
         QSettings{ format, scope, organization, application, parent }
      {
      }
      settings(const unicodestring& filename,
               Format format,
               QObject* parent = nullptr) :
         QSettings{ filename, format, parent }
      {
      }
      explicit settings(QObject* parent = nullptr) :QSettings{ parent }
      {
      }
   };
   //-----------------------------------------------------------------------------------------------//
   template<typename value_t>
   class libstdframe_exception : public exception
   {
   public:
      explicit libstdframe_exception(value_t const& message) :
         exception{ unicodestring{message}.toStdString().data() }
      {
      }
   };
   //-----------------------------------------------------------------------------------------------//
   template<class Func, typename ...Args> 
      requires(is_function_v<Func>)
      inline bool dispatch_event(Func&& func, Args&&...args)
   {
      static_exception(forward<Func>(func) == nullptr, "parameter <func> is null!");
      return forward<Func>(func)(forward<Args>(args)...);
   }
   //-----------------------------------------------------------------------------------------------//
   template<class TaskGroup, typename Func, typename ...Args>
      requires(is_same_v<TaskGroup, task_group>&& is_function_v<Func>)
   inline auto dispatch_event_by_pplx(TaskGroup&& thread_class,
                                      Func&& func,
                                      Args&&...args)
   {
      static_exception(forward<TaskGroup>(thread_class) == nullptr, "invalid parameter thread_class!");
      static_exception(forward<Func>(func) == nullptr, "parameter func is null!");
      //
      return forward<TaskGroup>(thread_class)->run_and_wait([&]()->auto
      {
         return forward<Func>(func)(forward<Args>(args)...);
      });
   }
   //-----------------------------------------------------------------------------------------------//
   template< typename Value, typename Message>
      requires(is_fundamental_v<Value>)
   inline bool static_exception(Value&& value, Message&& message)
   {
      if (forward<Value>(value) == true)
      {
         throw libstdframe_exception{ forward<Message>(message) };
      }
      return true;
   }
}
/*eof*/
