//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef world_hpp
#define world_hpp

#include <cstdint>
#include <string>
#include <filesystem>

#include "uomap.hpp"

class secgroup_t ;
class langmsg ;
struct factory_t ;

//=========================================================
struct world_t {
	int number ;
	uomap ultimamap ;
	std::filesystem::path uodir ;
	langmsg *language ;
	secgroup_t *definitions ;
	secgroup_t *configuration ;
	factory_t *factory ;
	tileinfo *info ;

	world_t(int mapnum=-1) ;
	auto set(int mapnum,const std::filesystem::path &uodir,langmsg *language,secgroup_t *definitions, secgroup_t *configuration, factory_t *factory,tileinfo *info) ->void ;
	auto set(const std::filesystem::path &uodir,langmsg *language,secgroup_t *definitions, secgroup_t *configuration, factory_t *factory,tileinfo *info) ->void ;
	auto load() ->bool ;
};
#endif /* world_hpp */
