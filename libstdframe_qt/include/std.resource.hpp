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
#include <std.widget.hpp>
#include <std.progressbar.hpp>
#include <std.button.hpp>
#include <std.layouts.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   namespace resource
   {
      class Q_DECL_EXPORT compiler;
      class Q_DECL_EXPORT icon;
      class Q_DECL_EXPORT resource_impl : public widget
      {
         Q_OBJECT
      public:
         friend class compiler;
      public:
         explicit resource_impl(widget * owner = nullptr, unicodestring const & name = unicodestring{});
         virtual resource_impl * process(compiler const & name);
         virtual resource_impl * load(compiler const & name);
         virtual QPixmap const find(unicodestring const & name);
         /**/
      protected:
         QPixmap * m_current_resource{ nullptr };
         progressbar * m_progress_bar{ nullptr };
         button * m_cancel{ nullptr };
         horizontal_box * m_horizontal_lay{ nullptr };
      };

      class Q_DECL_EXPORT icon : public QIcon, public QObject
      {
      public:
         template <typename object_t> icon(object_t && obj) :
            QIcon{ forward<object_t>(obj) }
         {
         }
         ~icon() override = default;
      };
      //-----------------------------------------------------------------------------------------------//
      class Q_DECL_EXPORT header : public QObject
      {
      public:
         enum class header_id
         {
            IDD_EOF = 0xffee,
            IDD_ID = 0xaaff
         };
         friend class compiler;
      public:
         header();
         explicit header(unicodestring const & name,
                         long long const & size,
                         header::header_id const & id,
                         QDate const & date);
         bool const write(QFile * handle);
         bool const read(QFile * handle);

         QDate get_date() const
         {
            return m_date;
         }
         unicodestring get_name() const
         {
            return m_name;
         }
         header::header_id const get_id() const
         {
            return m_id;
         }
         long long get_size() const
         {
            return m_size;
         }
         //
      protected:
         header_id m_id{};
         long long m_size{ 0L };
         QDate m_date{};
         unicodestring m_name{};
      };
      //-----------------------------------------------------------------------------------------------//
      class Q_DECL_EXPORT resource_data : public QObject
      {
      public:
         resource_data();
         explicit resource_data(QByteArray const * buffer);
         ~resource_data() override;
         resource_data * set_data(QByteArray const * buffer);
         bool const write(QFile * handle);
         bool const read(QFile * handle, qint64 offset);
         QByteArray const * get_data() const;
         //
      protected:
         QByteArray * m_buffer{ nullptr };
      };
      //-----------------------------------------------------------------------------------------------//      
      class Q_DECL_EXPORT information : public QFileInfo, public QFile
      {
      public:
         information() = default;
         template<typename file_t> information(file_t const && filename) :
            QFileInfo{ forward<name_t>(filename) },
            QFile{ forward<name_t>(filename) }
         {
         }
         template<typename path_t, typename file_t, typename extension_t>
         information(path_t const && pathname,
                     file_t const && filename,
                     extension_t const && extension) : QFileInfo{}, QFile{},
            m_path{ forward<path_t>(pathname) },
            m_file{ forward<file_t>(filename) },
            m_extension{ forward<extension_t>(extension) }
         {
         }
         template<typename path_t> information & set_path(path_t const && name)
         {
            m_path = forward<path_t>(name);
         }
         template<typename file_t> information & set_file(typename file_t const && file)
         {
            m_file = forward<typename file_t>(file);
         }
         template<typename extension_t> information & set_extension(typename extension_t const && extension)
         {
            m_extension = forward<typename extensiont_t>(extension);
         }
         unicodestring const & get_path() const
         {
            return m_path;
         }
         unicodestring const & get_file() const
         {
            return m_file;
         }
         unicodestring const & get_extension() const
         {
            return m_extension;
         }
         //
      protected:
         unicodestring m_path{};
         unicodestring m_file{};
         unicodestring m_extension{};
      };
      //-----------------------------------------------------------------------------------------------//
      class Q_DECL_EXPORT compiler : public information, public map<unicodestring, QFileInfo>
      {
      public:
         friend class resource_impl;
         using fileinfo_mapped_value = std::map<key_type, mapped_type>;
         using fileinfo_list_value = list<QFileInfo>;
         //
      public:
         compiler() : information{}, fileinfo_mapped_value{}, m_datastream{ new QDataStream{} }{}
         template<typename path_t, typename file_t, typename extension_t>
         compiler(path_t const && path, file_t const && file, extension_t const && extension):
            information{forward<path_t>(path), forward<file_t>(file), forward<extension_t>(extension)},
            mapped_value{}, m_datastream{ new QDataStream{} }{}
         ~compiler() override = default;
         virtual bool const create_resource_file(unicodestring const & name);
         virtual fileinfo_list_value const get_fileinfo_list();
         virtual QDataStream const * get_buffer();
         //
      protected:
         QDataStream * m_datastream{ nullptr };
      };
   }
}