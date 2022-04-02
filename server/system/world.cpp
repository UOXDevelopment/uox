//Copyright © 2022 Charles Kerr. All rights reserved.

#include "world.hpp"

#include <iostream>

#include "secgroup.hpp"
#include "factory.hpp"
#include "langmsg.hpp"
#include "strutil.hpp"

using namespace std::string_literals;

//=========================================================
world_t::world_t(int mapnum) {
	number = mapnum ;
	
	info = nullptr ;
	language = nullptr ;
	definitions = nullptr;
	configuration = nullptr;
	factory = nullptr ;
}
//=========================================================
auto world_t::set( int mapnum,const std::filesystem::path &uodir,const std::filesystem::path &worldloc,langmsg *language,secgroup_t *definitions, secgroup_t *configuration, factory_t *factory,tileinfo *info) ->void {
	number = mapnum ;
	set(uodir,worldloc,language,definitions,configuration,factory,info);
}
//=========================================================
auto world_t::set( const std::filesystem::path &uodir,const std::filesystem::path &worldloc,langmsg *language,secgroup_t *definitions, secgroup_t *configuration, factory_t *factory,tileinfo *info) ->void {
	this->uodir = uodir ;
	this->language = language ;
	this->definitions = definitions;
	this->configuration = configuration ;
	this->factory = factory ;
	this->info = info ;
	worldpath = worldloc / std::filesystem::path(strutil::format("world%i",number));
	if (!std::filesystem::exists(worldpath)){
		std::filesystem::create_directories(worldpath);
	}
}
//=========================================================
auto world_t::load() ->bool {
	auto rvalue = false ;
	if (!uodir.empty() && (number >=0) && (language!=nullptr) && (definitions != nullptr) && (configuration != nullptr) && (factory!=nullptr) && (info != nullptr)){
		ultimamap.set(number,0,0);
		rvalue = ultimamap.load(uodir, info) ;
	}
	return rvalue ;
}

//=========================================================
auto world_t::addWorldRegion(const worldregion_t &region)->void{
	worldregions.push_back(region) ; // this makes a copy, so region_t had a copy constructor to accomdate the internal pointers
}
//=========================================================
auto world_t::unwindWorldRegions() ->void {
	worldareas.clear() ;
	for (const auto &region : worldregions){
		worldareas.insert(std::end(worldareas),std::begin(region.areas),std::end(region.areas));
	}
	// now we need to sort them
	std::sort(worldareas.begin(),worldareas.end(),[](const area_t &lhs, const area_t &rhs){
		return lhs.boundary.size() < rhs.boundary.size();
	});
}
//=========================================================
auto world_t::add(baseobj_t *object) ->void {
	
}
