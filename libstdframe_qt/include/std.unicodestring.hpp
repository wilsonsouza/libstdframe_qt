//-----------------------------------------------------------------------------------------------//
// stdx.frame.x86 for Windows
//
// Created by Wilson.Souza 2012, 2013, 2014, 2015, 2016, 2017, 2018
// For 
//
// WR Developer
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)

#include <qtcore/qtcore>
#include <memory>

namespace std
{
   typedef QStringList stringlist;
   class Q_DECL_EXPORT unicodestring : public QString
   {
   public:
      using uf_list_pointer = shared_ptr<stringlist>;
      //
   public:
      unicodestring() = default;
      //-----------------------------------------------------------------------------------------------//
      template <typename string_type_t> unicodestring(typename string_type_t && value) :
         QString{ forward<typename string_type_t>(value) }
      {
      }
      //-----------------------------------------------------------------------------------------------//
      template <typename compare_t> bool const compare(typename compare_t && value) const
      {
         return QString::compare(forward<typename compare_t>(value)) == 0;
      }
      //-----------------------------------------------------------------------------------------------//
      template<typename bind_value_t> unicodestring & bind(typename bind_value_t && value)
      {
         this->arg(forward<typename bind_value_t>(value));
         return *this;
      }
      //-----------------------------------------------------------------------------------------------//
      operator wstring const () const;
      operator const string() const;
      string to_string() const;
      wstring to_wstring() const; /*to_wstring, towstring()*/
      operator char const *() const;
      unicodestring & bind(stringlist const & queue, unicodestring const & sep = ",");
      unicodestring & bind(std::list<int> const & queue, unicodestring const & sep = ",");
      virtual bool empty() const;
      virtual bool find_uf(std::unicodestring const & uf);
      virtual unicodestring::uf_list_pointer get_uf();
   };
}