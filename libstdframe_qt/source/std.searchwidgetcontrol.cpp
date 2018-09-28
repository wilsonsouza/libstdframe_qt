//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013, 2018
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#include <std.defsx.hpp>
#include <std.button.hpp>
#include <std.combobox.hpp>
#include <std.lineedit.hpp>
#include <std.checkbox.hpp>
#include <std.groupbox_top_button_control.hpp>
#include <std.search_widget_control.hpp>
#include <std.layouts.hpp>
#include <std.mdichildwindow.hpp>
#include <std.label.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   search_widget_control::search_widget_control(QWidget * owner, unicodestring const & name) :
      widget{ owner, name, 0 },
      m_cancel{ new button{this, captions::common{}.CANCEL, m_iconslist->CANCEL, unicodestring{}, true} },
      m_findwhat{ new lineedit{this} },
      m_help{ new button{this, captions::common{}.HELP, m_iconslist->HELPINDEX} },
      m_ok{ new button{this, captions::common{}.OK, m_iconslist->OK} },
      m_lookin{ new combobox{this, unicodestring{}, false} },
      m_options{ new groupbox_top_button_control{unicodestring{"Opções de pesquisa"}} },
      m_regularexpressions{ new combobox{this, unicodestring{}, false} }
   {
      //set default width component
      setMinimumWidth(310);
      setMaximumWidth(310);
   }
   //-----------------------------------------------------------------------------------------------//
   search_widget_control * search_widget_control::set_lookinmapper(LookInMapper const & lm)
   {
      /**/
      m_lookinhasher->assign(lm.cbegin(), lm.cend());
      /**/
      for_each(m_lookinhasher->begin(), m_lookinhasher->end(), [&](auto const & value)
      {
         m_lookin->addItem(value.first, value.second);
      });
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   search_widget_control * search_widget_control::set_findwhat_listmask(FindWhatMaskMapper const & fm)
   {
      m_findwhatmaskhasher->assign(fm.cbegin(), fm.cend());
      return this;
   }
   //-----------------------------------------------------------------------------------------------//
   widget * search_widget_control::create()
   {
      m_regularexpressions->addItems(stringlist{ unicodestring{"Expressões regulares"},
                                     unicodestring{"Mascaras (Tipo *, %, ?"} });

      box()->addWidget(new label{ this, "Procurar por" });
      box()->addWidget([this]()->auto
      {
         /**/
         m_findwhat->on_returnpressed = [=](lineedit * sender)->auto
         {
            return dispatch_event(m_ok->on_clicked, false, m_ok);
         };
         /**/
         m_findwhat->on_textchanged = [=](unicodestring const & value, lineedit * sender)->auto
         {
            m_ok->setEnabled(value.trimmed().length());
            return true;
         };
         return m_findwhat;
      }());
      //
      box()->addWidget(new label{ this, "Filtrar por" });
      box()->addWidget([this]()->auto
      {
         //update combobox look in
         set_lookinmapper(*m_lookinhasher);
         m_lookin->setEditable(false);
         //
         m_lookin->on_current_index_changed = [&](int const & n, combobox * sender)
         {
            using lookmapper_pointer = shared_ptr<LookInMapper>;
            auto fm = m_findwhatmaskhasher->size();
            auto lm = m_lookinhasher->size();
            auto fn_lookup = [&](int const & n, lookmapper_pointer const & f)->auto
            {
               auto p = 0;
               auto out = find_if(f->begin(), f->end(), [&](auto const & d)
               {
                  if (p == n)
                  {
                     return !d.second.empty();
                  }
                  /**/
                  p++;
                  return false;
               });
               return out->second;
            };
            /**/
            if (lm && (n <= lm))
            {
               m_filterselectedname = fn_lookup(n, m_lookinhasher);
            }
            //
            if (fm && (n <= fm))
            {
               m_findwhat->setInputMask(fn_lookup(n, m_findwhatmaskhasher));
            }
            //
            return dispatch_event(sender->on_update_current_data, sender, m_filterselectedname);
         };
         return m_lookin;
      }());
      //
      box()->addWidget(m_options);
      //
      auto pgboptions = m_options->get_group();
      pgboptions->box()->addWidget([this]()->auto
      {
         auto pcbmatchcase = new checkbox{ nullptr, "Correspondente", unicodestring{}, true };
         pcbmatchcase->on_state_changed = [=](int const & state, checkbox * sender)
         {
            return(uint(m_state = (sender->isChecked() ? search_idd::IDDMATCHCASE : m_state)));
         };
         return pcbmatchcase;
      }());
      //
      pgboptions->box()->addWidget([this]()->auto
      {
         auto pcbmatchwholeword = new checkbox{ nullptr, "Coincidir palavra inteira", unicodestring{}, true };
         pcbmatchwholeword->on_state_changed = [=](int const & state, checkbox * sender)
         {
            return(uint(m_state = (sender->isChecked() ? search_idd::IDDMATCHWHOLEWORD : m_state)));
         };
         return pcbmatchwholeword;
      }());
      //
      pgboptions->box()->addWidget([this]()->auto
      {
         auto pcbuse = new checkbox(nullptr, "Usar", unicodestring{}, true);
         pcbuse->on_state_changed = [this](int const & state, checkbox * sender)
         {
            m_regularexpressions->setEnabled(sender->isChecked());
            return true;
         };
         return pcbuse;
      }());
      //
      auto regx = new horizontal_box{};
      {
         regx->addWidget(m_regularexpressions);
         pgboptions->box()->addLayout(regx);
      }

      //create objects
      m_options->create();
      //
      auto phorizontalbuttons = new widget_impl<horizontal_box>{ nullptr, unicodestring{} };
      {
         phorizontalbuttons->box()->addStretch();
         phorizontalbuttons->box()->addWidget([this]()->auto
         {
            m_ok->on_clicked =  [this](bool const &, button * sender)
            {
               dispatch_event(on_findwhat, this);
               return true;
            };
            return m_ok;
         }());
         //
         phorizontalbuttons->box()->addWidget([this]()->auto
         {
            m_cancel->on_clicked = [=](bool const &, button *)
            {
               m_findwhat->setText(unicodestring{});
               m_findwhat->setFocus();
               return true;
            };
            return m_cancel;
         }());
         phorizontalbuttons->box()->addWidget(m_help);
      }
      //
      box()->addWidget(phorizontalbuttons);
      box()->addStretch();
      return this;
   }
}