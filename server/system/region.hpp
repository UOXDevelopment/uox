//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef region_hpp
#define region_hpp

#include <cstdint>
#include <string>

#include "position_types.hpp"
class section_t ;

//=========================================================
struct worldregion_t  : public region_t{
	std::string name ;
	bool guarded ;
	bool gate ;
	bool mark ;
	bool recall ;
	bool housing ;
	worldregion_t() ;
	worldregion_t(const worldregion_t& worldregion) ;
	worldregion_t(const section_t &section);
	auto operator=(const worldregion_t &worldregion) ->worldregion_t& ;
};

#endif /* region_hpp */
