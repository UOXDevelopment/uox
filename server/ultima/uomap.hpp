//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef uomap_hpp
#define uomap_hpp

#include <cstdint>
#include <vector>
#include <array>
#include <string>
#include <filesystem>
#include <utility>
#include <tuple>

#include "terrainblock.hpp"
#include "artblock.hpp"
#include "uopfile.hpp"
/* ***************************************************************************
 This class is designed to work with uox, which is why we dont have some invidual methods
 to load the files seperately, or with strings.  Easily added, but not needed
 for the purposes.  Basically, one supplies the directory where there files are
 located, and it will load the terrain (trying uop, and then mul) and art work (mul).
 The diffs can be applied separatly, again by supplying the directory of where the files
 are locations.  If the map was loaded as a uop, no diff will be applied
****************************************************************************** */
//=========================================================
class uomap : public uopfile {
private:

	static constexpr std::array<int,12> _mapsizes{7168,4096,7168,4096,2304,1600,2560,2048,1448,1448,1280,4096};

	static const std::string _mapmul ;
	static const std::string _mapuop ;
	static const std::string _staidx ;
	static const std::string _stamul ;
	static const std::string _mapdifl;
	static const std::string _mapdif ;
	static const std::string _stadifl ;
	static const std::string _stadifi;
	static const std::string _stadif ;
	static const std::string _uophash;
	static const std::string _uophash_trailer;

	
	int _map_number ;
	int _width ;
	int _height ;
	int _terrain_diff_count ;
	int _art_diff_count ;
	bool _uop ;
	
	std::vector<terrainblock> _terrain;
	std::vector<artblock> _art ;
public:

private:
	auto processEntry(std::size_t entry, std::size_t index, std::vector<std::uint8_t> &data,tileinfo * info)->bool final;

	auto entriesToWrite()const ->int final ;
	auto entryForWrite(int entry)->std::vector<unsigned char> final ;
	auto writeHash(int entry)->std::string  final;

protected:
	auto loadTerrainMul(const std::filesystem::path &filepath,tileinfo *info)->bool ;
	auto loadTerrain(const std::filesystem::path &uodir,tileinfo *info)->bool ;
	auto loadArt(const std::filesystem::path &uodir,tileinfo *info)->bool;
	auto loadTerrainDiff(const std::filesystem::path &uodir,tileinfo *info)->int ;
	auto loadArtDiff(const std::filesystem::path &uodir,tileinfo *info)->int ;

	auto indexForCoord(int x, int y) const ->std::tuple<int,int,int>;
	
public:
	
	static auto defaultSizeForMap(int number) -> std::pair<int,int> ;
	static auto indexForCoord(int x, int y, int height) -> std::tuple<int, int, int> ;
	uomap();
	uomap(int mapnumber , int width, int height) ;
	auto set(int mapnumber, int width, int height) ->void;
	virtual ~uomap() = default ;
	auto load(const std::filesystem::path &uodir,tileinfo *info)->bool;
	auto loadTerrainFile(const std::string &filepath,tileinfo *info, bool uop)->bool;
	auto size() const ->std::pair<int,int>;
	auto terrainDiff() const ->int ;
	auto artDiff() const -> int ;
	auto uop() const ->bool ;
	
	auto terrain(int x, int y) -> tile_t&;
	auto terrain(int x, int y) const ->const tile_t & ;
	auto art(int x, int y) ->std::vector<tile_t>& ;
	auto art(int x, int y) const ->const std::vector<tile_t>& ;
	
	auto writeTerrain(const std::string &filename,bool uop=false)  ->bool ;
	auto writeArt(const std::string &idxname, const std::string &mulname) const ->bool ;
	
	auto artBlock(size_t index) const ->const artblock&;
	auto artBlock(size_t index)  -> artblock&;
	auto terrainBlock(size_t index) const ->const terrainblock&;
	auto terrainBlock(size_t index)  -> terrainblock&;
};
#endif /* uomap_hpp */
