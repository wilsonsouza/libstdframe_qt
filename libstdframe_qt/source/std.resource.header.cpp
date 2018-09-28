//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012
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
      header::header() :QObject{}
      {
         m_date = (new QDate())->currentDate();
         m_name = unicodestring();
         m_id = header_id::IDD_ID;
         m_size = sizeof(*this);
      }
      //-----------------------------------------------------------------------------------------------//
      header::header(unicodestring const & name,
                     long long const & size,
                     header::header_id const & id,
                     QDate const & date) :
         QObject{}, m_name{ name }, m_size{ size }, m_id{ id }, m_date{ date }
      {
      }
      //-----------------------------------------------------------------------------------------------//
      bool const header::write(QFile * handle)
      {
         auto buffer = QByteArray{}.append(reinterpret_cast<char *>(header_id::IDD_EOF));
         static_exception(handle->write(buffer) != buffer.length(),
                          unicodestring{ "File %1 write failure!" }.bind(handle->fileName()));
         return true;
      }
      //-----------------------------------------------------------------------------------------------//
      bool const header::read(QFile * handle)
      {
         auto buffer = handle->read(qint64(sizeof(*this)));
         static_exception(buffer.length() != sizeof(*this),
                          unicodestring{ "File %1 with offset invalid!" }.arg(handle->fileName()));
         static_exception(m_id != header_id::IDD_ID,
                          unicodestring{ "Invalid file %1!" }.arg(handle->fileName()));
         return true;
      }
   }
}