//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef tileinfo_hpp
#define tileinfo_hpp

#include <cstdint>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
//===============================================================
// Why dont we use bitset for this?
// Because it doesn't lend itself to testing multiple specific
// flags at the same time.  We dont want to pollute the entire namepace
// with these names, so we wrapper it in a UO namespace (we could have done that
// for all of the uo stuff), something to consider?
//=======================================================================
namespace UO {
	//===============================================================
	//flag constants
	static constexpr std::uint64_t none 	= 0x0000000000000000;
	static constexpr std::uint64_t background = 0x0000000000000001;
	static constexpr std::uint64_t weapon 	= 0x0000000000000002;
	static constexpr std::uint64_t holdable 	= 0x0000000000000002;	// Alternative for weapon
	static constexpr std::uint64_t transparent= 0x0000000000000004;
	// The tile is rendered with partial alpha-transparency.
	static constexpr std::uint64_t translucent= 0x0000000000000008;
	// The tile is a wall.
	static constexpr std::uint64_t wall 	= 0x0000000000000010;
	// The tile can cause damage when moved over.
	static constexpr std::uint64_t damaging 	= 0x0000000000000020;
	// The tile may not be moved over or through.
	static constexpr std::uint64_t impassable = 0x0000000000000040;
	static constexpr std::uint64_t wet 		= 0x0000000000000080;
	static constexpr std::uint64_t unknownBit9= 0x0000000000000100;
	// The tile is a surface. It may be moved over, but not through.
	static constexpr std::uint64_t surface 	= 0x0000000000000200;
	// The tile is a stair, ramp, or ladder.
	static constexpr std::uint64_t bridge 	= 0x0000000000000400;
	static constexpr std::uint64_t climable 	= 0x0000000000000400;  // alternative for bridge
	// The tile is stackable
	static constexpr std::uint64_t generic 	= 0x0000000000000800;
	static constexpr std::uint64_t stackable 	= 0x0000000000000800;  // alternative for generic
	// The tile is a window. Like NoShoot, tiles with this flag block line of sight.
	static constexpr std::uint64_t window 	= 0x0000000000001000;
	// The tile blocks line of sight.
	static constexpr std::uint64_t noShoot 	= 0x0000000000002000;
	// For single-amount tiles, the string "a " should be prepended to the tile name.
	static constexpr std::uint64_t articleA 	= 0x0000000000004000;
	// For single-amount tiles, the string "a " should be prepended to the tile name.
	static constexpr std::uint64_t articleAn 	= 0x0000000000008000;
	// Probably article The prepended to the tile name.
	static constexpr std::uint64_t articleThe = 0x0000000000010000;
	static constexpr std::uint64_t description= 0x0000000000010000;  // alternative for articThe
	// The tile becomes translucent when walked behind. Boat masts also have this flag.
	static constexpr std::uint64_t foliage 	= 0x0000000000020000;
	// Only gray pixels will be hued
	static constexpr std::uint64_t partialHue = 0x0000000000040000;
	// NoHouse or Unknown. Needs further research.
	static constexpr std::uint64_t noHouse 	= 0x0000000000080000;
	// The tile is a map--in the cartography sense. Unknown usage.
	static constexpr std::uint64_t map 		= 0x0000000000100000;
	// The tile is a container.
	static constexpr std::uint64_t container 	= 0x0000000000200000;
	// The tile may be equipped.
	static constexpr std::uint64_t wearable 	= 0x0000000000400000;
	// The tile gives off light.
	static constexpr std::uint64_t lightSource= 0x0000000000800000;
	// The tile is animated.
	static constexpr std::uint64_t animated 	= 0x0000000001000000;
	// Gargoyles can fly over or NoDiagonal
	static constexpr std::uint64_t hoverOver 	= 0x0000000002000000;
	// NoDiagonal (Unknown3).
	static constexpr std::uint64_t noDiagnol 	= 0x0000000004000000;
	static constexpr std::uint64_t armor 	= 0x0000000008000000;
	static constexpr std::uint64_t roof 	= 0x0000000010000000;
	static constexpr std::uint64_t door 	= 0x0000000020000000;
	static constexpr std::uint64_t stairBack 	= 0x0000000040000000;
	static constexpr std::uint64_t stairRight = 0x0000000080000000;
	
	// HS tile flags
	// Blend Alphas, tile blending.
	static constexpr std::uint64_t alphaBlend = 0x0000000100000000;
	// Uses new art style? Something related to the nodraw tile?
	static constexpr std::uint64_t useNewArt 	= 0x0000000200000000;
	// Has art being used?
	static constexpr std::uint64_t artUsed 	= 0x0000000400000000;
	// Disallow shadow on this tile, lightsource? lava?
	static constexpr std::uint64_t noShadow 	= 0x0000001000000000;
	// Let pixels bleed in to other tiles? Is this Disabling Texture Clamp?
	static constexpr std::uint64_t pixelBleed	= 0x0000002000000000;
	// Play tile animation once.
	static constexpr std::uint64_t animatedOnce = 0x0000004000000000;
	
	// Movable multi? Cool ships and vehicles etc? Something related to the masts ???
	static constexpr std::uint64_t multiMove 	= 0x0000100000000000;
	
};


//=========================================================
using tileid_t = std::uint16_t ;
static constexpr tileid_t invalid_tileid = 0xFFFF ;

//==============================================================
// What type of tiles do we have?  Fundementally, we have the
// lower 0x4000 tiles (terrain), that are used in the map, and one set of
// attributes, and the the art tiles
//===============================================================
enum class tiletype_t {
	invalid = -1 , terrain = 0, art
};

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

#endif /* TileInfo_hpp */
