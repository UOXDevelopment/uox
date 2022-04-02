//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef world_hpp
#define world_hpp

#include <cstdint>
#include <string>
#include <filesystem>
#include <vector>

#include "uomap.hpp"
#include "position_types.hpp"
#include "region.hpp"
class secgroup_t ;
class langmsg ;
struct factory_t ;
struct baseobj_t ;
//=========================================================
struct world_t {
	
	// ultima number and map
	int number ;
	uomap ultimamap ;
	// system variables
	std::filesystem::path uodir ;
	std::filesystem::path worldpath ;
	langmsg *language ;
	secgroup_t *definitions ;
	secgroup_t *configuration ;
	factory_t *factory ;
	tileinfo *info ;
	

	// world data
	std::vector<worldregion_t> worldregions ;
	std::vector<area_t> worldareas ;
	
	world_t(int mapnum=-1) ;
	auto set(int mapnum,const std::filesystem::path &uodir,const std::filesystem::path &worldloc,langmsg *language,secgroup_t *definitions, secgroup_t *configuration, factory_t *factory,tileinfo *info) ->void ;
	auto set(const std::filesystem::path &uodir,const std::filesystem::path &worldloc, langmsg *language,secgroup_t *definitions, secgroup_t *configuration, factory_t *factory,tileinfo *info) ->void ;
	auto load() ->bool ;
	auto add(baseobj_t *object) ->void ;
	auto addWorldRegion(const worldregion_t &region)->void;
	auto unwindWorldRegions() ->void ;
	
};
#endif /* world_hpp */
