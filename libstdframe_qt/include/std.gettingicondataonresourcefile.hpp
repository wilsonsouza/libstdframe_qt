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
#include <std.icondata.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT gettingicondataonresourcefile : public icondata
   {
   public:
      gettingicondataonresourcefile() = default;
      /* starter inline object class */
      explicit gettingicondataonresourcefile(unicodestring const & resource_name,
                                             unicodestring const & resource_path = "./") :
         icondata{ resource_name, resource_path }
      {
      }
      ~gettingicondataonresourcefile() override = default;
      virtual bool const build();
      //
   public:
      function<bool(QFileInfo * file_info, QDataStream::Status data_stream_status)> on_notify{ nullptr };
   };
}