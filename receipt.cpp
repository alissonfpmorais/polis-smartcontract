/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <utility>
#include <vector>
#include <string>
#include <eosiolib/eosio.hpp>
#include <eosiolib/time.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/contract.hpp>
#include <eosiolib/crypto.h>

using eosio::key256;
using eosio::indexed_by;
using eosio::const_mem_fun;
using eosio::asset;
using eosio::permission_level;
using eosio::action;
using eosio::print;
using eosio::name;

class receipt : public eosio::contract {
    public:
        receipt(account_name self)
        :contract(self),
        invoices(_self, _self)
        {}

        void insert(account_name from, uint64_t DescReceita, uint64_t NumExercicio, uint64_t NumReceita, uint64_t VlPrevisto, uint64_t VlRealizado)
        {
            require_auth(from);
            
            auto new_invoice_itr = invoices.emplace(_self, [&](auto& invoice) {
                invoice.id = invoices.available_primary_key();
                invoice.institution = from;
                invoice.DescReceita = DescReceita;
                invoice.NumExercicio = NumExercicio;
                invoice.NumReceita = NumReceita;
                invoice.VlPrevisto = VlPrevisto;
                invoice.VlRealizado = VlRealizado;
            });
        }

    private:
        struct invoices
        {
            uint64_t id;
            account_name institution;       // the institution that inserted the data
            uint64_t DescReceita;
            uint64_t NumExercicio;
            uint64_t NumReceita;
            uint64_t VlPrevisto;
            uint64_t VlRealizado;

            EOSLIB_SERIALIZE(invoice, (DescReceita), (NumExercicio), (NumReceita), (VlPrevisto), (VlRealizado))
        };

        typedef eosio::multi_index<N(invoice), invoice> invoce_index;

        invoice_index invoices;
}

EOSIO_ABI(receipt, (insert))