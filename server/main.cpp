//
// Copyright © 2022 Charles Kerr. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <filesystem>
#include <thread>
#include <algorithm>

#include "serverlocation.hpp"
#include "secgroup.hpp"
#include "tileinfo.hpp"
#include "langmsg.hpp"
#include "universe.hpp"

using namespace std::string_literals ;
int main(int argc, const char * argv[]) {
	auto config_file  = "uox.cfg"s;
	auto retstatus = EXIT_FAILURE ;
	if (argc > 1){
		config_file = argv[1] ;
	}
	auto location = serverlocation() ;
	if (location.load(config_file)) {
		std::cout <<"Loading configuration data."<< std::endl;
		// Now load the configuration data
		secgroup_t configuration = secgroup_t(location.serverdata[serverloc_t::configuration].string(),true,".cfg") ;
		configuration.load(location.userdata[userloc_t::configuration].string(),true,".cfg");

		std::cout <<"Loading definition data."<< std::endl;

		secgroup_t definition = secgroup_t(location.serverdata[serverloc_t::configuration].string(),true,".cfg") ;
		definition.load(location.userdata[userloc_t::definition].string(),true,".cfg");
	
		std::cout <<"Loading language data." << std::endl;
		


		// We now have the configuration/definition data
		std::cout <<"Normalizing configuration data."<< std::endl;
		// we now need to normalize it
		auto normalize = configuration.section("normalize", "config") ;
		if (normalize != nullptr){
			for (auto &entry : normalize->entries()){
				if (entry.key()=="type"){
					configuration.normalize(entry.value());
				}
			}
		}
		std::cout <<"Normalizing definition data."<< std::endl;
		normalize = definition.section("normalize", "config") ;
		if (normalize != nullptr){
			for (auto &entry : normalize->entries()){
				if (entry.key()=="type"){
					definition.normalize(entry.value());
				}
			}
		}

		std::cout <<"Removing requested configuration sections."<< std::endl;
		// we need to remove sections
		auto removal = configuration.type("remove") ;
		if (removal != nullptr){
			for (auto &sectype : *removal){
				auto type = sectype.second.header().identifier() ;
				for (auto &entry : sectype.second.entries()) {
					if (entry.key() == "id"){
						configuration.remove(type, entry.value());
					}
				}
			}
		}
		std::cout <<"Removing requested definition sections."<< std::endl;
		removal = definition.type("remove") ;
		if (removal != nullptr){
			for (auto &sectype : *removal){
				auto type = sectype.second.header().identifier() ;
				for (auto &entry : sectype.second.entries()) {
					if (entry.key() == "id"){
						definition.remove(type, entry.value());
					}
				}
			}
		}
		// Before we go any further, get the server configuration, we need some information
		auto servercfg = configuration.section("", "server");
		if ( servercfg){
			auto deflang = language_t::english ;
			try {
				deflang =languageForName(servercfg->last("language")->value());
			}
			catch(...){
				// Do nothing, just continue on, language entry in server section not found or invalid
				std::cerr <<"Server language not found/invalid, defaulting to english." << std::endl;
			}
			std::cout <<"Loading languages."<<std::endl;
			auto languages = langmsg(deflang) ;
			languages.load(location.serverdata[serverloc_t::language].string(),true,".lang") ;
			languages.load(location.userdata[userloc_t::language].string(),true,".lang") ;
			std::cout <<"Loaded " << languages.size() << " languages." << std::endl;
			std::cout << "Loading Ultima tile information." << std::endl;
			auto tiledata = tileinfo() ;
			if (tiledata.load(location.ultima)){
				universe_t universe ;
				universe.set(&location, &languages, &definition, &configuration, &tiledata);
				if (universe.load()) {
					
				}
			}

		}
		else {
			std::cerr <<"Can not find server configuration."<<std::endl;
		}
	}
	
	
	return retstatus;
}
