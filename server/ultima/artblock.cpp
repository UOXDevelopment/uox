//Copyright © 2022 Charles Kerr. All rights reserved.

#include "artblock.hpp"

#include <iostream>
#include <algorithm>

//=========================================================
artblock::artblock(const std::vector<unsigned char> &data , tileinfo *info){
	if (!data.empty()) {
		load(data,info);
	}
}
//=========================================================
auto artblock::load(const std::vector<unsigned char> &data, tileinfo *info )->void{

	for (auto& entry : _tiles) {
		for (auto& tile : entry) {
			tile.clear();
		}
	}

// 	_tiles = std::array<std::array<std::vector<tile_t>,8>,8>() ;
	auto count = static_cast<int>(data.size()) / 7 ;
	for (auto i = 0 ; i<count ; i++){
		auto offset = i*7 ;
		auto tile = tile_t() ;
		tile._type = tiletype_t::art ;
		std::copy(data.data()+offset, data.data()+offset+2,reinterpret_cast<std::uint8_t*>(&tile._tileid )) ;
		auto xloc = static_cast<int>(*(data.data()+offset+2)) ;
		auto yloc = static_cast<int>(*(data.data()+offset+3)) ;
		tile._z = static_cast<int>(*reinterpret_cast<const char*>(data.data()+offset+4));
		std::copy(data.data()+offset+5, data.data()+offset+7,reinterpret_cast<std::uint8_t*>(&tile._hue )) ;
		if (info != nullptr){
			tile._info = &info->art(tile._tileid);
		}
		_tiles[xloc][yloc].push_back(std::move(tile)) ;
		
	}

}
//=========================================================
auto artblock::tiles(int x, int y) -> std::vector<tile_t> & {
	return _tiles[x][y];
}
//=========================================================
auto artblock::tiles(int x, int y) const -> const std::vector<tile_t>& {
	return _tiles[x][y];
}

//=========================================================
auto artblock::raw() const ->std::vector<unsigned char> {
	auto blockdata = std::vector<unsigned char>() ;
	for (auto y=0;y<8;y++){
		for (auto x=0;x<8;x++){
			for (const auto &tile : _tiles[x][y]){
				auto tiledata = tile.raw(x,y) ;
				if (!tiledata.empty()) {
					std::copy(tiledata.begin(),tiledata.end(),std::back_inserter(blockdata));
				}
			}
		}
	}
	return blockdata ;
}
