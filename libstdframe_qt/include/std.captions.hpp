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
   namespace captions
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
         char const * INVALIDPOINTER{ "Invalid pointer, variable %s" };
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
         const unicodestring PREFERENCES{ unicodestring::fromLatin1("Preferências") };
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
      namespace libbs
      {
         unicodestring const CONTROLE_DE_VERBAS{ "Controle de Verbas" };

         struct Equipe
         {
            const unicodestring NAME{ "&Equipe" };
            const unicodestring REGIONAL{ "&Regional" };
            const unicodestring CARGO{ "&Cargo" };
            const unicodestring VAGA{ "&Vaga" };
            const unicodestring MATRICULAS{ "&Matriculas" };
            const unicodestring NCC{ unicodestring::fromLatin1("Número de conta corrente (N.C/C)") };
            Equipe() = default;
         };
         //-----------------------------------------------------------------------------------------------//
         struct Despesas
         {
            const unicodestring NAME{ "&Despesas" };
            const unicodestring TIPO_DE_DESPESAS{ "&Tipo de despesas" };
            const unicodestring QUANTIDADES{ "&Quantidades" };
            //-----------------------------------------------------------------------------------------------//
            struct Valores
            {
               const unicodestring NAME{ "&Valores" };
               const unicodestring BASICOS{ "&Basicos" };
               const unicodestring PESSOAIS{ "&Pessoais" };
               Valores() = default;
            };
            //-----------------------------------------------------------------------------------------------//
            struct Controles
            {
               const unicodestring NAME{ "&Controles" };

               struct ContaCorrente
               {
                  const unicodestring NAME{ "&Conta corrente" };
                  const unicodestring LANCAMENTO_DE_RELATORIOS{ unicodestring::fromLatin1("&Lançamento de relatórios") };
                  ContaCorrente() = default;
               };

               struct PainelControle
               {
                  const unicodestring NAME{ "&Painel de controle" };
                  const unicodestring TODOS_EXCETO_DEMITIDOS{ "&Todos exceto demitidos" };
                  const unicodestring EQUIPE_DE_CAMPO{ "Equipe de campo" };
                  const unicodestring DEMITIDOS{ "Demitidos" };
                  PainelControle() = default;
               };

               Controles() = default;
            };
            //-----------------------------------------------------------------------------------------------//
            struct Agenda
            {
               const unicodestring NAME{ "&Agenda" };
               const unicodestring PENDENTES{ "&Pendentes" };
               const unicodestring ENCERRADOS{ "&Encerrados" };
               const unicodestring ATUALIZAR{ "A&tualizar" };
               Agenda() = default;
            };
            //-----------------------------------------------------------------------------------------------//
            const unicodestring REMESSAS{ "&Remessas" };
            const unicodestring BANCO_RETORNO{ "&Banco retorno" };
            const unicodestring EXTRATO_SAQUE{ "&Extrato de saque" };

            Despesas() = default;
         };
         //-----------------------------------------------------------------------------------------------//
         struct Saldos
         {
            const unicodestring NAME{ "&Saldos" };
            const unicodestring GERENCIAL{ "&Gerencial" };

            struct Contabil
            {
               const unicodestring NAME{ "&Contabil" };
               const unicodestring SITUACAO_GERAL{ "Situação geral" };
               const unicodestring EXTRATO_DE_FUNCIONARIO{ "Extrato de funcionário" };
               Contabil() = default;
            };

            Saldos() = default;
         };
         //-----------------------------------------------------------------------------------------------//
         const unicodestring LANCA_OS_BB{ unicodestring::fromLatin1("Lançamentos banco do brasil") };
         //-----------------------------------------------------------------------------------------------//         
         struct Bloqueio
         {
            const unicodestring NAME{ "&Bloqueio" };
            const unicodestring BLOQUEAR_SALDOS_ANTERIORES{ "Bloquear saldos anteriores" };
            Bloqueio() = default;
         };
         //-----------------------------------------------------------------------------------------------//
         struct Tabelas
         {
            const unicodestring NAME{ "&Tabelas" };

            struct Eventos
            {
               const unicodestring NAME{ "&Eventos" };
               const unicodestring EVENTOS{ unicodestring::fromLatin1("Manutenção de &eventos") };
               Eventos() = default;
            };

            const unicodestring PESSOAS_DE_CONTATO{ "Pessoas de &contato" };
            const unicodestring REGIONAIS{ "Regionais" };
            const unicodestring PRODUTOS{ "&Produtos" };
            const unicodestring GERENCIA_DE_PRODUTO{ unicodestring::fromLatin1("Gerência de produto") };

            const unicodestring TAREFAS{ "&Tarefas" };
            const unicodestring GASTOS{ "&Gastos" };
            const unicodestring RATEIO{ "&Rateio" };

            const unicodestring CIDADES{ "&Cidades" };
            const unicodestring MEDICOS{ unicodestring::fromLatin1("&Médicos") };
            const unicodestring CENTRO_DE_CUSTO{ "Centro de custo" };

            Tabelas() = default;
         };

         struct Propagandistas
         {
            const unicodestring NAME{ "Propagandistas" };
            const unicodestring TODOS_EXCETO_DEMITIDOS{ "Todos exceto demitidos" };
            const unicodestring EQUIPE_DE_CAMPO{ "&Equipe de campo" };
            const unicodestring DEMITIDOS{ "&Demitidos" };

            const unicodestring TIPOS_DE_DESPESAS{ "&Tipos de despesas" };
            const unicodestring TIPOS_DE_EVENTOS{ "Tipos de eventos" };
            const unicodestring DIRETORIAS{ "&Diretorias" };
            const unicodestring FORNECEDORES{ "&Fornecedores" };
            const unicodestring ATIVIDADES{ "&Atividades" };

            Propagandistas() = default;
         };

         struct Verbas
         {
            const unicodestring NAME{ "&Verbas" };
            const unicodestring ANDAMENTO{ "&Andamento" };
            const unicodestring ENCERRADAS{ "&Encerradas" };
            const unicodestring DISTRIBUICAO{ unicodestring::fromLatin1("&Distribuição") };

            const unicodestring GASTOS{ "&Gastos" };
            const unicodestring LANCAMENTOS{ unicodestring::fromLatin1("&Lançamentos") };

            const unicodestring MULTIPLOS{ "Multiplos" };
            const unicodestring TAREFAS{ "&Tarefas" };
            const unicodestring ENCERRAR{ "Encerrar" };
            const unicodestring VERIFICAR_ORCAMENTO{ unicodestring::fromLatin1("&Verificar orçamento") };

            const unicodestring RECALCULO{ "&Recalculo" };
            const unicodestring LISTAGEM{ "&Listagem" };
            const unicodestring RDS{ "RDs" };
            const unicodestring WWG{ unicodestring::fromLatin1("Solicitações de verbas vindos do sistema de cartões banco do brasil (WWG)") };

            const unicodestring NOTAS_FISCAIS{ "&Notas fiscais" };
            const unicodestring VERIFICAO{ unicodestring::fromLatin1("Verificação") };
            Verbas() = default;
         };

         struct Pagamentos
         {
            const unicodestring NAME{ "&Pagamentos" };
            const unicodestring NORMAIS{ "&Normais" };
            const unicodestring PENDENTES{ "Pendentes" };
            const unicodestring ADIANTAMENTOS_PENDENTES{ "&Adiantamentos pendentes" };
            const unicodestring TODOS_ADIANTAMENTOS{ "&Todos adiantamentos" };
            const unicodestring ESTATISTICA{ "&Estatistica" };
            const unicodestring PAGAR{ "Pagar" };
            Pagamentos() = default;
         };

         struct Financeiro
         {
            const unicodestring NAME{ "&Financeiro" };
            const unicodestring GERAR_CARTA{ "&Gerar carta" };
            const unicodestring LANCAMENTOS{ unicodestring::fromLatin1("Lançamentos") };
            Financeiro() = default;
         };

         const unicodestring CONTRATOS{ "&Contratos" };

         struct Romaneio
         {
            const unicodestring NAME{ "&Romaneio" };
            const unicodestring EMISSAO{ unicodestring::fromLatin1("&Emissão") };
            Romaneio() = default;
         };

         const unicodestring NOTAS_FISCAIS{ std::captions::libbs::Verbas{}.NOTAS_FISCAIS };
      }
   }
}