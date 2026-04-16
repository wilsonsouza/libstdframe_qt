//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012, 2013, 2018
// For many platform
//
// 2WW Engenharia de Sistemas
// (c) 2012, 2026, 2013
//-----------------------------------------------------------------------------------------------//
#include <std.label.hpp>
//-----------------------------------------------------------------------------------------------//
using namespace std;
//-----------------------------------------------------------------------------------------------//
label::label(QWidget* owner,
             unicodestring const& title,
             unicodestring const& name = std::unicodestring(),
             Qt::WindowFlags wf = Qt::WindowFlags{}) :QLabel{ owner, wf }
{
   this->setText(title);
   this->setObjectName(name);
}
//-----------------------------------------------------------------------------------------------//
//
//
//
void label::set_notify_everthing()
{
   connect(this, &QLabel::linkActivated, [=](unicodestring const& link)
   {
      dispatch_event(on_link_activated, link, this);
   });
   connect(this, &QLabel::linkHovered, [=](unicodestring const& link)
   {
      dispatch_event(this->on_link_hovered, link, this);
   });
}

