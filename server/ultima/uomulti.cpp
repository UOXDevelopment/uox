//Copyright © 2022 Charles Kerr. All rights reserved.

#include "uomulti.hpp"

#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std::string_literals;
//=========================================================
// mcomponent_t
//=========================================================
//=========================================================
mcomponent_t::mcomponent_t() :_flags(0),_xoffset(0),_yoffset(0){
	
}
//=========================================================
// mstructure_t
//=========================================================
//=========================================================
mstructure_t::mstructure_t():maxXOffset(0),minXOffset(0),maxYOffset(0),minYOffset(0),maxZOffset(0),minZOffset(0){
	
}
//=========================================================
// uomulti
//=========================================================
const std::string uomulti::_multiidx = "multi.idx"s ;
const std::string uomulti::_multimul = "multi.mul"s;
const std::string uomulti::_multiuop ="MultiCollection.uop";
const std::string uomulti::_uophash ="build/multicollection/%.6u.bin"s;

//=========================================================
auto uomulti::processHash(std::uint64_t hash,std::size_t entry , std::vector<std::uint8_t> &data) ->bool{
	if (hash == 0x126D1E99DDEDEE0ALL){
		return false ;  // This is the hash for the housing.bin file
	}
	return true ;
}

//=========================================================
auto uomulti::processEntry(std::size_t entry, std::size_t index, std::vector<std::uint8_t> &data,tileinfo *info) ->bool {
	if (data.size()>8){
		auto offset = std::uint32_t(4) ;
		// We skip the first 32 bit word (why offset is 4).
		// The next 32 bit word is the number of entries in this data ;
		
		auto count = std::int32_t(0) ;
		std::copy(data.data()+offset,data.data()+offset+4,reinterpret_cast<std::uint8_t*>(&count));
		offset += 4; ;
		// we increment offfset now that we have read the count
		// at this point,we are now looking at the data for each entry ;
		// before we start looping, make some dummy read space we can get data
		// out of the vector
		auto flag = std::int16_t(0) ;
		auto clilocs = std::uint32_t(0) ;
		
		// Now make a vector to store each entry
		auto components = std::vector<mcomponent_t>(count);
		for (auto comp = 0 ; comp < count ; comp++){
			// Make a component entry
			auto current = mcomponent_t() ;
			// Get the tileid
			std::copy(data.begin()+offset, data.begin()+offset+2,reinterpret_cast<unsigned char*>(&current._tile._tileid));
			if (info != nullptr){
				current._tile._info = &info->art(current._tile._tileid);
			}
			offset += 2 ;
			// Now get the xoffset
			std::copy(data.begin()+offset, data.begin()+offset+2,reinterpret_cast<unsigned char*>(&flag));
			current._xoffset = static_cast<int>(flag) ;
			offset +=2 ;
			// Now get the yoffset
			std::copy(data.begin()+offset, data.begin()+offset+2,reinterpret_cast<unsigned char*>(&flag));
			current._yoffset = static_cast<int>(flag) ;
			offset +=2 ;
			// Now get the z
			std::copy(data.begin()+offset, data.begin()+offset+2,reinterpret_cast<unsigned char*>(&flag));
			current._tile._z = static_cast<int>(flag) ;
			offset +=2 ;
			// now we need to get the flags, which are different then in the mul file in terms of lenght
			std::copy(data.begin()+offset, data.begin()+offset+2,reinterpret_cast<unsigned char*>(&flag));
			offset +=2 ;
			switch (flag){
				default:
				case 0:
					current._flags=1 ;
					break;
				case 1:
					break;
				case 257:
					current._flags = 0x800 ;
					break;
			}
			// we now have some clilocs to read past, have to find out how many
			std::copy(data.begin()+offset, data.begin()+offset+4,reinterpret_cast<unsigned char*>(&clilocs));
			offset += 4 ;
			// Now skip past them;
			offset += (clilocs*4) ;
			// now put it in the compoents
			components[comp] = std::move(current) ;
		}
		// Now we need to find the min/max of the structure
		mstructure_t building ;
		// Now find all the max/min
		building.maxXOffset = components[0]._xoffset ;
		building.maxYOffset = components[0]._yoffset ;
		building.maxZOffset = components[0]._tile._z ;
		building.minXOffset = components[0]._xoffset ;
		building.minYOffset = components[0]._yoffset ;
		building.minZOffset = components[0]._tile._z ;
		for (const auto &entry: components){
			building.maxXOffset = std::max(entry._xoffset,building.maxXOffset) ;
			building.maxYOffset = std::max(entry._yoffset,building.maxYOffset);
			building.maxZOffset = std::max(entry._tile._z,building.maxZOffset) ;
			building.minXOffset = std::min(entry._xoffset,building.minXOffset) ;
			building.minYOffset = std::min(entry._yoffset,building.minYOffset) ;
			building.minZOffset = std::min(entry._tile._z,building.minZOffset) ;
			
		}
		building._components = std::move(components);
		_multis[static_cast<int>(index)] = std::move(building) ;
	}
	return true ;
}
//=========================================================
auto uomulti::loadEntry(int entrynum, const std::vector<unsigned char> &data, bool hs,tileinfo *info)->bool {
	auto size = 16 ;
	if (!hs) {
		size = 12 ;
	}
	auto entrycount = static_cast<int>(data.size()/size) ;
	std::vector<mcomponent_t> components ;
	components.reserve(entrycount) ;
	auto offset = std::int16_t(0) ;
	auto flag32 = std::uint32_t(0) ;
	for (auto entry = 0 ; entry < entrycount ; entry++){
		mcomponent_t comp ;
		std::copy(data.begin()+(entry*size),data.begin()+(entry*size)+2,reinterpret_cast<unsigned char*>(&comp._tile._tileid));
		if (info !=nullptr){
			comp._tile._info = &info->art(comp._tile._tileid);
		}
		std::copy(data.begin()+(entry*size)+2,data.begin()+(entry*size)+4,reinterpret_cast<unsigned char*>(&offset));
		comp._xoffset = static_cast<int>(offset) ;
		std::copy(data.begin()+(entry*size)+4,data.begin()+(entry*size)+6,reinterpret_cast<unsigned char*>(&offset));
		comp._yoffset = static_cast<int>(offset) ;
		std::copy(data.begin()+(entry*size)+6,data.begin()+(entry*size)+8,reinterpret_cast<unsigned char*>(&offset));
		comp._tile._z = static_cast<int>(offset) ;
		if (!hs){
			std::copy(data.begin()+(entry*size)+8,data.begin()+(entry*size)+12,reinterpret_cast<unsigned char*>(&flag32));
			comp._flags = static_cast<std::uint64_t>(flag32) ;
		}
		else {
			std::copy(data.begin()+(entry*size)+8,data.begin()+(entry*size)+16,reinterpret_cast<unsigned char*>(&comp._flags));
		}
		
		components.push_back(std::move(comp));
	}
	mstructure_t building ;
	// Now find all the max/min
	building.maxXOffset = components[0]._xoffset ;
	building.maxYOffset = components[0]._yoffset ;
	building.maxZOffset = components[0]._tile._z ;
	building.minXOffset = components[0]._xoffset ;
	building.minYOffset = components[0]._yoffset ;
	building.minZOffset = components[0]._tile._z ;
	for (const auto &entry: components){
		building.maxXOffset = std::max(entry._xoffset,building.maxXOffset) ;
		building.maxYOffset = std::max(entry._yoffset,building.maxYOffset);
		building.maxZOffset = std::max(entry._tile._z,building.maxZOffset) ;
		building.minXOffset = std::min(entry._xoffset,building.minXOffset) ;
		building.minYOffset = std::min(entry._yoffset,building.minYOffset) ;
		building.minZOffset = std::min(entry._tile._z,building.minZOffset) ;

	}
	building._components = std::move(components);
	_multis[entrynum]=std::move(building);
	return true ;
}

