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
   //-----------------------------------------------------------------------------------------------//
   namespace captions
   {
      struct tabbed
      {
          unicodestring const POSITION{ "Posição" };
          unicodestring const SHAPE{ "Modelo" };
          unicodestring const CLOSE{ "Fechar" };
          unicodestring const NEXT{ "Proximo" };
          unicodestring const PREVIEW{ "Anterior" };
          unicodestring const PROPERTYS{ "Propriedades" };
         //-----------------------------------------------------------------------------------------------//
          unicodestring const POSITION_NORTH{ "Acima das Paginas" };
          unicodestring const POSITION_SOUTH{ "Abaixo das Paginas" };
          unicodestring const POSITION_WEST{ "A Esquerda das Paginas" };
          unicodestring const POSITION_EAST{ "A Direita das Paginas" };
          unicodestring const SHAPE_ROUNDED{ "Cantos Redondos" };
          unicodestring const SHAPE_TRIANGULAR{ "Cantos Triangulares" };
         //-----------------------------------------------------------------------------------------------//
          unicodestring const NAME{ "Tabbed-Popup-Menu" };
          tabbed() = default;
      };
   }
   //-----------------------------------------------------------------------------------------------//
   namespace icons
   {
      struct tabbed
      {
         using pointer = shared_ptr<QIcon>;

         pointer NORTH{ new QIcon{"Action-arrow-up.ico"} };
         pointer SOUTH{ new QIcon{"Action-arrow-down.ico"} };
         pointer WESTH{ new QIcon{"Action-arrow-left.ico"} };
         pointer EAST{ new QIcon{"Action-arrow-right.ico"} };
         pointer CLOSE{ new QIcon{"Action-cancel.ico"} };
         pointer PROPERTYS{ new QIcon{"App-win-settings.ico"} };
         pointer NEXT{ new QIcon{"Action-arrow-blue-double-right.ico"} };
         pointer PREVIEW{ new QIcon{"Action-arrow-blue-double-left.ico"} };
         tabbed() = default;
      };
   }
}