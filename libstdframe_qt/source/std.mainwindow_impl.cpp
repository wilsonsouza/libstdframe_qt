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
#include <std.mainwindow_impl.hpp>
//-----------------------------------------------------------------------------------------------//
std::implement::mainwindow::mainwindow(QWidget* owner,
                                       unicodestring const& name,
                                       Qt::WindowFlags f) :
   QMainWindow{ owner, std::move(f) },
   task_group{},
   popup::pointer{ new popup{name} }
{
   setObjectName(name);
}
