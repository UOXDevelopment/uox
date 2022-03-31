//Copyright © 2022 Charles Kerr. All rights reserved.

#include "world.hpp"

#include <iostream>

#include "secgroup.hpp"
#include "factory.hpp"
#include "langmsg.hpp"

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
auto world_t::set( int mapnum,const std::filesystem::path &uodir,langmsg *language,secgroup_t *definitions, secgroup_t *configuration, factory_t *factory,tileinfo *info) ->void {
	number = mapnum ;
	set(uodir,language,definitions,configuration,factory,info);
}
//=========================================================
auto world_t::set( const std::filesystem::path &uodir,langmsg *language,secgroup_t *definitions, secgroup_t *configuration, factory_t *factory,tileinfo *info) ->void {
	this->uodir = uodir ;
	this->language = language ;
	this->definitions = definitions;
	this->configuration = configuration ;
	this->factory = factory ;
	this->info = info ;
	
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
