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
   class Q_DECL_EXPORT splitter : public QSplitter
   {
      Q_OBJECT
   public:
      typedef Qt::Orientation ORIENTATION;
   public:
      splitter(QWidget * owner,
               unicodestring const & name = std::unicodestring{},
               Qt::Orientation direction = Qt::Horizontal) :QSplitter{ direction, owner }
      {
         setObjectName(name);
         connect(this, &QSplitter::splitterMoved, [=](int p, int i)
         {
            if (on_splitter_moved != nullptr)
            {
               emit on_splitter_moved(p, i, this);
            }
         });
      }
      ~splitter() override
      {
         disconnect();
      }
      QWidget * operator[](uint const & index)
      {
         return this->widget(index);
      }
      /**/
   public:
      function<bool(int const & p, int const & i, splitter * sender)> on_splitter_moved{ nullptr };
   };
}

