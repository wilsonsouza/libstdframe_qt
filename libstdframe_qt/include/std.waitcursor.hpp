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
   class Q_DECL_EXPORT waitcursor : public QCursor
   {
   public:
      template <typename control_t>  explicit waitcursor(control_t *& source) :
         QCursor{ Qt::WaitCursor },
         m_source{ forward<control_t>(source) }
      {
         if (m_source)
         {
            m_old_cursor = m_source->cursor();
            m_source->setCursor(*this);
         }
      }
      ~waitcursor()
      {
         restore();
      }
      virtual waitcursor & wait()
      {
         if (m_source)
         {
            m_source->setCursor(Qt::WaitCursor);
         }
         else
         {
            QApplication::setOverrideCursor(*this);
         }
         return *this;
      }
      virtual waitcursor & restore()
      {
         if (m_source)
         {
            m_source->setCursor(m_old_cursor);
         }
         else
         {
            QApplication::restoreOverrideCursor();
         }
         return *this;
      }
   private:
      QWidget * m_source{ nullptr };
      QCursor m_old_cursor{ Qt::ArrowCursor };
   };
}