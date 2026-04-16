//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012, 2013, 2018
// For many platform
//
// 2WW Engenharia de Sistemas
// (c) 2012, 2026, 2013
//
// Last Updated: introduce support for c++14 2018
// Last Updated: introduce support for c++20 2026
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <std.dialog_impl.hpp>
//-----------------------------------------------------------------------------------------------//
std::dialog_impl::dialog_impl(QWidget* owner, Qt::WindowFlags flags, unicodestring const& name) :
   QDialog{ owner, flags },
   task_group{},
   m_verticallay{ new vertical_box{ this, name } },
   m_buttons{ new horizontal_box{ this, HORIZONTAL_LAYOUT_BUTTONS_NAME } }
{
   setObjectName(name);
   setWindowTitle(name);
}
