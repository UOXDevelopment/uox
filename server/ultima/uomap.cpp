//Copyright © 2022 Charles Kerr. All rights reserved.

#include "uomap.hpp"
#include "strutil.hpp"

#include <iostream>
#include <fstream>

using namespace std::string_literals;
//=========================================================
// Our string constants
//=========================================================

const std::string uomap::_mapmul ="map%i.mul"s;
const std::string uomap::_mapuop = "map%iLegacyMUL.uop"s;
const std::string uomap::_staidx = "staidx%i.mul"s;
const std::string uomap::_stamul = "statics%i.mul"s;
const std::string uomap::_mapdifl = "mapdifl%i.mul"s;
const std::string uomap::_mapdif = "mapdif%i.mul"s;
const std::string uomap::_stadifl = "stadifl%i.mul"s;
const std::string uomap::_stadifi = "stadifi%i.mul"s;
const std::string uomap::_stadif = "stadif%i.mul"s;
const std::string uomap::_uophash = "build/map%ilegacymul/%s"s ;
const std::string uomap::_uophash_trailer = "%.8u.dat"s;

//==========================================================
auto uomap::defaultSizeForMap(int number) -> std::pair<int,int> {
	auto index = number*2 ;
	return std::make_pair(_mapsizes[index],  _mapsizes[index+1]) ;
}

//=========================================================
uomap::uomap():_width(0), _height(0),
_map_number(-1), _art_diff_count(0), _terrain_diff_count(0), _uop(false) {

}
//=========================================================
uomap::uomap(int mapnumber , int width, int height):uomap() {
	
	set(mapnumber, width, height);
}
//=========================================================
auto uomap::set(int mapnumber, int width, int height) ->void {
	_map_number = mapnumber;
	_width = width;
	_height = height;
	if ((width == 0) || (height == 0)) {
		// We look up the mapnumber
		auto index = mapnumber * 2;
		_width = _mapsizes[index];
		_height = _mapsizes[index + 1];
	}
	// Now, we need the number of blocks!
	auto totalblocks = (_width / 8) * (_height / 8);
	_terrain.resize(totalblocks);
	_art.resize(totalblocks);
}
//=============================================================================
auto uomap::loadTerrain(const std::filesystem::path &uodir,tileinfo *info)->bool{
	// So first, build the map
	auto path = uodir ;
	auto uoppath= path / std::filesystem::path(strutil::format(_mapuop,_map_number)) ;
	// Does that exist?
	if (std::filesystem::exists(uoppath)){
		// It does, is is a valid uop?
		_uop = isUOP(uoppath.string());
		if (_uop){
			// We will process this one
			return loadUOP(uoppath.string(),0x300,strutil::format(_uophash,_map_number,_uophash_trailer.c_str()),info);
		}
	}
	// Made it to here, lets try the mul file
	auto mulpath = uodir / std::filesystem::path(strutil::format(_mapmul,_map_number)) ;
	if (std::filesystem::exists(mulpath)){
		return loadTerrainMul(mulpath, info);
	}
	return false ;
}

//=============================================================================
auto uomap::loadTerrainMul(const std::filesystem::path &filepath,tileinfo *info)->bool {
	if (filepath.empty()){
		return false ;
	}
	auto input = std::ifstream(filepath.string(),std::ios::binary);
	if (!input.is_open()){
		return false ;
	}
	// We are all ready sized correctly, so lets just run the blocks
	auto data = std::vector<unsigned char>(196,0);
	for (auto &block : _terrain){
		input.read(reinterpret_cast<char*>(data.data()),196);
		if (input.gcount()==196){
			block.load(data, info);
		}
		else {
			return false ;
		}
	}
	return true;
}

