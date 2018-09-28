//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.layouts.hpp>
#include <std.button.hpp>
#include <std.progressbar.hpp>
#include <std.captions.hpp>
#include <std.icons.hpp>
#include <std.resource.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   namespace resource
   {
      resource_impl::resource_impl(widget * owner, unicodestring const & name) :
         widget{ owner, name, 0 }
      {
         m_horizontal_lay = new std::horizontal_box{ this, unicodestring{} };
         m_progress_bar = new std::progressbar{ this };
         m_cancel = new std::button{ this, std::captions::common{}.CANCEL, icons::common{}.CANCEL };
         m_horizontal_lay->addWidget(m_cancel);
         m_horizontal_lay->addWidget(m_progress_bar);
      }
      //-----------------------------------------------------------------------------------------------//
      resource_impl * resource_impl::process(compiler const & compiler_value)
      {
         auto addr = dynamic_cast<compiler *>(&const_cast<compiler &>(compiler_value));
         //
         static_exception(addr->QFile::fileName().isEmpty(),
                          "Resource file identification isn´t defined!");
         //
         auto dir = shared_ptr<QDir>{ new QDir(addr->m_path, addr->m_extension) };
         auto finfo = dir->entryInfoList();
         //
         for_each(finfo.cbegin(), finfo.cend(), [=](QFileInfo const & fileinfo)
         {
            auto current_name = fileinfo.filePath() + "/" + fileinfo.fileName();
            auto in = make_shared<QFile>(new QFile{ current_name });
            //
            if (in->open(QIODevice::ReadOnly))
            {
               auto bytes = in->read(fileinfo.size());
               //
               if (bytes.length())
               {
                  static_exception(std::resource::resource_data{ &bytes }.write(in.get()) == false,
                                   unicodestring{ "Failure to write operation of file %1!" }.
                                   bind(in->fileName()));
               }
            }
            else
            {
               static_exception(true,
                                unicodestring{ "Isn´t was possible access to file %1!" }.
                                bind(fileinfo.fileName()));
            }
         });
         return this;
      }
      //-----------------------------------------------------------------------------------------------//
      resource_impl * resource_impl::load(compiler const & compiler_value)
      {
         auto addr = dynamic_cast<compiler *>(&const_cast<compiler &>(compiler_value));
         //
         addr->setFileName(addr->m_file);
         addr->setFile(addr->m_file);
         //
         static_exception(!addr->QFile::exists(), unicodestring{ "File %1 not exists!" }.arg(addr->m_file));
         static_exception(!addr->open(QIODevice::ReadWrite),
                          unicodestring{ "Error, isn´t possible access file %1!" }.arg(addr->m_file));
         //
         addr->clear();
         static_exception(!header{}.read(addr), "Failure reading of address!");
         return this;
      }
      //-----------------------------------------------------------------------------------------------//
      QPixmap const resource_impl::find(unicodestring const & name)
      {
         return QPixmap{};
      }
      //-----------------------------------------------------------------------------------------------//
   }
}