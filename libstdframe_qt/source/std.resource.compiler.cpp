//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.resource.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   namespace resource
   {
      bool const compiler::create_resource_file(unicodestring const & name)
      {
         this->setFile(m_file);
         this->setFileName(m_file);
         //
         static_exception(QFile::exists(), unicodestring{ "File %1 already exists!" }.arg(name));
         static_exception(!QFile::open(QIODevice::ReadWrite),
                          unicodestring{ "Can´t possible create file %1!" }.arg(name));
         //
         auto temp = new header{};
         auto base = new header{ "WR Resource File", temp->get_size(), temp->get_id(), QDate{} };
         //
         static_exception(!base->write(this), "Write failure!");
         return true;
      }
      //-----------------------------------------------------------------------------------------------//
      compiler::fileinfo_list_value const compiler::get_fileinfo_list()
      {
         auto filelist = fileinfo_list_value{};
         //
         for_each_loop(begin(), end(), [&](auto const & fileinfo)
         {
            filelist.push_back(fileinfo.second);
         });
         return filelist;
      }
      //-----------------------------------------------------------------------------------------------//
      QDataStream const * compiler::get_buffer()
      {
         return m_datastream;
      }
      //-----------------------------------------------------------------------------------------------//
   }
}