//============================================================================
auto uomap::loadArt(const std::filesystem::path &uodir,tileinfo *info)->bool {
	auto path = uodir ;
	auto idxpath = path / std::filesystem::path(strutil::format(_staidx,_map_number)) ;
	auto mulpath = path / std::filesystem::path(strutil::format(_stamul,_map_number)) ;
	auto idx = std::ifstream(idxpath.string(),std::ios::binary);
	auto mul = std::ifstream(mulpath.string(),std::ios::binary);
	if (!idx.is_open() || !mul.is_open()){
		return false ;
	}
	auto offset = std::uint32_t(0) ;
	auto length = std::uint32_t(0) ;
	auto block = std::uint32_t(0);
	while (idx.good() && !idx.eof()){
		idx.read(reinterpret_cast<char*>(&offset),sizeof(offset));
		idx.read(reinterpret_cast<char*>(&length),sizeof(length));
		idx.seekg(sizeof(offset),std::ios::cur);
		if (idx.gcount() == sizeof(length)){
			// We know the read was good !
			if ((length < 0xFFFFFFFE) && (offset < 0xFFFFFFFE) && (length >0)) {
				mul.seekg(offset,std::ios::beg) ;
				auto data = std::vector<unsigned char>(length,0) ;
				mul.read(reinterpret_cast<char*>(data.data()),length);
				if ((mul.gcount() != length) || (block >= _art.size())){
					return false ;
				}
				_art[block].load(data,info);
			}
			else {
				_art[block].load(std::vector<unsigned char>(),nullptr);
			}
		}
		block++;
	}

	return true ;
}
//============================================================================
auto uomap::loadTerrainDiff(const std::filesystem::path &uodir,tileinfo *info)->int {
	auto path = uodir ;
	auto diflpath = path / std::filesystem::path(strutil::format(_mapdifl,_map_number));
	auto difpath = path / std::filesystem::path(strutil::format(_mapdif,_map_number));
	auto difl = std::ifstream(diflpath.string(),std::ios::binary);
	auto dif = std::ifstream(difpath.string(),std::ios::binary);
	if (!difl.is_open() || !dif.is_open()){
		return 0 ;
	}
	// So we have some diffs!
	auto diffcount = 0 ;
	auto block = std::uint32_t(0) ;
	auto data = std::vector<unsigned char>(196,0) ;
	
	while (difl.good() && !difl.eof() && dif.good() ){
		difl.read(reinterpret_cast<char*>(&block),sizeof(block));
		if (difl.gcount() == sizeof(block)){
			// Check to ensure the block is valid!
			if (block >= _terrain.size()){
				break;
			}
			dif.read(reinterpret_cast<char*>(data.data()),data.size());
			if (dif.gcount()== data.size()){
				_terrain[block].load(data, info);
				diffcount++;
			}
		}
	}
	return diffcount ;
}
//============================================================================
auto uomap::loadArtDiff(const std::filesystem::path &uodir,tileinfo *info)->int {
	auto path = uodir ;
	auto diflpath = path / std::filesystem::path(strutil::format(_stadifl,_map_number));
	auto difpath = path / std::filesystem::path(strutil::format(_stadif,_map_number));
	auto difipath = path / std::filesystem::path(strutil::format(_stadifi,_map_number));
	auto difl = std::ifstream(diflpath.string(),std::ios::binary);
	auto dif = std::ifstream(difpath.string(),std::ios::binary);
	auto difi = std::ifstream(difipath.string(),std::ios::binary);
	if (!difl.is_open() || !dif.is_open() || !difi.is_open()){
		return 0 ;
	}
	auto block = std::uint32_t(0) ;
	auto offset = std::uint32_t(0) ;
	auto length = std::uint32_t(0) ;
	auto diffcount = 0 ;
	while (difl.good() && !difl.eof() && difi.good() && dif.good()){
		difl.read(reinterpret_cast<char*>(&block),sizeof(block)) ;
		if (difl.gcount() == sizeof(block)){
			if (block >= _art.size()){
				break;
			}
			difi.read(reinterpret_cast<char*>(&offset),sizeof(offset));
			difi.read(reinterpret_cast<char*>(&length),sizeof(length));
			difi.seekg(sizeof(length),std::ios::cur);
			if (difi.gcount()==sizeof(length)){
				// The read was good!
				if ((offset < 0xFFFFFFFE) && (length>0) && (length < 0xFFFFFFFE)){
					// we have data for a block
					dif.seekg(offset,std::ios::beg);
					auto data = std::vector<unsigned char>(length,0);
					dif.read(reinterpret_cast<char*>(data.data()),length);
					if (dif.gcount() == length){
						_art[block] = artblock(data,info);
						diffcount++;
					}
				}
				else {
					_art[block] = artblock() ;
					diffcount++;
				}
				
			}
		}
	}
	return diffcount;
}
//============================================================================
auto uomap::indexForCoord(int x, int y, int height) -> std::tuple<int, int, int> {
	auto blockx = x/8 ;
	auto blocky = y/8 ;
	auto block = (blockx* (height/8) ) + blocky ;
	auto offsetx = x%8 ;
	auto offsety = y%8 ;
	return std::make_tuple(block,offsetx,offsety);

}
//============================================================================
auto uomap::indexForCoord(int x, int y) const ->std::tuple<int,int,int>{
	return indexForCoord(x,y, _height);
}

