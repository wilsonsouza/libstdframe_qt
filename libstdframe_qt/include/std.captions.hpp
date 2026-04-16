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
namespace std::captions
{
   struct shared
   {
      unicodestring const SEARCHED{ "Pesquisar" };
      unicodestring const DETAILS{ "Detalhes" };
      shared() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct tokens
   {
      const unicodestring nullstr{};
      const unicodestring SEPARATOR{ "-" };
      const unicodestring STRINGEND{};
      const QIcon nullicon{};
      tokens() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct messages
   {
      char const* INVALIDPOINTER{ "Invalid pointer, variable %s" };
      messages() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct errors
   {
      unicodestring const CRITICAL{ "Erro!!!" };
      unicodestring const QUESTION{ "Confirma?" };
      unicodestring const WARNING{ unicodestring::fromLatin1("Atenção!") };
      errors() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct styles
   {
      const unicodestring WINDOWS{ "windows" };
      const unicodestring FUSION{ "fusion" };
      const unicodestring WINDOWSXP{ "windowsxp" };
      const unicodestring MACINTOSH{ "macintosh" };
      styles() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct common
   {
      const unicodestring OK{ "&OK" };
      const unicodestring CANCEL{ "&Cancelar" };
      const unicodestring CONTINUE{ "Con&tinuar" };
      const unicodestring RETRY{ "&Repetir" };
      const unicodestring HELP{ "&Ajuda" };
      const unicodestring INSERT{ "&Incluir" };
      const unicodestring CHANGE{ "&Alterar" };
      const unicodestring DETAILS{ "&Detalhes" };
      const unicodestring REFRESH{ "&Atualizar" };
      const unicodestring ERASE{ "&Excluir" };
      common() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct file
   {
      const unicodestring NAME{ "&Arquivo" };
      const unicodestring NEW{ "&Novo" };
      const unicodestring OPEN{ "&Abrir" };
      const unicodestring CLOSE{ "&Fechar" };
      const unicodestring SAVE{ "&Salvar" };
      const unicodestring SAVE_AS{ "Salvar &Como" };
      const unicodestring PRINT{ "&Imprimir" };
      const unicodestring PRINT_VIEW{ unicodestring::fromLatin1("&Visualizar Impressão") };
      const unicodestring PRINT_SETUP{ unicodestring::fromLatin1("Configurar Impressão") };
      const unicodestring PRINT_PAGE_SETUP{ "Configurar pagina para impressão" };
      const unicodestring IMPORT{ "Importar" };
      const unicodestring EXPORT{ "Exportar" };
      const unicodestring RECENT_FILES{ "&Recentes" };
      const unicodestring CHANGE_USER{ unicodestring::fromLatin1("&Trocar Usuário") };
      const unicodestring LOGOFF{ "&Desligar Sistema" };
      const unicodestring EXIT{ "&Sair" };
      file() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct edit
   {
      const unicodestring NAME{ "Editar" };
      const unicodestring UNDO{ "Desfazer" };
      const unicodestring REDO{ "Refazer" };
      const unicodestring CUT{ "Recortar" };
      const unicodestring PASTE{ "Colar" };
      const unicodestring COPY{ "Copiar" };
      const unicodestring REMOVE{ "Remover" };
      const unicodestring SELECT_ALL{ "Selecionar Tudo" };
      const unicodestring FIND_REPLACE{ "Pesquisar e Modificar" };
      const unicodestring GOTO{ "Ir Para" };
      edit() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct view
   {
      const unicodestring NAME{ "Visualizar" };
      const unicodestring TOOLBAR{ "Barra de Ferramentas" };
      const unicodestring STATUSBAR{ "Barra de Estados" };
      view() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct tools
   {
      const unicodestring NAME{ "Ferramentas" };
      const unicodestring PREFERENCES{ unicodestring::fromLatin1("Prefer�ncias") };
      tools() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct window
   {
      const unicodestring NAME{ "&Janela" };
      const unicodestring CLOSE{ "&Fechar" };
      const unicodestring CLOSEALL{ "Fechar &toda(s)" };
      const unicodestring MAXIMIZE{ "&Maximizar" };
      const unicodestring MINIMIZE{ "&Minimizar" };
      const unicodestring SHOW{ "Mos&trar" };
      const unicodestring HIDE{ "&Esconder" };
      const unicodestring REFRESH{ "&Atualizar" };
      const unicodestring DOCUMENT{ "Modo &documento" };
      const unicodestring TABBED{ "Modo a&ba" };
      const unicodestring TILE{ "Posicionar &lado a lado" };
      const unicodestring CASCADE{ "Posicionar em &cascata" };
      const unicodestring NEXT{ "&Proxima" };
      const unicodestring PREVIOUS{ "Anterior" };
      window() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct style
   {
      const unicodestring NAME{ "Estilo" };
      const unicodestring WINDOWS{ "Tipo &Windows Nativo" };
      const unicodestring MOTIF{ "Tipo &Motif" };
      const unicodestring CDE{ "Tipo &CDE" };
      const unicodestring PLASTIQUE{ "Tipo &Plastique" };
      const unicodestring VISTA{ "Tipo Windows &Vista" };
      const unicodestring XP{ "Tipo Windows &XP" };
      const unicodestring MACINTOSH{ "Tipo &Macintosh iOS" };
      const unicodestring FUSION{ "Tipo &Fusion" };
      const unicodestring PART{ "Tipo " };
      style() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct user
   {
      const unicodestring NAME{ unicodestring::fromLatin1("Usuários") };
      const unicodestring PASSWORD{ "Senha" };
      const unicodestring PERMISSION{ unicodestring::fromLatin1("Permissões") };
      const unicodestring MANAGER{ unicodestring::fromLatin1("Manutenção") };
      user() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct analyzer
   {
      const unicodestring NAME{ "Analisar" };
      const unicodestring PAGE{ "Selecionar Tipo de Analise..." };
      analyzer() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   struct help
   {
      const unicodestring NAME{ "Ajuda" };
      const unicodestring INDEX{ unicodestring::fromLatin1("Índice da Ajuda") };
      const unicodestring LIBBS{ "Libbs Home Page" };
      const unicodestring DEDALUS{ "Dedalus Home Page" };
      const unicodestring WRDEVINFO{ "WR DevInfo Home Page" };
      const unicodestring ABOUT{ unicodestring::fromLatin1("Sobre %1") };
      help() = default;
   };
   //-----------------------------------------------------------------------------------------------//
   namespace gates
   {
   }
}