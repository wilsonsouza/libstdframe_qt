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
   class Q_DECL_EXPORT textedit : public QTextEdit
   {
      Q_OBJECT
   public:
      explicit textedit(QWidget * owner,
                        unicodestring const & contents = unicodestring{},
                        unicodestring const & name = unicodestring{}) :
         QTextEdit{ owner }
      {
         this->set_notify_everthing()->setObjectName(name);
      }
      ~textedit() override
      {
         disconnect();
      }
      //
   public:
      function<bool(bool const & yes, textedit * sender)> on_copy_available{ nullptr };
      function<bool(QTextCharFormat const & fmt, textedit * sender)> on_current_char_format_changed{ nullptr };
      function<bool(textedit * sender)> on_cursor_position_changed{ nullptr };
      function<bool(bool const & ok, textedit * sender)> on_redo_available{ nullptr };
      function<bool(textedit * sender)> on_selection_changed{ nullptr };
      function<bool(textedit * sender)> on_text_changed{ nullptr };
      function<bool(bool const & ok, textedit * sender)> on_undo_available{ nullptr };
      //
   protected:
      textedit * set_notify_everthing()
      {
         connect(this, &QTextEdit::copyAvailable, [=](bool ok)
         {
            emit (on_copy_available != nullptr?on_copy_available(ok, this): nullptr);
         });
         connect(this, &QTextEdit::currentCharFormatChanged, [=](const QTextCharFormat & f)
         {
            emit on_current_char_format_changed(f, this);
         });
         connect(this, &QTextEdit::cursorPositionChanged, [=]()
         {
            emit on_cursor_position_changed(this);
         });
         connect(this, &QTextEdit::redoAvailable, [=](bool ok)
         {
            emit on_redo_available(ok, this);
         });
         connect(this, &QTextEdit::selectionChanged, [=]()
         {
            emit on_selection_changed(this);
         });
         connect(this, &QTextEdit::textChanged, [=]()
         {
            emit on_text_changed(this);
         });
         connect(this, &QTextEdit::undoAvailable, [=](bool ok)
         {
            emit on_undo_available(ok, this);
         });
         return this;
      }
   };
}
//-----------------------------------------------------------------------------------------------//

