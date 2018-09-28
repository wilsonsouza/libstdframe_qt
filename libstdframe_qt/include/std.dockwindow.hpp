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
   class Q_DECL_EXPORT dockwindow : public QDockWidget
   {
      Q_OBJECT
   public:
      explicit dockwindow(unicodestring const & title,
                          QWidget * owner,
                          unicodestring const & name = unicodestring{},
                          Qt::WindowFlags flags = 0);
      ~dockwindow() override;
      //
   public:
      function<bool(Qt::DockWidgetAreas areas, dockwindow * sender)> on_allowed_areas_changed{nullptr };
      function<bool(Qt::DockWidgetArea area, dockwindow * sender)> on_dock_location_changed{ nullptr };
      function<bool(QDockWidget::DockWidgetFeatures features, dockwindow * sender)> on_features_changed{ nullptr };
      function<bool(bool top, dockwindow * sender)> on_top_level_changed{ nullptr };
      function<bool(bool visible, dockwindow * sender)> on_visibility_changed{ nullptr };
      //
   protected:
      virtual dockwindow * set_notify_everthing();
   };
   //-----------------------------------------------------------------------------------------------//
};