//============================================================================
auto uomap::load(const std::filesystem::path &uodir,tileinfo *info)->bool{
	auto status = loadTerrain(uodir, info) ;
	if (status ){
		status = loadArt(uodir, info);
		if (status) {
			if (!_uop){
				_terrain_diff_count=loadTerrainDiff(uodir, info);
			}
			_art_diff_count = loadArtDiff(uodir, info);
		}
	}
	return status ;
}
//=========================================================================
auto uomap::loadTerrainFile(const std::string &filepath,tileinfo *info, bool uop)->bool {
	if (uop) {
		return loadUOP(filepath,0x300,strutil::format(_uophash,_map_number,_uophash_trailer.c_str()),info);
	}
	else {
		return loadTerrainMul(filepath, info);
	}
}

//============================================================================
auto uomap::size() const ->std::pair<int,int>{
	return std::make_pair(_width, _height);
}

//============================================================================
auto uomap::terrainDiff() const ->int {
	return _terrain_diff_count;
}
//============================================================================
auto uomap::artDiff() const -> int {
	return _art_diff_count;
}
//============================================================================
auto uomap::uop() const ->bool {
	return _uop;
}

//============================================================================
auto uomap::terrain(int x, int y) -> tile_t&{
	auto [block,offx,offy] = indexForCoord(x, y);
	return _terrain[block].terrain(offx, offy);
}
//============================================================================
auto uomap::terrain(int x, int y) const ->const tile_t & {
	auto [block,offx,offy] = indexForCoord(x, y);
	return _terrain[block].terrain(offx, offy);

}
//============================================================================
auto uomap::art(int x, int y) ->std::vector<tile_t>& {
	auto [block,offx,offy] = indexForCoord(x, y);
	return _art[block].tiles(offx, offy);

}
//============================================================================
auto uomap::art(int x, int y) const ->const std::vector<tile_t>& {
	auto [block,offx,offy] = indexForCoord(x, y);
	return _art[block].tiles(offx, offy);

}


