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
namespace std
{
   class Q_DECL_EXPORT timer : public QTimer
   {
   public:
      using pointer = shared_ptr<timer>;
      //
   public:
      explicit timer(QObject * owner, int interval_value, unicodestring const & name = unicodestring{}) :
         QTimer{ owner }
      {
         setObjectName(name);
         setInterval(interval_value);
      }
      ~timer() override
      {
         stop();
      }
      /**/
   private:
      void timerEvent(QTimerEvent * e) override
      {
         if (e->timerId() == this->timerId())
         {
            e->accept();
            static_cast<QGuiApplication *>(QCoreApplication::instance())->sendEvent(parent(), e);
            return;
         }
         return QTimer::timerEvent(e);
      }
   };
}


