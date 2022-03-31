//Copyright © 2022 Charles Kerr. All rights reserved.

#include "serverlocation.hpp"

#include <iostream>
#include <fstream>
#include "secgroup.hpp"

using namespace std::string_literals;
//=========================================================
auto serverlocation::load(const std::string &file) ->bool {
	auto rvalue1 = false ;
	auto rvalue2 = false ;
	auto rvalue3 = false ;
	auto secgroup = secgroup_t();
	
	if (secgroup.load(file)) {
		auto section = secgroup.section("", "location");
		if (section != nullptr){
			for (const auto &modtype : servmodNames()){
				auto keyvalue = section->last(modtype.second) ;
				if (keyvalue != nullptr) {
					auto value = keyvalue->value() ;
					if (modtype.first == servmod_t::data) {
						data = std::filesystem::path(value) ;
						rvalue1  = validateDataPath(data);
						if (!rvalue1){
							break;
						}
					}
					else if (modtype.first == servmod_t::user){
						user = std::filesystem::path(value) ;
						rvalue2  = validateUserPath(user,true);
						if (!rvalue2){
							break;
						}

					}
					else if (modtype.first == servmod_t::ultima){
						ultima = std::filesystem::path(value) ;
						rvalue3 = std::filesystem::exists(ultima);
						if (!rvalue3){
							std::cerr << "Ultima Online data directory not found: "<<ultima.string()<<std::endl;
							break;
						}
						
					}
				}
			}
		}
		else {
			std::cerr <<"Unable to process section [location] in cfg file: "<<file << std::endl;
		}
	}
	else {
		std::cerr <<"Unable to open uox config file: "<<file << std::endl;
	}
	return rvalue1&&rvalue2&&rvalue3 ;
}

//=========================================================
auto serverlocation::validateDataPath(std::filesystem::path &path) ->bool {
	auto rvalue = false ;
	for (const auto &entry : serverlocNames()){
		auto loc = path / std::filesystem::path(entry.second) ;
		serverdata[entry.first] = loc ;
		rvalue = std::filesystem::exists(loc) ;
		if (!rvalue){
			std::cerr <<"Server data location does not exist: "<<loc.string()<<std::endl;
			break;
		}
	}
	return rvalue ;
}
//=========================================================
auto serverlocation::validateUserPath(std::filesystem::path &path, bool create) ->bool {
	auto rvalue = false ;
	for (const auto &entry : userlocNames()){
		auto loc = path / std::filesystem::path(entry.second) ;
		userdata[entry.first] = loc ;
		rvalue = std::filesystem::exists(loc) ;
		if (!rvalue){
			std::cerr <<"User data location does not exist: "<<loc.string()<<std::endl;
			if (create){
				rvalue = std::filesystem::create_directories(loc);
				if (!rvalue){
					std::cerr <<"Unable to create user data location does not exist: "<<loc.string()<<std::endl;
					break;
				}
				else {
					std::cerr <<"Created directory" << std::endl;
				}
			}
			else {
				break;
			}
		}
	}

	return rvalue ;
}

