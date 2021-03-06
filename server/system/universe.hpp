//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef universe_hpp
#define universe_hpp

#include <cstdint>
#include <filesystem>
#include <string>
#include <array>

#include "serial_generator.hpp"
#include "world.hpp"
#include "factory.hpp"
#include "uomulti.hpp"

class secgroup_t ;
class langmsg ;
struct serverlocation;
class tileinfo ;

//=========================================================
struct universe_t {
	
private:
	auto loadObjects() ->bool ;
	auto loadWorldRegions() ->void ;
	auto loadInstaLog() ->void ;
	auto loadSos() ->void ;
	auto loadRegions() ->void ;
public:

	static constexpr auto ultima_maps = 6 ;


	// We have our worlds
	std::array<world_t,ultima_maps> worlds ;
	// the ultmia multis
	uomulti multicollection;
	// server locations/data
	std::filesystem::path uodir ;
	langmsg *language ;
	secgroup_t *definitions ;
	secgroup_t *configuration ;
	tileinfo *info ;
	serial_generator generator ;
	factory_t factory ;
	serverlocation *locations ;
	
	universe_t() ;
	~universe_t() ;
	
	universe_t(const universe_t&) = delete ;
	auto operator=(const universe_t&) ->universe_t& = delete ;
	
	auto set(serverlocation *location,langmsg *language,secgroup_t *definitions, secgroup_t *configuration, tileinfo *info) ->void ;
	auto load() ->bool ;
	auto save() ->bool ;
};
#endif /* universe_hpp */
