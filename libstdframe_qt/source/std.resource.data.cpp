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
      //-----------------------------------------------------------------------------------------------//
      resource_data::resource_data() :m_buffer{ new QByteArray{} }
      {
      }
      //-----------------------------------------------------------------------------------------------//
      resource_data::resource_data(QByteArray const * buffer) : m_buffer{ new QByteArray{} }
      {
         static_exception(buffer == nullptr, "Parameter invalid or null!");
         m_buffer->append(buffer->data());
      }
      //-----------------------------------------------------------------------------------------------//
      resource_data::~resource_data()
      {
         delete m_buffer;
      }
      //-----------------------------------------------------------------------------------------------//
      resource_data * resource_data::set_data(QByteArray const * buffer)
      {
         assert(buffer == nullptr);
         m_buffer->clear();
         m_buffer->append(buffer->data());
         return this;
      }
      //-----------------------------------------------------------------------------------------------//
      bool const resource_data::write(QFile * handle)
      {
         static_exception(handle == nullptr, "Parameter handle can´t be null!");
         static_exception(handle->write(*m_buffer) != qint64(m_buffer->length()), "Write buffer failure!");
         return true;
      }
      //-----------------------------------------------------------------------------------------------//
      bool const resource_data::read(QFile * handle, qint64 offset)
      {
         static_exception(handle == nullptr, "Parameter handle can´t be null!");
         static_exception(handle->read(offset).length() != offset,
                          unicodestring{ "Read file %1 failure!" }.arg(handle->fileName()));
         return true;
      }
      //-----------------------------------------------------------------------------------------------//
      QByteArray const * resource_data::get_data() const
      {
         return m_buffer;
      }
   }
}
