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
#include "netsupport.hpp"
#include "account.hpp"
#include "strutil.hpp"

using namespace std::string_literals ;

auto loadData(serverlocation &location, secgroup_t &configuration, secgroup_t &definition) ->bool ;


int main(int argc, const char * argv[]) {
	auto config_file  = "uox.cfg"s;
	auto retstatus = EXIT_FAILURE ;
	if (argc > 1){
		config_file = argv[1] ;
	}
	// Get the initializing network out of the way (a windows things)
	try {
		startNetwork() ;
	}
	catch(const std::exception &e) {
		std::cerr <<"Error initializing system network system: "<<e.what()<<std::endl;
		return EXIT_FAILURE ;
	}
	auto location = serverlocation() ;
	auto configuration = secgroup_t() ;
	auto definition = secgroup_t() ;
	auto langauges = langmsg() ;
	
	if (location.load(config_file)) {
		loadData(location,configuration, definition);
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
					// the worlds are loaded, objects recreated
					// Load accounts
					auto account_create = true ;
					auto actkeyvalue = servercfg->last("autoaccount");
					if (actkeyvalue){
						account_create = strutil::ston<bool>(actkeyvalue->value());
					}
					
					auto account = actholder_t(account_create,&universe.factory) ;
					std::cout <<"Loading account information: " ;
					account.set(location.userdata[userloc_t::access].string()) ;
					std::cout <<account.size() <<" accounts."<<std::endl;
					// Load network
				}
			}

		}
		else {
			std::cerr <<"Can not find server configuration."<<std::endl;
		}
	}
	stopNetwork();
	
	return retstatus;
}

//===========================================================================================
auto loadData(serverlocation &location,secgroup_t &configuration, secgroup_t &definition) ->bool {
	std::cout <<"Loading configuration data."<< std::endl;
	// Now load the configuration data
	auto rvalue = configuration.load(location.serverdata[serverloc_t::configuration].string(),true,".cfg") ;
	rvalue = configuration.load(location.userdata[userloc_t::configuration].string(),true,".cfg");
	
	std::cout <<"Loading definition data."<< std::endl;
	
	rvalue =  definition.load(location.serverdata[serverloc_t::configuration].string(),true,".cfg") ;
	rvalue =  definition.load(location.userdata[userloc_t::definition].string(),true,".cfg");
	
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
	return rvalue ;
	
}
