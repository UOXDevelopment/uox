//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef artblock_hpp
#define artblock_hpp
#include "tileinfo.hpp"
#include <cstdint>
#include <array>
#include <vector>
//=========================================================
class artblock {
private:
	std::array<std::array<std::vector<tile_t>,8>,8> _tiles ;
	
public:
	artblock(const std::vector<unsigned char> &data = std::vector<unsigned char>(), tileinfo *info=nullptr);
	auto load(const std::vector<unsigned char> &data, tileinfo *info = nullptr)->void;
	auto tiles(int x, int y) -> std::vector<tile_t> & ;
	auto tiles(int x, int y) const -> const std::vector<tile_t>& ;
	auto raw() const ->std::vector<unsigned char> ;
};
#endif /* artblock_hpp */
