//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//-----------------------------------------------------------------------------------------------//
#include <std.lineedit.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   lineedit::lineedit() :QLineEdit{}
   {
      setObjectName("lineedit");
      set_notify_everthing();
      setText(unicodestring{});
      setEchoMode(Normal);
   }
   //-----------------------------------------------------------------------------------------------//
   lineedit::lineedit(unicodestring const & name) :QLineEdit{}
   {
      setObjectName(name);
      set_notify_everthing();
      setText(unicodestring{});
      setEchoMode(Normal);
   }
   //-----------------------------------------------------------------------------------------------//
   lineedit::lineedit(unicodestring const & name, unicodestring const & mask, int const fixed_size_with) :
      QLineEdit{}
   {
      setObjectName(name);
      set_notify_everthing();
      this->set_inputmask(mask);
      setEchoMode(Normal);
      setText(unicodestring{});
      setMaxLength(mask.length());
      /**/
      setMaximumWidth(fixed_size_with);
      setMinimumWidth(fixed_size_with);
      setFixedWidth(fixed_size_with);
   }
   //-----------------------------------------------------------------------------------------------//
   lineedit::lineedit(unicodestring const & name, int const max_length, int const fixed_size_with) :
      QLineEdit{}
   {
      setObjectName(name);
      set_notify_everthing();
      setEchoMode(Normal);
      setText(unicodestring{});
      setMaxLength(max_length);
      /**/
      setMaximumWidth(fixed_size_with);
      setMinimumWidth(fixed_size_with);
      setFixedWidth(fixed_size_with);
   }
   //-----------------------------------------------------------------------------------------------//
   lineedit::lineedit(QWidget * owner, int const max_length) :QLineEdit{ owner }
   {
      setObjectName("lineedit");
      set_notify_everthing();
      setText(unicodestring{});
      setEchoMode(Normal);
      setMaxLength(max_length);
   }
   //-----------------------------------------------------------------------------------------------//
   lineedit::lineedit(QWidget * owner,
                      unicodestring const & contents,
                      int const max_length,
                      int const fixed_size_width,
                      unicodestring const & name) :QLineEdit{ contents, owner }
   {
      setObjectName(name);
      set_notify_everthing();
      setText(unicodestring{});
      setEchoMode(Normal);
      setMaxLength(max_length);
      /**/
      setMaximumWidth(fixed_size_width);
      setMinimumWidth(fixed_size_width);
      setFixedWidth(fixed_size_width);
   }
   //-----------------------------------------------------------------------------------------------//
   lineedit::~lineedit()
   {
      disconnect();
   }
   //-----------------------------------------------------------------------------------------------//
   void const lineedit::set_validator(QValidator const * validator)
   {
      setValidator(validator);
   }
   //-----------------------------------------------------------------------------------------------//
   void const lineedit::set_inputmask(unicodestring const & mask)
   {
      auto font_size = fontInfo().pixelSize() - 2;
      auto mask_size = mask.length();
      {
         if (mask.length() > 0)
         {
            setInputMask(mask);
            setMaxLength(mask.length());
            /**/
            auto set_dimensions = [this](int n)
            {
               setMinimumWidth(n);
               setMaximumWidth(n);
            };
            /**/
            set_dimensions(mask_size * font_size);
            show();
         }
      }
   }
   //-----------------------------------------------------------------------------------------------//
   void const lineedit::set_notify_everthing()
   {
      connect(this, &QLineEdit::cursorPositionChanged, [&](int old_pos, int new_pos)
      {
         if (on_cursorpositionchanged != nullptr)
         {
            emit on_cursorpositionchanged(old_pos, new_pos, this);
         }
      });
      connect(this, &QLineEdit::editingFinished, [=]()
      {
         if (on_editingfinished != nullptr)
         {
            on_editingfinished(this);
         }
      });
      connect(this, &QLineEdit::returnPressed, [=]()
      {
         if (on_returnpressed != nullptr)
         {
            on_returnpressed(this);
         }
      });
      connect(this, &QLineEdit::selectionChanged, [=]()
      {
         if (on_selectionchanged != nullptr)
         {
            on_selectionchanged(this);
         }
      });
      connect(this, &QLineEdit::textChanged, [=](unicodestring const & data)
      {
         if (on_textchanged != nullptr)
         {
            on_textchanged(data, this);
         }
      });
      connect(this, &QLineEdit::textEdited, [=](unicodestring const & data)
      {
         if (on_textedited)
         {
            on_textedited(data, this);
         }
      });
   }
   //-----------------------------------------------------------------------------------------------//
   void lineedit::keyPressEvent(QKeyEvent * e)
   {
      auto key = e->key();
      //
      switch (key)
      {
      case Qt::Key_Tab:
      case Qt::Key_Return:
         if (on_returnpressed != nullptr)
         {
            on_returnpressed(this);
         }
         break;
      case Qt::Key_Escape:
         m_old_data = text();
         setText(unicodestring{});
         break;
      default:
         if (key >= Qt::Key_A && key <= Qt::Key_Z || key >= Qt::Key_0 && key <= Qt::Key_9)
         {
            if (on_textchanged != nullptr)
            {
               on_textchanged(text(), this);
            }
         }
         else
         {
            QLineEdit::keyPressEvent(e);
         }
         break;
      }
   }
   //-----------------------------------------------------------------------------------------------//
   bool const lineedit::set_focusnextchild()
   {
      return focusNextChild();
   }
   //-----------------------------------------------------------------------------------------------//
   bool const lineedit::set_focuspreviouschild()
   {
      return focusPreviousChild();
   }
   //-----------------------------------------------------------------------------------------------//
}
