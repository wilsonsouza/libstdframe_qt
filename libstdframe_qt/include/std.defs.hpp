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
   enum Command : int
   {
      IDDOK = 1,
      IDDCANCEL,
      IDDHELP
   };
   //-----------------------------------------------------------------------------------------------//
   enum WMessages : int
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
   //-----------------------------------------------------------------------------------------------//
   namespace version
   {
      Q_DECL_EXPORT unicodestring const __cdecl get_string_version();
      Q_DECL_EXPORT uint32_t const __cdecl get_version();
   };
   //-----------------------------------------------------------------------------------------------//
   template< typename Iterator, typename Lambda,
      typename enable_if<is_arithmetic<typename Iterator>::value, typename Iterator>::type = 0>
      inline auto integral_find_if(typename Iterator first,
                                   typename Iterator last,
                                   typename Lambda lambda)
   {
      auto start = first;
      //
      for (; start != last; start++)
      {
         if (lambda(start))
         {
            return start;
         }
      }
      return last;
   }
   //-----------------------------------------------------------------------------------------------//
   template<typename Iterator, typename Lambda>
   inline void for_each_loop(typename Iterator first, typename Iterator last, typename Lambda lambda)
   {
      auto start = first;
      //
      for (; start != last; start++)
      {
         lambda(*start);
      }
   }
   //-----------------------------------------------------------------------------------------------//
   template<typename Iterator, typename Lambda,
      typename enable_if<is_arithmetic<typename Iterator>::value, typename Iterator>::type = 0>
      inline auto for_each_integral(typename Iterator first,
                                    typename Iterator last,
                                    typename Lambda lambda)
   {
      auto start = first;
      //
      for (; start != last; start++)
      {
         lambda(start);
      }
   }
   //-----------------------------------------------------------------------------------------------//
   struct settings : public QSettings
   {
      explicit settings(const unicodestring &organization,
                        const unicodestring &application = unicodestring{}, QObject *parent = nullptr) :
         QSettings{ organization, application, parent }
      {
      }
      settings(Scope scope, const unicodestring &organization,
               const unicodestring &application = unicodestring{}, QObject *parent = nullptr) :
         QSettings{ scope, organization, application, parent }
      {
      }
      settings(Format format, Scope scope, const unicodestring &organization,
               const unicodestring &application = unicodestring(), QObject *parent = nullptr) :
         QSettings{ format, scope, organization, application, parent }
      {
      }
      settings(const unicodestring &filename, Format format, QObject *parent = nullptr) :
         QSettings{ filename, format, parent }
      {
      }
      explicit settings(QObject *parent = nullptr) :QSettings{ parent }
      {
      }
   };
   //-----------------------------------------------------------------------------------------------//
   class libstdframe_exception : public exception
   {
   public:
      explicit libstdframe_exception(unicodestring const & message) : exception{ message.toStdString().data() }
      {
      }
      explicit libstdframe_exception(char const * message) :exception{ message }
      {
      }
   };
   //-----------------------------------------------------------------------------------------------//
   template<class Func, typename ...Args>
   inline bool dispatch_event(typename Func && func, Args&&...args)
   {
      static_exception(forward<typename Func>(func) == nullptr, "parameter func is null!");
      static_exception(!is_function<typename Func>::value, "func parameter isn´t an function!");
      return forward<typename Func>(func)(forward<Args>(args)...);
   }
   //-----------------------------------------------------------------------------------------------//
   template<class TaskGroup, typename Func, typename ...Args>
   inline auto dispatch_event_by_pplx(typename TaskGroup && thread_class,
                                      typename Func && func,
                                      Args&&...args)
   {
      static_exception(!is_same<typename TaskGroup, task_group>::value, "Class isn´t task_group!");
      static_exception(forward<typename TaskGroup>(thread_class) == nullptr, "invalid parameter thread_class!");
      static_exception(forward<typename Func>(func) == nullptr, "parameter func is null!");
      static_exception(!is_function<typename Func>::value, "func parameter isn´t an function!");
      //
      return forward<typename TaskGroup>(thread_class)->run_and_wait([&]()->auto
      {
         return forward<typename Func>(func)(forward<Args>(args)...);
      });
   }
   //-----------------------------------------------------------------------------------------------//
   template< typename Value, typename Message,
      typename enable_if<is_fundamental<typename Value>::value, typename bool>::type = 0>
      inline bool static_exception(typename Value && value, typename Message && message)
   {
      if (forward<typename Value>(value) == true)
      {
         throw libstdframe_exception{ forward<typename Message>(message) };
      }
      return true;
   }
   //-----------------------------------------------------------------------------------------------//
   template<class Source, class Func, typename ...Params>
   inline auto invoke_method(typename Source *&& source, typename Func && func, Params&& ...params)
   {
      static_exception(forward<typename Source>(source) == nullptr, "parameter source is null!");
      static_exception(forward<typename Func>(func) == nullptr, "parameter func is null!");
      static_exception(!is_function<typename Func>::value, "func parameter isn´t an function!");
      //
      return forward<typename Source>(source)->forward<typename Func>(func)(forward<Params>(params)...);
   }
}
/*eof*/
