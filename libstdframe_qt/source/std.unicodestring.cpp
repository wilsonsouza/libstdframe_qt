//-----------------------------------------------------------------------------------------------//
// stdx qt abstraction library for cpluplus
//
// Created by Wilson.Souza 2012 - 2026
// For 
//
// WR Developer
// (c) 2012 - 2026
//-----------------------------------------------------------------------------------------------//
#include <std.unicodestring.hpp>
//-----------------------------------------------------------------------------------------------//
using namespace std;
//-----------------------------------------------------------------------------------------------//
unicodestring::unicodestring(unicodestring const& value) : QString{ value }
{
}
//-----------------------------------------------------------------------------------------------//
unicodestring::unicodestring(QString const& value) : QString{ value }
{
}
//-----------------------------------------------------------------------------------------------//
unicodestring::unicodestring(const char* value) : QString{ value }
{
}
//-----------------------------------------------------------------------------------------------//
unicodestring::unicodestring(const wchar_t* value) : QString{ value }
{
}
//-----------------------------------------------------------------------------------------------//
unicodestring::unicodestring(const QChar* value) : QString{ value }
{
}
//-----------------------------------------------------------------------------------------------//
unicodestring::unicodestring(const string& value) : QString{ value.c_str() }
{
}
//-----------------------------------------------------------------------------------------------//
unicodestring::unicodestring(const wstring& value) : QString{ value.c_str() }
{
}
//-----------------------------------------------------------------------------------------------//
template<class compare_t> auto const unicodestring::compare(compare_t const&& value) const
{
   return static_cast<bool>(QString::compare(forward<compare_t>(value)) == 0);
}
//-----------------------------------------------------------------------------------------------//
template<typename bind_value_t> unicodestring& unicodestring::bind(bind_value_t const&& value)
{
   this->arg(forward<bind_value_t>(value));
   return *this;
}
//-----------------------------------------------------------------------------------------------//
unicodestring::operator const wstring() const
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
unicodestring::operator const char* () const
{
   return this->to_string().data();
}
//-----------------------------------------------------------------------------------------------//
unicodestring& unicodestring::bind(stringlist const& queue, unicodestring const& sep)
{
   this->arg(queue.join(sep));
   return *this;
}
//-----------------------------------------------------------------------------------------------//
unicodestring& unicodestring::bind(list<int> const& queue, unicodestring const& sep)
{
   auto s = make_unique<stringlist>();
   ranges::transform(queue, back_inserter(*s), [](int value)
   {
      return unicodestring{ "%1" }.arg(value);
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
bool unicodestring::find_uf(std::unicodestring const& uf)
{
   auto p = get_uf();
   auto success = ranges::find_if(*p, [=](auto const& value)
   {
      return value.toUpper().compare(uf.toUpper()) == 0;
   });
   return static_cast<bool>(success != p->end());
}
//-----------------------------------------------------------------------------------------------//
unicodestring::uf_list_pointer unicodestring::get_uf()
{
   return make_unique<std::stringlist>(std::stringlist
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
                                       });
}
//-----------------------------------------------------------------------------------------------//
