//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012, 2018, 2026
// For many platform
//
// 2WW Engenharia de Sistemas
// (c) 2012, 2026, 2015
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <std.mdichildwindow_impl.hpp>
//-----------------------------------------------------------------------------------------------//
std::mdichildwindow_impl::mdichildwindow_impl(QWidget* owner,
                                              unicodestring const& name,
                                              Qt::WindowFlags) :
   QMdiSubWindow{ owner, f },
   task_group{}
{
   setObjectName(name);
}
