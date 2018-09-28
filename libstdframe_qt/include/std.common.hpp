//-----------------------------------------------------------------------------------------------//
// dedaluslib.lib for Windows
//
// Created by Wilson.Souza 2012, 2013
// For Libbs Farma
//
// Dedalus Prime
// (c) 2012, 2013
//-----------------------------------------------------------------------------------------------//
#pragma once
#pragma warning(disable:4275)
#pragma warning(disable:4251)
#include <std.defs.hpp>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   //-----------------------------------------------------------------------------------------------//
   namespace index_medical
   {
      enum class status: uint
      {
         IDDAFASTADO = 0,
         IDDFALECIDO = 1,
         IDDTRANSFERIDO = 2,
         IDDAUSENTE = 3,
         IDDCASSADO = 4,
         IDDATIVO = 5,
         IDDPRIMARIA = 6,
         IDDSUSPENSO = 7,
         IDDCANCELADO = 8,
         IDDAPOSENTADO = 9,
         IDDDESCONHECIDO = 0xA
      };
   };
   //-----------------------------------------------------------------------------------------------//
   using employee_status_mapper = map<QChar, unicodestring>;
   using employee_status_icons_mapper = map<QChar, QIcon>;
   //-----------------------------------------------------------------------------------------------//
   template <class T = stringlist>
   class Q_DECL_EXPORT common_impl : public T
   {
   public:
      common_impl() = default;
      ~commonimpl() override = default;
      T & get_uf()
      {
         clear();
         *this << "AC" << "AL" << "AM" << "AP" << "BA" << "CE" << "DF"
            << "ES" << "EX" << "GO" << "IM" << "MA" << "MG" << "MS"
            << "MT" << "PA" << "PB" << "PE" << "PI" << "PR" << "RJ"
            << "RN" << "RO" << "RR" << "RS" << "SC" << "SE" << "SP"
            << "TO";
         return *this;
      }
      T & get_medical_status()
      {
         clear();
         *this << "Afastado" << "Falecido" << "Transferido" << "Ausente" << "Cassado" << "Ativo"
            << unicodestring("Primária") << "Suspenso" << "Cancelado" << "Aposentado" << "Desconhecido";
         return *this;
      }
      employee_status_mapper const get_employee_status()
      {
         return { {Qt::Key_A, "Ativo"},{Qt::Key_I, "Inativo"},{Qt::Key_D, "Demitido"} };
      }
      employee_status_icons_mapper get_employee_status_icons()
      {
         return { {Qt::Key_A, icons::common().OK}, {Qt::Key_I, icons::common().DENIED}, {Qt::Key_D, icons::common().CANCEL} };
      }
   };
}
//-----------------------------------------------------------------------------------------------//
