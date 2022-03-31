//Copyright © 2022 Charles Kerr. All rights reserved.

#include "serial_generator.hpp"

#include <iostream>
#include <algorithm>

//=========================================================
serial_generator::serial_generator() {
	item_serial = itemstart ;
	mob_serial = mobstart ;
}
//=========================================================
auto serial_generator::serial(objecttype_t type) ->serial_t {
	auto serial = serial_t(invalid_serial) ;
	switch (static_cast<int>(type)) {
		case static_cast<int>(objecttype_t::item):
		case static_cast<int>(objecttype_t::spawner):
		case static_cast<int>(objecttype_t::multi):
			serial = ++item_serial ;
			break;
		case static_cast<int>(objecttype_t::mob):
		case static_cast<int>(objecttype_t::player):
			serial = ++mob_serial ;
			break;

		default:
			break;
	}
	return serial ;
}
//=========================================================
auto serial_generator::usedSerial(serial_t serial) ->void {
	if ((serial >= mobstart)  && (serial < itemstart)){
		// This is a mob type serial
		mob_serial = std::max(mob_serial.load(),serial) ;
	}
	else {
		item_serial = std::max(item_serial.load(),serial) ;
	}
}
