//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.gettingicondataonresourcefile.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   bool const gettingicondataonresourcefile::build()
   {
      auto name = unicodestring{ "%1/%2" }.arg(m_resource_path).arg(m_resource_name);

      /* abort process if variables empty */
      if (m_resource_name.empty() || m_resource_path.empty())
      {
         return false;
      }
      /* verify archive */
      auto file_info = shared_ptr<QFileInfo>{ new QFileInfo() };
      auto dir = shared_ptr<QDir>{ new QDir{m_resource_path} };
      //
      file_info->setFile(*dir, m_resource_name);
      /* file already exists abort process */
      if (!file_info->exists())
      {
         throw exception{ unicodestring{"File %1 doesn´t exists!"}.
            arg(file_info->fileName()).toStdString().data() };
      }
      //
      dir->setPath(m_resource_path);
      dir->setFilter(QDir::Files);
      //
      m_file_handle = shared_ptr<QFile>{ new QFile{name} };
      m_datastream = shared_ptr<QDataStream>{ new QDataStream{m_file_handle.operator->()} };
      //
      /* open resource file */
      if (!m_file_handle->open(QIODevice::ReadOnly))
      {
         throw exception{ unicodestring{"Can´t open file %1!"}.
            arg(m_file_handle->fileName()).toStdString().data() };
      }
      //
      m_data = shared_ptr<icon_data::data>{ new icon_data::data{} };
      m_header = shared_ptr<icon_data::header>{ new icon_data::header{} };
      //
      m_data->offset = 0;
      m_header->offset = 0;
      //
      while (m_datastream->atEnd())
      {
         if (m_header->offset == 0)
         {
            m_datastream->readRawData(reinterpret_cast<char *>(&m_header->offset), sizeof(m_header->offset));
            m_datastream->readRawData(reinterpret_cast<char *>(&m_header->id), sizeof(m_header->id));
            m_datastream->readRawData(reinterpret_cast<char *>(&m_header->size), sizeof(m_header->size));
            /* get string buffer */
            auto buffer = unicodestring{};
            *m_datastream >> buffer;
            /* assign buffer on list */
            *m_list_resource_names = buffer.split("/");
            /* notify client */
            dispatch_event(on_notify, nullptr, m_datastream->status());
         }
         /**/
         m_datastream->readRawData(reinterpret_cast<char *>(&m_data->offset), sizeof(m_data->offset));
         name.clear();
         *m_datastream >> name;
         m_datastream->readRawData(reinterpret_cast<char *>(&m_data->size), sizeof(m_data->size));

         auto buffer = unicodestring{};
         *m_datastream >> buffer;

         auto f = shared_ptr<QFile>{ new QFile{name } };
         //
         if (!f->exists())
         {
            if (!f->open(QIODevice::ReadWrite))
            {
               dispatch_event(on_notify, nullptr, QDataStream::WriteFailed);
               continue;
            }

            /* write icon on disk */
            auto d = shared_ptr<QDataStream>{ new QDataStream{f.operator->()} };
            *d << buffer;

            /* notify */
            dispatch_event(on_notify, nullptr, d->status());
         }
      }
      return true;
   }
   //-----------------------------------------------------------------------------------------------//
}