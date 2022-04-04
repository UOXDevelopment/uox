//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef account_hpp
#define account_hpp

#include <cstdint>
#include <string>

#include <chrono>
#include <array>
#include <map>

#include "object_types.hpp"
#include "system_types.hpp"

struct playerobj_t ;


/* *************************************************************************
 actentry_t
 ************************************************************************ */
//=========================================================
struct actentry_t {
	std::chrono::system_clock::time_point logged_off;
	serial_t serial ;
	playerobj_t *player ;
	actentry_t();
};

/* *************************************************************************
 account_t
 ************************************************************************ */
struct account_t {
	std::string username ;
	std::string password ;
	
	std::chrono::system_clock::time_point created_on ;
	
	std::array<actentry_t, max_characters> characters ;
};

/* *************************************************************************
 actholder_t
 ************************************************************************ */
struct actholder_t {
	std::map<std::string , account_t> accounts ;
	// We only want one of these, not setup for it to be copied .
	actholder_t(const actholder_t&) = delete ;
	auto operator=(const actholder_t&)->actholder_t& = delete ;
};
#endif /* account_hpp */
