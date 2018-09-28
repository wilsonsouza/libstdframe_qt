//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//-----------------------------------------------------------------------------------------------//
#include <std.radiobutton.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   radiobutton::radiobutton(QWidget * owner,
                            unicodestring const & caption,
                            unicodestring const & name,
                            bool const & enabled,
                            bool const & checked):
      QRadioButton{ caption, owner }
   {
      setObjectName(name);
      setEnabled(enabled);
      setChecked(checked);
      /* signals */
      //void pressed();
      //void released();
      //void clicked(bool checked = false);
      //void toggled(bool checked);
      connect(this, &radiobutton::pressed, [=]()
      {
         dispatch_event(on_pressed, true, this);
      });
      connect(this, &radiobutton::released, [=]()
      {
         dispatch_event(on_pressed, false, this);
      });
      connect(this, &radiobutton::clicked, [=](bool checked)
      {
         dispatch_event(on_clicked, checked, this);
      });
      connect(this, &radiobutton::toggled, [=](bool checked)
      {
         dispatch_event(on_toggled, checked, this);
      });
   }
   //-----------------------------------------------------------------------------------------------//
   radiobutton::~radiobutton()
   {
      disconnect();
   }
   //-----------------------------------------------------------------------------------------------//
}