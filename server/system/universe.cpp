//Copyright © 2022 Charles Kerr. All rights reserved.

#include "universe.hpp"

#include <iostream>

#include "secgroup.hpp"
#include "factory.hpp"
#include "langmsg.hpp"
#include "serverlocation.hpp"

using namespace std::string_literals;
//=========================================================
universe_t::universe_t() {
	
	language =nullptr;
	definitions =nullptr;
	configuration =nullptr;
	info =nullptr ;
	locations = nullptr ;

}
//=========================================================
auto universe_t::set(serverlocation *location, langmsg *language,secgroup_t *definitions, secgroup_t *configuration,tileinfo *info) ->void{
	this->locations = location ;
	
	this->language = language ;
	this->definitions = definitions;
	this->configuration = configuration ;
	this->info = info ;
	uodir = locations->ultima ;
	factory.set(info, &multicollection, definitions, configuration, language);
	for (auto i=0 ; i< ultima_maps; ++i){
		worlds[i].set(i,uodir,language,definitions,configuration,&factory,info) ;
	}
}
//=========================================================
auto universe_t::load() ->bool {
	auto rvalue = true ;
	std::cout <<"Loading ultima multis."<<std::endl;
	rvalue = multicollection.load(uodir, info);
	if (rvalue){
		for (auto i=0 ; i< ultima_maps; ++i){
		std::cout <<"Loading ultima map: "<<i<<std::endl;
		if (!(rvalue = worlds[i].load())) {
			std::cerr <<"Error loading ultima map " << i<<std::endl;
		}
		}
	}
	else {
		std::cerr <<"Error loading ultima multis."<<std::endl;
	}
	return rvalue ;
}
