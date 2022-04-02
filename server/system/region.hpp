//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef region_hpp
#define region_hpp

#include <cstdint>
#include <string>

#include "position_types.hpp"
class section_t ;

//=========================================================
struct worldregion_t {
	region_t region ;
	std::string name ;
	bool guarded ;
	bool gate ;
	bool mark ;
	bool recall ;
	bool housing ;
	worldregion_t() ;
	worldregion_t(const section_t &section);
};

#endif /* region_hpp */
