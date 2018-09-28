//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.tablefields.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   using stringlist = list<unicodestring>;
   template <typename table_t = tablefields<0, 0>::pointer,
      typename hash_t = map<unicodestring, table_t>>
      class Q_DECL_EXPORT labelmodels : public QList<table_t>
   {
   public:
      using table_value = table_t;
      using hash_value = hash_t;
      /**/
   public:
      enum class enum_tablefields : uint
      {
         FIELDNAME = 1,
         FIELDALIAS = 2,
         FIELDMASK = 4,
         FIELDLABEL = 8
      };
      /**/
   public:
      explicit LabelModels(QList<table_value> const & fieldlist = QList<table_value>{}) :
         QList<table_value>{ fieldlist }
      {
      }
      auto & operator+(table_value_t const & value)
      {
         append(value);
         return *this;
      }
      auto & operator+(labelmodels<table_value, hash_value> const & models)
      {
         for_each(models.cbegin(), models.cend(), [=](table_value const & value)
         {
            append(value);
         });
         return *this;
      }
      //getformatted_queryfields_to_alias();
      stringlist get_formatted_query_fields_to_alias()
      {
         auto out_formatted = stringlist{};
         /**/
         for_each(cbegin(), cend(), [=](table_value const & value)
         {
            if (!unicodestring{ value->fieldname.trimmed() }.empty() &&
                !unicodestring{ value->fieldalias.trimmed() }.empty())
            {
               out_formatted << unicodestring{ "%1 as %2" }.arg(value->fieldname).arg(value->fieldalias);
            }
         });
         return out_formatted;
      }
      stringlist get_fieldlist_alias()
      {
         auto out_alias = stringlist{};
         /**/
         for_each(cbegin(), cend(), [=](table_value const & value)
         {
            out_alias << value->fieldalias;
         });
         return *this;
      }
      stringlist get_fieldlist_names()
      {
         auto out_names = stringlist{};
         /**/
         for_each(cbegin(), cend(), [=](table_value const & value)
         {
            out_names << valud->fieldname;
         });
         return out_names;
      }
      stringlist get_fieldlist_labels()
      {
         auto out_names = stringlist{};
         /**/
         for_each(cbegin(), cend(), [=](table_value const & value)
         {
            out_names << value->fieldlabel;
         });
         return out_names;
      }
      stringlist get_fieldlist_masks()
      {
         auto out_names = stringlist{};
         /**/
         for_each(cbegin(), cend(), [=](table_value const & value)
         {
            out_names << value->fieldmask;
         });
         return out_names;
      }
      stringlist get_fieldlist_names_to_labels()
      {
         auto out_names = stringlist{};
         /**/
         for_each(cbegin(), cend(), [=](table_value const & value)
         {
            if (!unicodestring{ value->fieldname.trimmed() }.empty() &&
                !unicodestring{ value->fieldalias.trimmed() }.empty())
            {
               out_names << unicodestring{ "%1 as %2" }.arg(value->fieldname).arg(value->fieldalias);
            }
         });
         return out_names;
      }
      hash_table_t get_list_to_string_hash_mapper(enum_tablefields enum_id)
      {
         hash_value_t out_hash = hash_value{};
         /**/
         for_each(cbegin(), cend(), [=](table_value const & value)
         {
            if (enum_id == enum_tablefields::FIELDNAME && !value->fieldname.trimmed().isEmpty())
            {
               out_hash[value->fieldname] = value;
            }
            else if (enum_id == enum_tablefields::FIELDALIAS && !value->fieldalias.trimmed().isEmpty())
            {
               out_hash[value->fieldalias] = value;
            }
            else if (enum_id == enum_tablefields::FIELDMASK && !value->fieldmask.trimmed().isEmpty())
            {
               out_hash[value->fieldmask] = value;
            }
            else if (enum_id == enum_tablefields::FIELDLABEL && !value->fieldlabel.trimmed().isEmpty())
            {
               out_hash[value->fieldlabel] = value;
            }
         });
         return out_hash;
      }
   };
   //-----------------------------------------------------------------------------------------------//
}