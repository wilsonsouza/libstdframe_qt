//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012
//-----------------------------------------------------------------------------------------------//
#include <std.application.hpp>
#include <std.display_progressbar.hpp>
#include <std.layouts.hpp>
#include <std.treemodel.hpp>
#include <sql.query.hpp>
#include <std.treewidget.hpp>
#include <std.mdiframewindow.hpp>
#include <std.mdichildwindow.hpp>
//-----------------------------------------------------------------------------------------------//
using namespace std;
//-----------------------------------------------------------------------------------------------//
treemodel::treemodel(MDIChildWindow * pChildWnd)
{
   shared_ptr<sql::Query> & pSQL = pChildWnd->GetFrameWindow()->GetSingleQueryLanguageHandle();
   SetSingleQueryLanguageMode(sqlcmd::SQL_AS);
   SetChildWnd(pChildWnd);
   SetTreeWidgetHandle(new TreeWidget(nullptr));
   SetTableHandle(shared_ptr<sql::Table>(new sql::Table
   {
      GetChildWnd()->GetFrameWindow()->GetSingleQueryLanguageHandle()->ConnectParameters
   }));
   SetRows(0);
   SetIndexKey(0);
   SetDisplayHandle(shared_ptr<DisplayProgressBar>(new DisplayProgressBar
   {
      GetChildWnd()->GetFrameWindow(), GetChildWnd()
   }));
}
//-----------------------------------------------------------------------------------------------//
TreeModel::~TreeModel()
{
   //delete m_Control;
   //delete m_pHeaderLink;
   //delete m_Common;
}
//-----------------------------------------------------------------------------------------------//
unsigned int const __fastcall TreeModel::Execute(std::ustring strfields, std::ustring strTable, std::ustring strconstraint)
{
   unsigned int hr = 0;
   std::ustring strcmd = std::ustring
   {
      "select %1 from %2 where %3" 
   }.arg(strfields).arg(strTable).arg(strconstraint);

   if(strTable.isEmpty())
      throw exception("Parameter strTable is empty!");

   if(strconstraint.isEmpty())
      strcmd = std::ustring("select %1 from %2").arg(strfields).arg(strTable);

   if(strfields.isEmpty())
      strcmd = std::ustring("select * from %2").arg(strTable);

   if (GetTableHandle()->Open(strcmd.to_wstring()))
   {
      hr = (unsigned int)GetTableHandle()->Reccount;
   }

   GetDisplayHandle()->Create(int(hr));

   //reinitialize line counter
   SetRows(0);

  // if(hr > 0)
  //    m_PBar->setrange(0, hr);

   return hr;
}
//-----------------------------------------------------------------------------------------------//
void const __fastcall TreeModel::Update()
{
   GetTableHandle()->Next();
   GetDisplayHandle()->Update();
}
//-----------------------------------------------------------------------------------------------//
void const __fastcall TreeModel::Refresh(StringList const & strlist)
{
   GetTreeWidgetHandle()->UpdateColumns(strlist);
}
//----------------------------------------------------------------------------------------------//
QTreeWidgetItem * TreeModel::GetItemDirection(ITEMDIRECTION ID) const
{
   return nullptr;
}
//----------------------------------------------------------------------------------------------//
StringList __fastcall TreeModel::GetModelHeaderList()
{
   StringList out;
   auto p = shared_ptr<QMap<ustring, ustring>>(*this);

   for (auto i = p->begin(); i != p->end(); ++i)
   {
      if (!i.value().isEmpty())
         out << i.value();
   }
   return out;
}
//----------------------------------------------------------------------------------------------//
StringList __fastcall TreeModel::GetModelFieldList()
{
   StringList out;
   unsigned int sql = GetSingleQueryLanguageMode();
   unsigned int sql_as = sqlcmd::SQL_AS;
   auto & p = shared_ptr<QMap<ustring, ustring>>(*this);

   for (auto i = p->begin(); i != p->end(); i++)
   {
      if (GetSingleQueryLanguageMode() == sqlcmd::SQL_AS)
      {
         if (!i.value().isEmpty())
            out << i.value();
         else
            out << i.value();
      }
      else
         out << i.key();
   }
   return out;
}
//----------------------------------------------------------------------------------------------//
std::ustring __fastcall TreeModel::GetModelFormattedFields()
{
   StringList out;
   unsigned int sql = GetSingleQueryLanguageMode();
   unsigned int sql_as = sqlcmd::SQL_AS;
   auto & p = shared_ptr<QMap<ustring, ustring>>(*this);

   for (auto i = p->begin(); i != p->end(); ++i)
   {
      if (sql == sql_as)
      {
         if (!i.value().isEmpty())
            out << i.key() + std::ustring(" as [%1]").arg(i.value());
         else
            out << i.key();
      }
   }
   return out.join(",");
}
//-----------------------------------------------------------------------------------------------//
