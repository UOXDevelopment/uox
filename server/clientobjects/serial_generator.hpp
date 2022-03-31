//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef serial_generator_hpp
#define serial_generator_hpp

#include <cstdint>
#include <atomic>
//#include <filesystem>

#include "object_types.hpp"

//=========================================================
class serial_generator {
	std::atomic<serial_t> item_serial ;
	std::atomic<serial_t> mob_serial ;

	//std::filesystem::path worlddir ;
public:
	static constexpr auto itemstart = serial_t(0x40000000) ;
	static constexpr auto mobstart =  serial_t(0x00000001) ;

	serial_generator(const serial_generator&) = delete ; // We can only have one of these
	auto operator=(const serial_generator&) ->serial_generator& = delete ; // Cant assign one either
	
	serial_generator() ;
	
	auto serial(objecttype_t type) ->serial_t ;
	auto usedSerial(serial_t serial) ->void ;
	
	
};
#endif /* serial_generator_hpp */
