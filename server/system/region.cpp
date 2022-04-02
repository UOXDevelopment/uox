//Copyright © 2022 Charles Kerr. All rights reserved.

#include "region.hpp"

#include <iostream>

#include "section.hpp"
#include "strutil.hpp"
//=========================================================
worldregion_t::worldregion_t() {
	guarded = false ;
	gate = true ;
	mark = true ;
	recall = true ;
	housing = true ;
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
	}
}

