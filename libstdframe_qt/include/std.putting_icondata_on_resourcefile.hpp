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
   class Q_DECL_EXPORT putting_icondata_on_resourcefile : public icondata
   {
   public:
      putting_icondata_on_resourcefile() = default; /* starter inline object class */
      explicit putting_icondata_on_resourcefile(unicodestring const & resource_name,
                                                unicodestring const & resource_path = "./");
      virtual ~putting_icondata_on_resourcefile() override = default;
      virtual bool const build();
   public:
      function<bool(QFileInfo const * fileinfo, QDataStream::Status status)> on_notify{ nullptr };
   };
};