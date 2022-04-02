//Copyright © 2022 Charles Kerr. All rights reserved.

#include "region.hpp"

#include <iostream>

#include "section.hpp"
#include "strutil.hpp"
//=========================================================
worldregion_t::worldregion_t() :region_t(){
	guarded = false ;
	gate = true ;
	mark = true ;
	recall = true ;
	housing = true ;
}
//==========================================================
worldregion_t::worldregion_t(const worldregion_t& worldregion): worldregion_t(){
	this->areas = worldregion.areas ;
	this->guarded = worldregion.guarded ;
	this->mark = worldregion.mark ;
	this->recall = worldregion.recall ;
	this->housing = worldregion.housing ;
}
//==========================================================
auto worldregion_t::operator=(const worldregion_t &worldregion) ->worldregion_t& {
	this->areas = worldregion.areas ;
	this->guarded = worldregion.guarded ;
	this->mark = worldregion.mark ;
	this->recall = worldregion.recall ;
	this->housing = worldregion.housing ;
	return *this ;
}
//=========================================================
worldregion_t::worldregion_t(const section_t &section):worldregion_t(){
	for (const auto &entry : section.entries()){
		auto key = entry.key();

		if (key == "guarded"){
			guarded = strutil::ston<bool>(entry.value());
		}
		else if (key == "gate"){
			gate = strutil::ston<bool>(entry.value());

		}
		else if (key == "mark"){
			mark = strutil::ston<bool>(entry.value());
			
		}
		else if (key == "recall"){
			recall = strutil::ston<bool>(entry.value());
			
		}
		else if (key == "housing"){
			housing = strutil::ston<bool>(entry.value());
			
		}
		else if (key == "name"){
			name = entry.value();
			
		}
		else if (key == "area"){
			auto area = area_t(entry.value());
			add(area) ;
			
		}

	}
}
