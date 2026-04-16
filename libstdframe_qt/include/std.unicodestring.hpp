//-----------------------------------------------------------------------------------------------//
// stdx qt abstraction library for cpluplus
//
// Created by Wilson.Souza 2012, 2013, 2014, 2015, 2016, 2017, 2018
// For 
//
// WR Developer
// (c) 2012, 2026, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)

#include <qtcore/qtcore>
#include <memory>

namespace std
{
   using stringlist = QStringList;
   class Q_DECL_EXPORT unicodestring : public QString
   {
   public:
      using uf_list_pointer = unique_ptr<std::stringlist>;
      //
   public:
      unicodestring() = default;
      //-----------------------------------------------------------------------------------------------//
      unicodestring(unicodestring const& value);
      unicodestring(QString const& value);
      unicodestring(const char* value);
      explicit unicodestring(const wchar_t* value);
      explicit unicodestring(const QChar* value);
      unicodestring(const string& value);
      explicit unicodestring(const wstring& value);
      //-----------------------------------------------------------------------------------------------//
      template<typename compare_t> auto const compare(compare_t const&& value) const;
      template<typename bind_value_t> unicodestring& bind(bind_value_t const&& value);
      //-----------------------------------------------------------------------------------------------//
      operator const wstring() const;
      operator const string() const;
      string to_string() const;
      wstring to_wstring() const; /*to_wstring, towstring()*/
      operator const char* () const;
      unicodestring& bind(stringlist const& queue, unicodestring const& sep = ",");
      unicodestring& bind(std::list<int> const& queue, unicodestring const& sep = ",");
      virtual bool empty() const;
      virtual bool find_uf(std::unicodestring const& uf);
      virtual unicodestring::uf_list_pointer get_uf();
   };
}