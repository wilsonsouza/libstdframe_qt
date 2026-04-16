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
   class Q_DECL_EXPORT checkbox : public QCheckBox
   {
      Q_OBJECT
   public:
      explicit checkbox(QWidget * owner,
                        unicodestring const & caption = unicodestring{},
                        unicodestring const & name = unicodestring{},
                        bool const & enabled = true,
                        bool const & checked = false) :QCheckBox{ caption, owner }
      {
         setObjectName(name);
         setEnabled(enabled);
         setChecked(checked);
         //
         connect(this, &checkbox::stateChanged, [=](int state)
         {
            dispatch_event(on_state_changed, state, this);
         });
      }
      virtual ~checkbox() override = default;
      //
   public:
      function<bool(uint state, checkbox * sender)> on_state_changed{ nullptr };
   };
};
//-----------------------------------------------------------------------------------------------//

