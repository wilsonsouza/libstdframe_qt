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
//-----------------------------------------------------------------------------------------------//
#include <std.dockwindow.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   dockwindow::dockwindow(unicodestring const & title,
                          QWidget * owner,
                          unicodestring const & name,
                          Qt::WindowFlags flags) :
      QDockWidget{ title, owner, flags }
   {
      set_notify_everthing()->setObjectName(name);
   }
   //-----------------------------------------------------------------------------------------------//
   dockwindow::~dockwindow()
   {
      disconnect();
   }
   //-----------------------------------------------------------------------------------------------//
   dockwindow * dockwindow::set_notify_everthing()
   {
      connect(this, &QDockWidget::allowedAreasChanged, [=](Qt::DockWidgetAreas mode)
      {
         dispatch_event(on_allowed_areas_changed, mode, this);
      });
      connect(this, &QDockWidget::dockLocationChanged, [=](Qt::DockWidgetArea mode)
      {
         dispatch_event(on_dock_location_changed, mode, this);
      });
      connect(this, &QDockWidget::featuresChanged, [=](QDockWidget::DockWidgetFeatures mode)
      {
         dispatch_event(on_features_changed, mode, this);
      });
      connect(this, &QDockWidget::topLevelChanged, [=](bool top)
      {
         dispatch_event(on_top_level_changed, top, this);
      });
      connect(this, &QDockWidget::visibilityChanged, [=](bool top)
      {
         dispatch_event(on_visibility_changed, top, this);
      });
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
}