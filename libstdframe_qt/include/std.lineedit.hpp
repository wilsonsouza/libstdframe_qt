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
   class Q_DECL_EXPORT lineedit : public QLineEdit
   {
      Q_OBJECT
   public:
      lineedit();
      //-----------------------------------------------------------------------------------------------//
      explicit lineedit(unicodestring const & name);
      //-----------------------------------------------------------------------------------------------//
      explicit lineedit(unicodestring const & name,
                        unicodestring const & mask,
                        int const fixed_size_width);
      //-----------------------------------------------------------------------------------------------//
      explicit lineedit(unicodestring const & name,
                        int const max_length,
                        int const fixed_size_width);
      //-----------------------------------------------------------------------------------------------//
      explicit lineedit(QWidget * owner, int const max_length = 0xff);
      //-----------------------------------------------------------------------------------------------//
      explicit lineedit(QWidget * owner,
                        unicodestring const & contents,
                        int const max_length = 0xff,
                        int const fixed_size_width = 0x32,
                        unicodestring const & name = unicodestring());
      //-----------------------------------------------------------------------------------------------//
      virtual ~lineedit();
      virtual void const set_validator(QValidator const * validator);
      virtual void const set_inputmask(unicodestring const & mask);
      virtual bool const set_focusnextchild();
      virtual bool const set_focuspreviouschild();

      /* events method call */
   public:
      function<bool(int, int, lineedit *)> on_cursorpositionchanged{ nullptr };
      function<bool(lineedit *)> on_editingfinished{ nullptr };
      function<bool(lineedit *)> on_returnpressed{ nullptr };
      function<bool(unicodestring const &, lineedit *)> on_textchanged{ nullptr };
      function<bool(unicodestring const &, lineedit *)> on_textedited{ nullptr };
      function<bool(lineedit *)> on_selectionchanged{ nullptr };
      //
   protected:
      void const set_notify_everthing();
      //
   protected:
      void keyPressEvent(QKeyEvent * pKey) override;
      //
   protected:
      unicodestring m_old_data{};
   };
};
//-----------------------------------------------------------------------------------------------//

