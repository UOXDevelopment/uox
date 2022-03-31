//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef terrainblock_hpp
#define terrainblock_hpp

#include <cstdint>
#include <array>
#include <vector>

#include "tileinfo.hpp"

//=========================================================
class terrainblock {
private:
	std::array<std::array<tile_t,8>,8> _tiles ;
	
public:
	terrainblock(const std::vector<unsigned char> &data = std::vector<unsigned char>(),tileinfo *info=nullptr) ;
	auto terrain(int x, int y) ->tile_t & ;
	auto terrain(int x, int y) const -> const tile_t& ;
	auto load(const std::vector<unsigned char>& data , tileinfo *info)->void ;
	auto updateInfo(tileinfo *info);
	auto raw() const ->std::vector<unsigned char> ;
};
#endif /* terrainblock_hpp */
