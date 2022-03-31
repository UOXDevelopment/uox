//Copyright © 2022 Charles Kerr. All rights reserved.

#include "tileinfo.hpp"
#include "strutil.hpp"
#include <iostream>
#include <algorithm>

using namespace std::string_literals;
//=========================================================
// info_t items
//=========================================================
const std::map<std::string, std::uint64_t> info_t::_flag_names={
	{"background"s,UO::background},{"holdable"s,UO::holdable},{"transparent"s,UO::transparent},
	{"translucent"s,UO::translucent},{"wall"s,UO::translucent},{"damaging"s,UO::damaging},
	{"impassable"s,UO::impassable},{"wet"s,UO::wet},{"unknownbit9"s,UO::unknownBit9},
	{"surface"s,UO::surface},{"climbable"s,UO::climable},{"stackable"s,UO::stackable},
	{"window"s,UO::window},{"noShoot"s,UO::noShoot},{"articleA"s,UO::articleA},
	{"articleAn"s,UO::articleAn},{"articleThe"s,UO::articleThe},{"foliage"s,UO::foliage},
	{"partialHue"s,UO::partialHue},{"noHouse"s,UO::noHouse},{"map"s,UO::map},
	{"container"s,UO::container},{"wearable"s,UO::wearable},{"lightSource"s,UO::lightSource},
	{"animated"s,UO::animated},{"hoverOver"s,UO::hoverOver},{"noDiagnol"s,UO::noDiagnol},
	{"armor"s,UO::armor},{"roof"s,UO::roof},{"door"s,UO::door},
	{"stairBack"s,UO::stairBack},{"stairRight"s,UO::stairRight},{"alphaBlend"s,UO::alphaBlend},
	{"useNewArt"s,UO::useNewArt},{"artUsed"s,UO::artUsed},{"noShadow"s,UO::noShadow},
	{"pixelBleed"s,UO::pixelBleed},{"animatedOnce"s,UO::animatedOnce},{"multiMove"s,UO::multiMove}
};
//=========================================================
auto info_t::setFlag(const std::string &flagname,bool value) ->void{
	auto mask = _flag_names.at(flagname);
	if (value){
		_flag |=mask ;
	}
	else {
		_flag &= (~mask) ;
	}

}
//=========================================================
info_t::info_t(tiletype_t type): _type(type),_flag(0),_texture(0),_weight(0),_quality(0),
					   _miscData(0),_unk2(0),_quantity(0),_animid(0),_unk3(0),
					   _hue(0),_stackingOffset(0),_value(0),_height(0) {
	
}

//=============================================================
// tile_t
//============================================================
//============================================================
tile_t::tile_t(tileid_t tileid,tiletype_t type):_tileid(tileid),_info(nullptr),_hue(0),_z(0),_type(type){
	
}
//============================================================

auto tile_t::raw(int xoffset,int yoffset) const ->std::vector<unsigned char> {
	auto data = std::vector<unsigned char>(3,0) ;
	std::copy(&_tileid,&_tileid+1,reinterpret_cast<tileid_t*>(data.data()));
	auto z = static_cast<char>(_z) ;

	std::copy(&z,&z + 1,reinterpret_cast<char*>(data.data()+2));
	if (this->_type == tiletype_t::art){
		data.resize(7,0);
		auto offset = static_cast<unsigned char>(xoffset);
		std::copy(&offset,&offset + 1,data.data()+2);
		offset = static_cast<unsigned char>(yoffset);
		std::copy(&offset,&offset + 1,data.data()+3);
		std::copy(&z,&z + 1,reinterpret_cast<char*>(data.data()+4));
		std::copy(&_hue,&_hue + 1,reinterpret_cast<std::uint16_t*>(data.data()+5));
	}
	return data ;
}

