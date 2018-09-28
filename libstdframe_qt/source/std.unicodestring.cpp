//-----------------------------------------------------------------------------------------------//
// stdx.frame.x86 for Windows
//
// Created by Wilson.Souza 2012, 2013, 2014, 2015, 2016, 2017, 2018
// For 
//
// WR Developer
// (c) 2012, 2013, 2014, 2015, 2016, 2017, 2018
//-----------------------------------------------------------------------------------------------//
#include <std.unicodestring.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   unicodestring::operator wstring const () const
   {
      return toStdWString();
   }
   //-----------------------------------------------------------------------------------------------//
   unicodestring::operator const string() const
   {
      return toLatin1().data();
   }
   //-----------------------------------------------------------------------------------------------//
   string unicodestring::to_string() const
   {
      return toLatin1().data();
   }
   //-----------------------------------------------------------------------------------------------//
   wstring unicodestring::to_wstring() const /*to_wstring, towstring()*/
   {
      return toStdWString();
   }
   //-----------------------------------------------------------------------------------------------//
   unicodestring::operator char const * () const
   {
      return this->to_string().data();
   }
   //-----------------------------------------------------------------------------------------------//
   unicodestring & unicodestring::bind(stringlist const & queue, unicodestring const & sep)
   {
      this->arg(queue.join(sep));
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   unicodestring & unicodestring::bind(list<int> const & queue, unicodestring const & sep)
   {
      auto s = shared_ptr<stringlist>{ new stringlist { } };
      for_each(queue.cbegin(), queue.cend(), [=](int value)
      {
         s->push_back(unicodestring{ "%1" }.arg(value));
      });
      this->arg(s->join(sep));
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   bool unicodestring::empty() const
   {
      return isEmpty();
   }
   //-----------------------------------------------------------------------------------------------//
   bool unicodestring::find_uf(std::unicodestring const & uf)
   {
      auto p = get_uf();
      auto success = find_if(p->begin(), p->end(), [=](unicodestring const & value)
      {
         return value.toUpper().compare(uf.toUpper()) == 0;
      });
      return bool{ success != p->end() };
   }
   //-----------------------------------------------------------------------------------------------//
   unicodestring::uf_list_pointer unicodestring::get_uf()
   {
      std::stringlist uf
      {
         "AC",
         "AL",
         "AP",
         "AM",
         "BA",
         "CE",
         "DF",
         "ES",
         "GO",
         "MA",
         "MT",
         "MS",
         "MG",
         "PR",
         "PB",
         "PA",
         "PE",
         "PI",
         "RJ",
         "RN",
         "RS",
         "RO",
         "RR",
         "SC",
         "SE",
         "SP",
         "TO"
      };
      return make_shared<stringlist>(uf);
   }
}
//-----------------------------------------------------------------------------------------------//