//=========================================================
auto uomulti::loadMul(const std::filesystem::path &uodir, tileinfo *info)->bool {
	auto path = uodir ;
	auto idxpath = path / std::filesystem::path(_multiidx);
	auto mulpath = path / std::filesystem::path(_multimul);
	if (!std::filesystem::exists(mulpath)){
		return false ;
	}
	auto size = std::filesystem::file_size(mulpath);
	auto ishs = false ;
	if (size >= _hssize){
		ishs = true ;
	}
	auto idx = std::ifstream(idxpath.string(),std::ios::binary);
	auto mul = std::ifstream(mulpath.string(),std::ios::binary);
	if (!idx.is_open() || !mul.is_open()) {
		return false ;
	}
	// Ok, now we loop and load
	auto offset = std::uint32_t(0) ;
	auto length = std::uint32_t(0) ;
	auto entry = 0 ;
	while (idx.good() && !idx.eof() && mul.good()){
		idx.read(reinterpret_cast<char*>(&offset),sizeof(offset));
		idx.read(reinterpret_cast<char*>(&length),sizeof(length));
		idx.seekg(sizeof(length),std::ios::cur);
		if (idx.gcount() == sizeof(length)){
			if ((offset < 0xFFFFFFFE) && (length>0) && (length < 0xFFFFFFFE)){
				mul.seekg(offset,std::ios::beg) ;
				auto data = std::vector<unsigned char>(length,0);
				mul.read(reinterpret_cast<char*>(data.data()),data.size());
				if (mul.gcount() == data.size()){
					loadEntry(entry, data, ishs, info);
				}
			}
			entry++;
		}
	}
	return true ;
}

//=========================================================
uomulti::uomulti(const std::filesystem::path &uodir,tileinfo *info ){
	if (!uodir.empty()){
		load(uodir,info);
	}
}

//=========================================================
auto uomulti::size() const ->std::size_t {
	return _multis.size();
}
//=========================================================
auto uomulti::multi(int multiid) -> mstructure_t & {
	return _multis.at(multiid);
}
//=========================================================
auto uomulti::multi(int multiid) const -> const mstructure_t & {
	return _multis.at(multiid);

}
//=========================================================
auto uomulti::load(const std::filesystem::path &uodir,tileinfo *info) ->bool{
	// first see if they have uop available
	auto path = uodir ;
	auto uoppath = path / std::filesystem::path(_multiuop);
	if (std::filesystem::exists(uoppath)){
		return loadUOP(uoppath.string(),  0x10000, _uophash,info);
	}
	return loadMul(uodir, info);
}