//=============================================================
// tileinfo
//============================================================
//============================================================
const std::string tileinfo::_tiledata_mul = "tiledata.mul"s;
//============================================================
tileinfo::tileinfo(): _usedHS(false){
	
}
//============================================================
auto tileinfo::loadTerrain(std::ifstream &input)->bool{
	_terrain.clear();
	_terrain.reserve(0x4000);
	std::uint32_t value32 = 0 ;
	std::uint64_t value64 =  0;
	std::array<char,20> string_buffer ;
	string_buffer.fill(0);
	for (auto i=0 ; i< 0x4000;i++){
		// We have to get rid of the header on blocks of information
		// HS has the firt entry messed up
		if (_usedHS) {
			if ( (((i & 0x1F)==0) && (i>0)) || (i == 1)){
				input.read(reinterpret_cast<char*>(&value32),4); // read off the group header
			}

		}
		else {
			if ( (i & 0x1f) == 0) {
				input.read(reinterpret_cast<char*>(&value32),4); // read off the group header
			}
		}
		// now create the info_t we will use
		auto info = info_t(tiletype_t::terrain);
		// read off the flags, 32 bit on pre-HS, 64 bit after
		if (_usedHS) {
			input.read(reinterpret_cast<char*>(&value64),8);
			info._flag = value64 ;
			
		}
		
		else{
			input.read(reinterpret_cast<char*>(&value32),4);
			info._flag = static_cast<std::uint64_t>(value32) ;
		}
		// only other thing for terrain is the texture
		// and name
		input.read(reinterpret_cast<char*>(&info._texture),2);
		input.read(string_buffer.data(),20);
		// We need to find the "0", if any
		auto iter = std::find(string_buffer.begin(),string_buffer.end(),0);
		info._name = std::string(string_buffer.begin(),iter);
		if (!input.good()){
			return false ;
		}
		_terrain.push_back(std::move(info));
	}
	return true ;
}
//============================================================
auto tileinfo::loadArt(std::ifstream &input)->bool{
	_art.clear();
	_art.reserve(0xFFFF);
	std::uint32_t value32 = 0 ;
	std::uint64_t value64 =  0;
	std::uint8_t value8 = 0 ;
	std::uint16_t value16 = 0;
	std::array<char,20> string_buffer ;
	string_buffer.fill(0);
	if (input.eof() || input.bad()){
		return false ;
	}
	auto loopcount = 0 ;
	do {
		if ( (loopcount & 0x1f) == 0) {
			input.read(reinterpret_cast<char*>(&value32),4); // read off the group header
		}
		auto info = info_t(tiletype_t::art);
		if (_usedHS) {
			input.read(reinterpret_cast<char*>(&value64),8);
			info._flag = value64;
			
		}
		else {
			input.read(reinterpret_cast<char*>(&value32),4);
			info._flag = static_cast<std::uint64_t>(value32);
			
		}
		input.read(reinterpret_cast<char*>(&value8),1);
		info._weight = value8;
		input.read(reinterpret_cast<char*>(&value8),1);
		info._quality = value8 ;
		//misc data
		input.read(reinterpret_cast<char*>(&value16),2);
		info._miscData = value16 ;
		//Second unkown
		input.read(reinterpret_cast<char*>(&value8),1);
		info._unk2 = value8 ;
		// Quantity
		input.read(reinterpret_cast<char*>(&value8),1);
		info._quantity = static_cast<int>(value8);
		// Animation
		input.read(reinterpret_cast<char*>(&value16),2);
		info._animid = value16 ;
		
		//Third a byte
		input.read(reinterpret_cast<char*>(&value8),1);
		info._unk3 = value8 ;
		
		// Hue/Value
		input.read(reinterpret_cast<char*>(&value8),1);
		info._hue = value8;
		//stacking offset
		input.read(reinterpret_cast<char*>(&value8),1);
		info._stackingOffset = value8 ;
		// value
		input.read(reinterpret_cast<char*>(&value8),1);
		info._value = value8 ;
		// Height
		input.read(reinterpret_cast<char*>(&value8),1);
		info._height = static_cast<int>(value8) ;
		// and name
		input.read(reinterpret_cast<char*>(&info._texture),2);
		input.read(string_buffer.data(),20);
		// We need to find the "0", if any
		auto iter = std::find(string_buffer.begin(),string_buffer.end(),0);
		info._name = std::string(string_buffer.begin(),iter);
		if (!input.good()){
			break ;
		}
		if (!input.eof()){
			_art.push_back(std::move(info));
		}
		loopcount++;

	}while( (!input.eof()) && input.good());
	
	return true ;
}
//============================================================
auto tileinfo::load(std::ifstream &input)->bool {
	if (loadTerrain(input)){
		return loadArt(input);
	}
	return false ;
}
//============================================================
auto tileinfo::load(const std::string &uodir_tiledata) ->bool {
	if (uodir_tiledata.empty()){
		return false ;
	}
	auto path = std::filesystem::path(uodir_tiledata);
	return load(path) ;
}
//============================================================
auto tileinfo::load(const std::filesystem::path &path)->bool {
	// Does this file exist?
	if (!std::filesystem::exists(path)) {
		return false ;
	}
	auto fp = path;
	if (std::filesystem::is_directory(fp)) {
		fp = fp / std::filesystem::path(_tiledata_mul);
	}
	if (!std::filesystem::exists(fp)) {
		return false;
	}

	auto size = std::filesystem::file_size(fp);
	if (size >= _size_for_HS){
		_usedHS=true ;
	}
	auto input = std::ifstream(fp.string(),std::ios::binary);
	if (input.is_open()){
		return load(input);
	}
	return false ;
}
//===============================================================
auto tileinfo::terrain(tileid_t tileid) const ->const info_t& {
	return _terrain[tileid];
}
//===============================================================
auto tileinfo::terrain(tileid_t tileid) ->info_t& {

	return _terrain[tileid];
}

//===============================================================
auto tileinfo::art(tileid_t tileid) const ->const info_t&{
	return _art[tileid];
}
//===============================================================
auto tileinfo::art(tileid_t tileid) ->info_t&{
	return _art[tileid];
}
//===============================================================
auto tileinfo::usedHS() const ->bool {
	return _usedHS;
}
//===============================================================
auto tileinfo::size(tiletype_t type) const ->std::size_t {
	switch (static_cast<int>(type)){
		case static_cast<int>(tiletype_t::terrain):
			return _terrain.size() ;
		case static_cast<int>(tiletype_t::art):
			return _art.size() ;
		default:
			return 0;
	}
}
