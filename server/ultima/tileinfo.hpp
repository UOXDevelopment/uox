//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef tileinfo_hpp
#define tileinfo_hpp

#include <cstdint>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

#include "ultima_types.hpp"
//===============================================================
// What about the information for a tile?  All tiles have flags, and name.
// Terrain tiles have a texture_id, and art tiles have various attributes.
// In the past, it was important to match the size of the attribute to what
// was in the binary file, for people did complete record reads.  Of course,
// since the data wasn't aligned, one had to pack structures, and not what,
// which then lead to error when accessing the data from the struct.
//
// There is NO reason to keep the data the same size as in the binary file (other
// then some small memory savings).  And it can cause havoc with overflows during
// calculation.  (Now, note, that when included in packets, the data would need
// to be sized).  So these sizes DO NOT represent the size in the binary file.
//===============================================================
struct info_t {
private:
	static const std::map<std::string, std::uint64_t> _flag_names ;
public:
	auto setFlag(const std::string &flagname,bool value) ->void;
	info_t(tiletype_t type = tiletype_t::invalid);
	
	tiletype_t _type ;
	
	// Common attributes
	std::string _name ;
	std::uint64_t _flag ;
	
	// Terrain only attribute
	std::uint16_t _texture ; // std::uint16_t in binary file
	// Art only attributes
	std::uint8_t _weight ;  // std::uint8_t in data
	std::uint8_t _quality ; // std::uint8_t in data
	std::int16_t _miscData ; // std::uint16_t in data
	std::uint8_t _unk2 ;	// std::uint8_t in data
	int _quantity ;	// std::uint8_t in data
	std::uint16_t _animid ;
	std::uint8_t _unk3 ;	// std::uint8_t in data
	std::uint8_t _hue ;	// std::uint8_t in data
	std::uint8_t _stackingOffset ;  // unk4
	std::uint8_t _value ; // unk5 , std::uint8_t in data
	int  _height ; // This is a uint8_t in the data,

};
//===============================================================
// The concept of a tile, contains it tileid, info
//================================================================
struct tile_t {
	tile_t(tileid_t tileid = invalid_tileid,tiletype_t type = tiletype_t::terrain) ;
	tiletype_t _type ;  // yes, it is in the info information as well
	tileid_t _tileid ;
	const info_t *_info ;
	int _z ;
	std::uint16_t _hue ;
	auto raw(int xoffset=0,int yoffset=0) const ->std::vector<unsigned char> ;
};

//==================================================================
// tileinfo - reads and parses the UO tiledata.mul
//=================================================================
class tileinfo {
private:
	static const std::string _tiledata_mul ;
	static constexpr auto _size_for_HS = 3188736 ;
	bool _usedHS ;
	
	std::vector<info_t> _terrain ;
	std::vector<info_t> _art ;
	
	auto loadTerrain(std::ifstream & input)->bool ;
	auto loadArt(std::ifstream & input)->bool ;
	auto load(std::ifstream &input)->bool;
public:
	tileinfo() ;
	tileinfo(const tileinfo&) = delete ;
	auto operator=(const tileinfo&) -> tileinfo& = delete;
	
	auto load(const std::string &uodir_tiledata) ->bool ;
	auto load(const std::filesystem::path &path)->bool ;
	
	auto terrain(tileid_t tileid) const  ->const info_t&;
	auto terrain(tileid_t tileid) ->info_t&;
	
	auto art(tileid_t tileid) const ->const info_t&;
	auto art(tileid_t tileid) ->info_t&;

	auto usedHS() const ->bool ;
	auto size(tiletype_t type) const ->std::size_t ;
};

#endif /* tileinfo_hpp */
