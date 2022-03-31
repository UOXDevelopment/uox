//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef world_hpp
#define world_hpp

#include <cstdint>
#include <string>
#include <filesystem>

#include "uomap.hpp"
#include "langmsg.hpp"
#include "secgroup.hpp"
//=========================================================
struct world_t {
	int number ;
	uomap map ;
	tileinfo *info ;
	std::filesystem::path uodir ;
	langmsg *language ;
	secgroup_t *definitions ;
	secgroup_t *configuration ;
	
	world_t(int mapnum=-1) ;
};
#endif /* world_hpp */
