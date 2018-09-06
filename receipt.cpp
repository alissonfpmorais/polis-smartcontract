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
        : contract(self), _accounts(_self, _self) {}

    void insert(account_name from, uint64_t DescReceita, uint64_t NumExercicio, uint64_t NumReceita, uint64_t VlPrevisto, uint64_t VlRealizado)
    {
        require_auth(from);

        data d(from, DescReceita, NumExercicio, NumReceita, VlPrevisto, VlRealizado);
        // enfia d na blockchain
    }

  private:
    struct data
    {
        account_name institution;       // the institution that inserted the data
        uint64_t DescReceita;
        uint64_t NumExercicio;
        uint64_t NumReceita;
        uint64_t VlPrevisto;
        uint64_t VlRealizado;

        data(account_name from, uint64_t dr, uint64_t ne, uint64_t nr, uint64_t vlp, uint64_t vlr)
            : institution(from), 
              DescReceita(dr), 
              NumExercicio(ne), 
              NumReceita(nr),  
              VlPrevisto(vlp),
              VlRealizado(vlr)
        {}
    };
}