//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef account_hpp
#define account_hpp

#include <cstdint>
#include <string>

#include <chrono>
#include <array>
#include <map>
#include <ostream>

#include "object_types.hpp"
#include "system_types.hpp"
#include "secparser.hpp"

struct playerobj_t ;
struct factory_t ;
class section_t ;

/* *************************************************************************
 actentry_t
 ************************************************************************ */
//=========================================================
struct actentry_t {
	std::chrono::system_clock::time_point logged_off;
	std::chrono::system_clock::time_point created_on ;
	playerobj_t *player ;
	priv_t privilege ;
	actentry_t();
	// The format is : playerserial#, privilege, created , logoff 
	actentry_t(const std::string &line,factory_t *factory) ;
	auto value() const ->std::string ;
};

/* *************************************************************************
 account_t
 ************************************************************************ */
//=========================================================
struct account_t {
	std::string username ;
	std::string password ;
	actnum_t number ;
	priv_t privilege ;
	factory_t *factory ;
	std::chrono::system_clock::time_point created_on ;
	std::array<actentry_t, max_characters> characters ;
	account_t(factory_t *factory = nullptr ) ;
	account_t(const section_t &section,factory_t *factory) ;
	auto load(const section_t &section) ->void ;
	auto save(std::ostream &output) const ->void ;
};

/* *************************************************************************
 actholder_t
 ************************************************************************ */
//=========================================================
struct actholder_t :public secparser_t{
private:
	auto processSection(section_t &section) ->void final;
	actnum_t nextnumber ;
	std::string accountfile ;
public:
	std::map<std::string , account_t> accounts ;
	bool create_account ;
	factory_t *factory ;
	// We only want one of these, not setup for it to be copied .
	actholder_t(const actholder_t&) = delete ;
	auto operator=(const actholder_t&)->actholder_t& = delete ;

	~actholder_t() ;
	actholder_t(bool create_account = true ,factory_t * factory = nullptr ) ;
	// Load is for creating new accounts , inherited from secparser_t
	// Set is for reading current accounts
	auto set(const std::string &filepath) ->bool ;
	auto size() const ->size_t ;
	auto account(const std::string &name) -> account_t * ;
	auto createAccount(const std::string &username, const std::string &password, priv_t privilege)->account_t* ;
};
#endif /* account_hpp */
