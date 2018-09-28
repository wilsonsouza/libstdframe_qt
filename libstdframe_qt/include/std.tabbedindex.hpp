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
   class Q_DECL_EXPORT tabbedindex : public shared_ptr<list<QWidget *>>
   {
   public:
      typedef shared_ptr<list<QWidget *>> pointer;
   public:
      explicit tabbedindex(QTabWidget * tabbed, uint const & index) :
         pointer{ new list<QWidget *>{} },
         m_tabbed{ tabbed },
         m_index{ index }
      {
      }
      //-----------------------------------------------------------------------------------------------//
      int get_index() const
      {
         return m_index;
      }
      //-----------------------------------------------------------------------------------------------//
      tabbedindex * set_index(uint const & index)
      {
         m_index = index;
         return this;
      }
      //-----------------------------------------------------------------------------------------------//
      bool is_enabled()
      {
         if (m_tabbed != nullptr)
         {
            return m_tabbed->isTabEnabled(m_index);
         }
         return false;
      }
      //-----------------------------------------------------------------------------------------------//
      tabbedindex * set_enabled(bool const & enabled)
      {
         if (m_tabbed)
         {
            m_tabbed->setTabEnabled(m_index, enabled);
         }
         return this;
      }
      //-----------------------------------------------------------------------------------------------//
      tabbedindex * set_enabled_all(bool const & enabled)
      {
         for (auto i = 0; i < m_tabbed->count(); i++)
         {
            m_tabbed->setTabEnabled(i, enabled);
         }
         return this;
      }
      //-----------------------------------------------------------------------------------------------//
      tabbedindex * update()
      {
         auto & p = pointer{ *this };
         {
            p->clear();

            for (auto i = 0; i < m_tabbed->count(); ++i)
            {
               p->push_back(m_tabbed->widget(i));
            }
         }
         return this;
      }
      //
   protected:
      uint m_index{ 0u };
      QTabWidget * m_tabbed{ nullptr };
   };
}