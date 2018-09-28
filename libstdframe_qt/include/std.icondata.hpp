//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013, 2014, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013, 2014
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.defs.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   namespace icon_data
   {
      struct header
      {
         long offset{ 0L };
         wchar_t id{ 0 };
         long size{ 0L };
         void * data{ nullptr };
      };

      struct data
      {
         long offset{ 0L };
         char * name{ nullptr };
         long size{ 0L };
         void * buffer{ nullptr };
      };
   }
   /* abstract class to resource icon data object  icondata */
   class Q_DECL_EXPORT icondata : public QObject
   {
   public:
      using pointer = shared_ptr<icondata>;
      /**/
   public:
      explicit icondata() = default; /**/
      template<typename ResourceName, typename ResourcePath>
      explicit icondata(typename ResourceName && resource_name, 
                        typename ResourcePath && resource_path) :
         QObject{},
         m_resource_name{ forward<typename ResourceName>(resource_name) },
         m_resource_path{ forward<typename ResourcePath>(resource_path) },
         m_header{ new icon_data::header{} },
         m_data{ new icon_data::data{} },
         m_file_handle{ new QFile{} },
         m_datastream{ new QDataStream{} },
         m_list_resource_names{ new stringlist{} }
      {
      }
      ~icondata() override = default;
      virtual bool const build() = 0;
      /**/
   protected:
      shared_ptr<icon_data::header> m_header{ nullptr };
      shared_ptr<icon_data::data> m_data{ nullptr };
      shared_ptr<QFile> m_file_handle{ nullptr };
      shared_ptr<QDataStream> m_datastream{ nullptr };
      unicodestring m_resource_name{};
      unicodestring m_resource_path{};
      shared_ptr<stringlist> m_list_resource_names{};
   };
}