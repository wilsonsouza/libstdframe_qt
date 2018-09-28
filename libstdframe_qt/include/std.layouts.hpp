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
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class vertical_box;   //QVBoxLayout
   class horizontal_box; //QHBoxLayout
   class formbox;        //QFormLayout
   class stacked_box;    //QStackedLayout
   class grid_box;       //QGridLayout
   //-----------------------------------------------------------------------------------------------//
   class vertical_box : public QVBoxLayout
   {
   public:
      vertical_box() = default;
      explicit vertical_box(QWidget * owner, unicodestring const & name) :QVBoxLayout{ owner }
      {
         setObjectName(name);
      }
      ~vertical_box() override = default;
   };
   //-----------------------------------------------------------------------------------------------//
   class horizontal_box : public QHBoxLayout
   {
   public:
      horizontal_box() = default;
      explicit horizontal_box(QWidget * owner, unicodestring const & name) :QHBoxLayout{ owner }
      {
         setObjectName(name);
      }
      ~horizontal_box() override = default;
   };
   //-----------------------------------------------------------------------------------------------//
   class formbox : public QFormLayout
   {
   public:
      formbox() = default;
      explicit formbox(QWidget * owner, unicodestring const & name) :QFormLayout{ owner }
      {
         setObjectName(name);
      }
      ~formbox() override = default;
   };
   //-----------------------------------------------------------------------------------------------//
   class stacked_box : public QStackedLayout
   {
   public:
      stacked_box() = default;
      explicit stacked_box(QWidget * owner, unicodestring const & name) :QStackedLayout{ owner }
      {
         setObjectName(name);
      }
      ~stacked_box() override = default;
   };
   //-----------------------------------------------------------------------------------------------//
   class gridbox : public QGridLayout
   {
   public:
      gridbox() = default;
      explicit gridbox(QWidget * owner, unicodestring const & name) :QGridLayout(owner)
      {
         setObjectName(name);
      }
      ~gridbox() override = default;
   };
}