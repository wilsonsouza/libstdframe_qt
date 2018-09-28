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
#include <std.submenuitemdata.hpp>
#include <std.menuitemdata.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   bool const menuitemdata::is_separator() const
   {
      return get_caption().contains(captions::tokens{}.SEPARATOR);
   }
   //-----------------------------------------------------------------------------------------------//
   bool const menuitemdata::is_action() const
   {
      return m_actionitem != nullptr;
   }
   //-----------------------------------------------------------------------------------------------//
   bool const menuitemdata::is_submenu() const
   {
      return m_submenu_itemdata->empty();
   }
   //-----------------------------------------------------------------------------------------------//
   menuitemdata & menuitemdata::operator[](menuitemdata * d)
   {
      if (d)
      {
         m_submenu_itemdata->push_back(d);
      }
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   menuitemdata & menuitemdata::operator+(menuitemdata * d)
   {
      if (d)
      {
         m_submenu_itemdata->push_back(d);
      }
      return *this;
   }
   //-----------------------------------------------------------------------------------------------//
   submenuitemdata * menuitemdata::get_submenu_itemdata() const
   {
      return m_submenu_itemdata.operator->();
   }
   //-----------------------------------------------------------------------------------------------//
}
