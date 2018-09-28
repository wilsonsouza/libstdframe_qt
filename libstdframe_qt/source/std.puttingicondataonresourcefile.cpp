//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.putting_icondata_on_resourcefile.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   putting_icondata_on_resourcefile::putting_icondata_on_resourcefile(
      unicodestring const & resource_name,
      unicodestring const & resource_path) :
      icondata{ resource_name, resource_path }
   {
   }
   //-----------------------------------------------------------------------------------------------//
   bool const putting_icondata_on_resourcefile::build()
   {
      /* abort process if variables empty */
      static_exception(m_resource_name.empty() || m_resource_path.empty(), "name or path cann´t be empty!");

      /* verify archive */
      auto fileinfo = shared_ptr<QFileInfo>{ new QFileInfo{} };
      auto dir = shared_ptr<QDir>{ new QDir{m_resource_path} };
      //
      fileinfo->setFile(*dir, m_resource_name);
      /* file already exists abort process */
      static_exception(fileinfo->exists(), unicodestring{ "File %1 already exists!" }.bind(fileinfo->fileName()));
      dir->setPath(m_resource_path);
      dir->setFilter(QDir::Files);
      /**/
      auto filelist = dir->entryInfoList(QDir::Files, QDir::Name);
      auto filename = unicodestring{ "%1/%2" }.bind(m_resource_path).bind(m_resource_name);
      /**/
      m_file_handle = shared_ptr<QFile>{ new QFile{filename} };
      m_datastream = shared_ptr<QDataStream>{ new QDataStream{ m_file_handle.get() } };
      /**/
      /* open resource file */
      static_exception(m_file_handle->open(QIODevice::ReadWrite) == false,
                       unicodestring{ "Cann´t possible open file %1" }.bind(m_file_handle->fileName()));
      /* get file list */
      auto listnames = shared_ptr<stringlist>{ new stringlist{} };
      static_exception(filelist.count() == 0, "List of files is empty!");

      /* set data */
      m_header->id = QDataStream::Qt_1_0 | 0 | QDataStream::Qt_1_0 | 0;

      /*set file version */
      m_datastream->setVersion(QDataStream::Qt_5_1);
      for_each(filelist.begin(), filelist.end(), [=](auto const & finfo)
      {
         listnames->push_back(finfo.fileName());
      });
      /**/
      auto names = listnames->join("/");
      m_header->offset = sizeof(*m_header);
      m_header->size = names.length();
      /**/
      *m_datastream
         << m_header->offset
         << m_header->id
         << m_header->size
         << names
         << "\n";
      //
      static_exception(m_datastream->status() == QDataStream::WriteFailed, "Write failed detected!");
      /**/
      for_each_loop(filelist.begin(), filelist.end(), [&](QFileInfo const & finfo)
      {
         auto in = shared_ptr<QFile>{ new QFile{finfo.fileName()} };
         static_exception(in->open(QIODevice::ReadOnly) == false,
                          unicodestring{ "Cann´t open file %1!" }.bind(finfo.fileName()));
         /* write buffer stream */
         *m_datastream
            << long{ sizeof(*m_data) }
            << finfo.fileName()
            << finfo.size()
            << in->readAll().data()
            << "\n";
         /* notify */
         dispatch_event(on_notify, addressof(finfo), m_datastream->status());
      });
      return true;
   }
   //-----------------------------------------------------------------------------------------------//
}
