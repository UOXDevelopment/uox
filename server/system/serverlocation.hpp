//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef serverlocation_hpp
#define serverlocation_hpp

#include <cstdint>

#include <filesystem>
#include <string>
#include <map>

#include "system_types.hpp"
//=========================================================
struct serverlocation {
	std::map<serverloc_t,std::filesystem::path> serverdata ;
	std::map<userloc_t,std::filesystem::path> userdata ;
	std::filesystem::path data ;
	std::filesystem::path user ;
	std::filesystem::path ultima ;
	auto load(const std::string &file) ->bool ;
private:
	auto validateDataPath(std::filesystem::path &path) ->bool ;
	auto validateUserPath(std::filesystem::path &path, bool create) ->bool ;
};

#endif /* serverlocation_hpp */
