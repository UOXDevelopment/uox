//Copyright © 2022 Charles Kerr. All rights reserved.

#include "terrainblock.hpp"

#include <iostream>
#include <algorithm>


//=========================================================
auto terrainblock::terrain(int x, int y) ->tile_t & {
	return _tiles[x][y] ;
}
//=========================================================
auto terrainblock::terrain(int x, int y) const -> const tile_t& {
	return _tiles[x][y] ;
}

//=========================================================
terrainblock::terrainblock(const std::vector<unsigned char> &data ,tileinfo *info) {
	if (!data.empty()){
		load(data,info);
	}
}


//===================================================================
// Data is stored n rows, eight cells wide.  There is 8 rows.
// A cell is a two bytes for tileid, and one byte for altitude
// There is also a 4 byte "header" at the beginning of the block
//=========================================================
auto terrainblock::load(const std::vector<unsigned char>& data,tileinfo *info)->void {
	
	if(data.size() == 196) {
		for ( auto y = 0 ; y < 8 ; y++) {
			for (auto x = 0 ; x < 8 ; x++){
				auto offset = (y*24) + (x*3) + 4 ;
				std::copy(data.data()+offset, data.data()+offset+2,reinterpret_cast<std::uint8_t*>(&_tiles[x][y]._tileid )) ;
				_tiles[x][y]._z = static_cast<int>(*reinterpret_cast<const char*>(data.data()+offset+2));
				if (info != nullptr){
					// Update the info for this tile
					_tiles[x][y]._info = &info->terrain(_tiles[x][y]._tileid);
				}
			}
		}
	}
}
//=========================================================
auto terrainblock::updateInfo(tileinfo *info){
	if (info != nullptr){
		for (auto y = 0; y< 8 ; y++){
			for (auto x = 0; x< 8 ; x++){
				_tiles[x][y]._info = &(info->terrain(_tiles[x][y]._tileid));
			}
		}
	}
}
//=========================================================

auto terrainblock::raw() const  ->std::vector<unsigned char> {
	std::vector<unsigned char> data;
	data.reserve(192);
	; // 8X8 and each tile is 3 bytes
	//Data is stored row at a time
	for (auto y=0;y<8;y++){
		for (auto x=0;x<8;x++){
			auto tiledata = _tiles[x][y].raw(x,y) ;
			std::copy(tiledata.begin(),tiledata.end(),std::back_inserter(data));
		}
	}
	return data ;
}

