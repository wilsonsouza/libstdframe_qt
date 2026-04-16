//-----------------------------------------------------------------------------------------------//
// lib-std-frame-qt abstraction framework
//
// Created by Wilson.Souza 2012, 2018, 2026
// For many platform
//
// 2WW Engenharia de Sistemas
// (c) 2012, 2026
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.defs.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   class Q_DECL_EXPORT widget;
   class Q_DECL_EXPORT toolbox : public QToolBox
   {
      Q_OBJECT
   public:
      explicit toolbox(QWidget * owner,
                       unicodestring const & name = unicodestring{},
                       Qt::WindowFlags wf = 0) : QToolBox{ owner, wf }
      {
         setObjectName(name);
         connect(this, &toolbox::currentChanged, [=](int index)
         {
            dispatch_event(on_current_changed, index, this);
         });
      }
      ~toolbox() override = default;
      //
   public:
      function<bool(int index, toolbox * sender) > on_current_changed{ nullptr };
   };
}
//-----------------------------------------------------------------------------------------------//

