//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.generate_container_mapper.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   template <class T>
   class Q_DECL_EXPORT search_internal_container_mapper : protected QObject
   {
   public:
      typedef value_type = T;
      typedef widget_mapper = map<unicodestring, T *>;

   public:
      search_internal_container_mapper(shared_ptr<generate_container_mapper<value_type, widget_mapper>> const & obj)
      {
         m_generate_container_mapper = shared_ptr<generate_container_mapper<T, widget_mapper>>
         {
            new generate_container_mapper<value_type, widget_mapper>{obj}
         };
      }
      ~search_internal_container_mapper() override = default;
      search_internal_container_mapper<T> & search(unicodestring const & name)
      {
         setObjectName(name);
         return *this;
      }
      value_type * get_result() const
      {
         return m_generate_container_mapper->get_result()->value(objectName());
      }
      search_internal_container_mapper * set_enabled(unicodestring const & id,
                                                     bool const & enabled,
                                                     bool const & all = false)
      {
         if (all)
         {
            auto auto_mapper = m_generate_container_mapper->do_mapper();
            auto const & queue = shared_ptr<generate_container_mapper<value_type, widget_mapper>::map_value>
            {
               new generate_container_mapper<value_type, widget_mapper>::map_value{auto_mapper}
            };
            //
            if (queue->empty())
            {
               return this;
            }
            //
            parallel_for(queue->begin(), queue->end(), [=](auto const & value)
            {
               value.second->setEnabled(enabled);
            });
         }
         else
         {
            search(id)->get_result()->setEnabled(enabled);
         }
         return this;
      }
   protected:
      shared_ptr<generate_container_mapper<T, widget_mapper>> m_generate_container_mapper{nullptr};
   };
}