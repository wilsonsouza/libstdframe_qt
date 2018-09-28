//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.linedate.hpp>
#include <std.combobox.hpp>
#include <std.checkbox.hpp>
#include <std.textedit.hpp>
#include <std.treewidget.hpp>
#include <std.lcdnumber.hpp>
#include <std.generate_container_mapper.hpp>
#include <std.searchinternalcontainermapper.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   template <class fieldmapper_t, class widget_t,
      enable_if < is_same<widget_t, QWidget>::value || is_same<widget_t, widget>::value>::type = 0>
      class Q_DECL_EXPORT update_controlsby_mapper : public fieldmapper_t, public widget_t
   {
   public:
      typedef fieldmapper_t fieldmapper_value;
      typedef widget_t widget_value;
      //
   public:
      explicit update_controlsby_mapper(fieldmapper_value const & fmapper, widget_value const *& owner) :
         fieldmapper_value{ fmapper },
         widget_value{ owner },
         m_container{ new generate_container_mapper<>{onwer} }
      {
      }
      //-----------------------------------------------------------------------------------------------//
      virtual update_controlsby_mapper * set_enabled(bool const & enabled)
      {
         for_each(cbegin(), cend(), [=](auto const & value)
         {
            auto object_value = m_container->value(value.first);
            //
            if (object_value != nullptr)
            {
               object_value.second->setEnabled(enabled);
            }
         });
         return this;
      }
      //-----------------------------------------------------------------------------------------------//
      auto update(bool const & enabled)
      {
         for_each(cbegin(), cend(), [=](auto const & value)
         {
            auto widget_value = m_container->value(value.first);
            auto field_value = value.second;
            /**/
            if (widget_value)
            {
               auto field_name = field_value->get_name();
               /**/
               if ((widget_value->inherits("std::lineedit") ||
                   widget_value->inherits("std::linedate") ||
                   widget_value->inherits("std::textedit")) &&
                   widget_value->objectName() == field_name)
               {
                  update<"std::lineedit">(widget_value, field_value, enabled);
               }
               else if (widget_value->inherits("std::checkbox") && widget_value->objectName() == field_name)
               {
                  update<checkbox *, "std::checkbox">(widget_value, field_value, enabled);
               }
               else if (widget_value->inherits("std::combobox") && widget_value->objectName() == field_name)
               {
                  if (static_cast<combobox *>(widget_value)->on_update_current_data != nullptr)
                  {
                     static_cast<combobox *>(widget_value)->on_current_index_changed(widget_value,
                                                                                     field_value->get_data());
                  }
                  widget_value->setEnabled(enabled);
               }
               else if (widget_value->inherits("std::treewidget") && widget_value->objectName() == field_name)
               {
                  static_cast<treewidget *>(widget_value)->on_notify(widget_value, WM_TREEWIDGET_UPDATEITEMS, field_value);
               }
               else if (widget_value->inherits("std::lcdnumber") && widget_value->objectName() == field_name)
               {
                  static_cast<lcdnumber *>(widget_value)->display(field_value->get_integer());
                  widget_value->setEnabled(enabled);
               }
            }
         });
         return this;
      }
      //-----------------------------------------------------------------------------------------------//
   protected:
      template <typename object_t, typename field_t, unicodestring class_name,
         enable_if<is_same<object_t, lineedit>::value ||
         is_same<object_t, lineedit>::value ||
         is_same<object_t, textedit>::value, object_t>::type = 0>
         auto update(object_t *& source, field_t *& field, bool const & enabled)
      {
         if (forward<object_t>(source)->inherits(class_name) &&
             forward<field_t>(field)->get_name().compare(forward<object_t>(source)->objectName()) == 0)
         {
            forward<object_t>(source)->setEnabled(enabled);
            forward<object_t>(source)->setText(forward<field_t>(field)->get_string());
            //
            if (forward<object_t>(source)class_name.compare("std::lineedit") == 0)
            {
               forward<object_t>(source)->setMaxLength(forward<field_t>(field)->get_size());
            }
         }
         return this;
      }
      //-----------------------------------------------------------------------------------------------//
      template <typename object_t, typename field_t, unicodestring class_name,
         enable_if<is_same<object_t, checkbox>::value, object_t>::type = 0>
         auto update(object_t *& source, field_t *& field, bool const & enabled)
      {
         switch (forward<field_t>(field)->get_string().data()->digitValue())
         {
         case Qt::Key_S:
         case Qt::Key_1:
            forward<object_t>(source)->setChecked(true);
            break;
         case Qt::Key_N:
         case Qt::Key_0:
            forward<object_t>(source)->setChecked(false);
            break;
         default:
            forward<object_t>(source)->setChecked(forward<field_t>(field)->get_bool());
         }
         forward<object_t>(source)->setEnabled(enabled);
         return this;
      }
   protected:
      shared_ptr<generate_container_mapper<>> m_container;
   };
}