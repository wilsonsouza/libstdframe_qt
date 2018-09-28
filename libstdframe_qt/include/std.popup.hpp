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
#include <std.menuitems.hpp>
#include <std.menuitemdata.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class popup : public list<menuitems *>, public QObject
   {
   public:
      using pointer = shared_ptr<popup>;
      using value_type = list<menuitems *>;
      //
   public:
      popup() = default;
      explicit popup(unicodestring const & name = unicodestring{}) : value_type{}, QObject{}
      {
         setObjectName(name);
      }
      explicit popup(popup const & rhs) : value_type{}, QObject{}
      {
         for_each(begin(), end(), [=](menuitems * value)
         {
            push_back(value);
         });
      }
      popup & operator+(menuitems * value)
      {
         if (value != nullptr)
         {
            push_back(value);
         }
         return *this;
      }
      popup & operator+(popup const & value)
      {
         for_each(value.begin(), value.end(), [=](menuitems * p)
         {
            push_back(p);
         });
         return *this;
      }
      virtual menuitemdata  * operator[](unicodestring const & name)
      {
         for (auto & value : *this)
         {
            auto out = value->finditem(name);
            /**/
            if (out != nullptr)
            {
               return out;
            }
         }
         return nullptr;
      }
      virtual menuitems * operator()(unicodestring const & name)
      {
         return *find_if(begin(), end(), [&](menuitems * value)
         {
            return(name.compare(value->get_caption()));
         });
      }
      virtual menuitems * findpopup(unicodestring const & name)
      {
         return (*this)(name);
      }
      template <typename t> t * find(unicodestring const & name)
      {
         return static_cast<t *>((*this)(name));
      }
      virtual menuitemdata * finditem(unicodestring const & name)//search_item
      {
         return (*this)[name];
      }
      popup & operator<<(menuitems * items)
      {
         return operator+(items);
      }
   };
}