//============================================================================
//  Overridden virtual methods of uopfile
//============================================================================
//============================================================================
auto uomap::processEntry(std::size_t entry, std::size_t index, std::vector<std::uint8_t> &data,tileinfo * info)->bool{
	auto block = (index * 0xC4000)/196  ;
	if (block < _terrain.size()){
		auto count = static_cast<int>(data.size()/196) ;
		for (auto i=0 ; i < count ; i++){
			std::vector<std::uint8_t> blockdata(196,0) ;
			std::copy(data.cbegin()+(i*196) ,data.cbegin()+((i+1)*196),blockdata.begin()) ;
			if ((block+i) < _terrain.size()) {
				_terrain[block+i].load(blockdata,info);
			}
			else {
				break;
			}
		}
	}
	return true ;
}
//============================================================================
auto uomap::entriesToWrite()const ->int {
	return ((static_cast<int>(_terrain.size()) * 196 ) / 0xC4000) + 1 ;
	
}
//============================================================================
auto uomap::entryForWrite(int entry)->std::vector<unsigned char> {
	constexpr int number = 0xC4000/196 ;
	auto start_block = (entry*0xC4000)/196 ;
	if (start_block >= static_cast<int>(_terrain.size())){
		return std::vector<unsigned char>() ;
	}
	auto data = std::vector<unsigned char>(0xC4000,0);
	auto offset = 0 ;
	for (auto j=start_block ; j< start_block+number; ++j){
		if (j>= static_cast<int>(_terrain.size())){
			break ;
		}
		std::copy(reinterpret_cast<unsigned char*>(&j),reinterpret_cast<unsigned char*>(&j)+sizeof(j),data.begin()+offset);
		auto blockdata = _terrain[j].raw() ;
		std::copy(blockdata.begin(),blockdata.end(),data.begin()+offset+sizeof(j));
		offset += 196 ;
	}
	return data ;
}
//============================================================================
auto uomap::writeHash(int entry)->std::string  {
	auto hashfmt = strutil::format(_uophash,_map_number,_uophash_trailer.c_str());
	return strutil::format(hashfmt,entry);
}

//============================================================================
//  write out that data blocks to "mul" files
//============================================================================
//=============================================================================
auto uomap::writeTerrain(const std::string &filename,bool uop)  ->bool {
	if (uop){
		return writeUOP(filename);
	}
	auto output = std::ofstream(filename,std::ios::binary);
	if (!output.is_open()){
		return false ;
	}
	// now just write out the blocks, whith a header in front of each
	auto header = std::int32_t(0);
	for (const auto &block : _terrain){
		output.write(reinterpret_cast<char*>(&header),sizeof(header));
		auto blockdata = block.raw() ;
		output.write(reinterpret_cast<char*>(blockdata.data()),blockdata.size());
		header++;
	}
	return true ;
}
//=============================================================================
auto uomap::writeArt(const std::string &idxname, const std::string &mulname) const ->bool {
	auto idx = std::ofstream(idxname,std::ios::binary);
	auto mul = std::ofstream(mulname,std::ios::binary);
	if (!idx.is_open()||!mul.is_open()){
		return false ;
	}
	auto nodata = std::uint32_t(0xFFFFFFFF);
	auto offset = std::uint32_t(0) ;
	auto length = std::uint32_t(0);
	auto zero = std::uint32_t(0);
	for (const auto &block : _art){
		auto blockdata = block.raw() ;
		
		if (!blockdata.empty()) {
			idx.write(reinterpret_cast<char*>(&offset),sizeof(offset));
			length = static_cast<std::uint32_t>(blockdata.size());
			idx.write(reinterpret_cast<char*>(&length),sizeof(length));
			offset += length ;
			idx.write(reinterpret_cast<char*>(&zero),sizeof(zero));
			mul.write(reinterpret_cast<char*>(blockdata.data()),blockdata.size());
		}
		else {
			idx.write(reinterpret_cast<char*>(&nodata),sizeof(nodata));
			idx.write(reinterpret_cast<char*>(&zero),sizeof(zero));
			idx.write(reinterpret_cast<char*>(&zero),sizeof(zero));
		}
	}
	return true ;

}
//=============================================================================
auto uomap::artBlock(size_t index) const ->const artblock&{
	return _art[index];
}
//=============================================================================
auto uomap::artBlock(size_t index)  -> artblock&{
	return _art[index];
}
//=============================================================================
auto uomap::terrainBlock(size_t index) const ->const terrainblock&{
	return _terrain[index];
}
//=============================================================================
auto uomap::terrainBlock(size_t index)  -> terrainblock&{
	return _terrain[index];
}
