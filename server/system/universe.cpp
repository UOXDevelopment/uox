//Copyright © 2022 Charles Kerr. All rights reserved.

#include "universe.hpp"

#include <iostream>
#include <array>
#include <fstream>

#include "secgroup.hpp"
#include "factory.hpp"
#include "langmsg.hpp"
#include "system_types.hpp"
#include "secgroup.hpp"
#include "serverlocation.hpp"
#include "strutil.hpp"
#include "region.hpp"

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
universe_t::~universe_t() {
	save() ;
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
		worlds[i].set(i,uodir,location->userdata[userloc_t::world],language,definitions,configuration,&factory,info) ;
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
	if (rvalue){
		std::cout <<"Loading world regions" << std::endl;
		loadWorldRegions();
		// We now load the raw data
		std::cout <<"Loading world save data."<<std::endl;
		loadObjects();
	}
	return rvalue ;
}
//=========================================================
auto universe_t::save() ->bool {
	std::unordered_map<objecttype_t, std::ofstream> nomap ;
	std::array<std::unordered_map<objecttype_t, std::ofstream>,ultima_maps> streams ;
	for (auto i=0 ; i < ultima_maps;++i) {
		for (const auto &entry : objecttypeNames()){
			if (entry.first != objecttype_t::base){
				auto loc = locations->userdata[userloc_t::world] / std::filesystem::path(strutil::format("world%i/%s.uox",i,entry.second.c_str()));
				streams[i].try_emplace(entry.first, loc.string()) ;
				if (!streams[i].at(entry.first).is_open()){
					std::cerr <<"Error creating save file: "<< loc.string()<<std::endl;
				}
			}
		}
	}
	// Now do the non map ones
	for (const auto &entry : objecttypeNames()){
		if (entry.first != objecttype_t::base){
			auto loc = locations->userdata[userloc_t::world] / std::filesystem::path(strutil::format("%s.uox",entry.second.c_str()));
			nomap.try_emplace(entry.first, loc.string()) ;
			if (!nomap.at(entry.first).is_open()){
				std::cerr <<"Error creating save file: "<< loc.string()<<std::endl;
			}
		}
	}
	for (const auto &nametype : objecttypeNames()){
		if (nametype.first != objecttype_t::base){
			for (const auto &entry : factory.items){
				auto path = &nomap[nametype.first] ;
				if (entry.second->location.world >=0){
					path = &streams[entry.second->location.world].at(nametype.first);
				}
				entry.second->save(*path);
			}

		}
	}
	return true ;
}

//======================================================================
auto universe_t::loadObjects() ->bool {
	auto worlddata = secgroup_t(locations->userdata[userloc_t::world].string(),true,".uox") ;
	// we now have all the world data
	for (const auto &type : worlddata.raw()){
		try {
			auto objectype = objecttypeForName(type.first) ;
			// Get all the sections for this type
			std::cout << "Creating saved objects of type: "<<type.first <<std::endl;
			for (const auto &section : type.second){
				auto serial = strutil::ston<serial_t>(section.first) ;
				auto object = factory.create(objectype,serial) ;
				object->loadWorldSection(section.second, &factory);
				if (object->location.world > -1){
					// we need to store it in the world
					worlds[object->location.world].add(object);
				}
			}
		}
		catch(...){
			// A type we dont know about
			std::cerr <<"Unknown world type found in saved data: "<<type.first<<std::endl;
		}
	}
	return true ;
}
//======================================================================
auto universe_t::loadWorldRegions() ->void {
	auto sections = configuration->type("worldregion");
	if (sections!=nullptr){
		for (const auto &section : *sections){
			auto parent = section.second.header().parent() ;
			auto maps = std::vector<int>{0};
			if (!parent.empty()){
				maps.clear() ;
				for (const auto &value : strutil::parse(parent,",")){
					maps.push_back(strutil::ston<int>(value));
				}
			}
			// We now have the maps this belongs to
			std::cout <<"Loading region :"<< section.first <<  std::endl;
			auto region = worldregion_t(section.second);
			for (auto worldnum : maps){
				worlds[worldnum].addWorldRegion(region);
			}
		}
		for (auto i=0 ; i< ultima_maps; ++i) {
			worlds[i].unwindWorldRegions();
			std::cout <<"World " << i<<" has " << worlds[i].regionCount()<<" world regions comprising of " << worlds[i].areaCount()<<" unique areas." << std::endl;
		}
	}
}
