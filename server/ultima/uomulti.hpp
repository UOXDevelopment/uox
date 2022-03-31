//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef UOMulti_hpp
#define UOMulti_hpp

#include <cstdint>
#include <map>
#include <filesystem>

#include "tileinfo.hpp"
#include "uopfile.hpp"

//=========================================================
// Multi entrys have some additional attributes over a tile
//=========================================================
struct mcomponent_t {
	tile_t _tile ;
	int _xoffset ;
	int _yoffset ;
	std::uint64_t _flags ;
	mcomponent_t() ;
};
//=========================================================
// The structure that holds the entries
//=========================================================

struct mstructure_t {
	int maxXOffset ;
	int minXOffset ;
	int maxYOffset ;
	int minYOffset ;
	int maxZOffset ;
	int minZOffset ;
	std::vector<mcomponent_t> _components ;
	mstructure_t();
};

//=========================================================
// uomulti
//=========================================================
//=========================================================
class uomulti : public uopfile {
private:
	static const std::string _multiidx ;
	static const std::string _multimul ;
	static const std::string _multiuop ;
	static const std::string _uophash ;

	static constexpr auto _hssize = 908592 ;

	std::map<int, mstructure_t> _multis ;
	
	auto processHash(std::uint64_t hash,std::size_t entry , std::vector<std::uint8_t> &data) ->bool;
	auto processEntry(std::size_t entry, std::size_t index, std::vector<std::uint8_t> &data,tileinfo *info) ->bool final;
	auto loadEntry(int entrynum, const std::vector<unsigned char> &data, bool hs,tileinfo *info)->bool ;
	auto loadMul(const std::filesystem::path &uodir, tileinfo *info)->bool ;
public:
	uomulti(const std::filesystem::path &uodir=std::filesystem::path(),tileinfo *info = nullptr);
	auto load(const std::filesystem::path &uodir,tileinfo *info) ->bool;
	auto size() const ->std::size_t ;
	auto multi(int multiid) -> mstructure_t & ;
	auto multi(int multiid) const -> const mstructure_t & ;
	
};
#endif /* UOMulti_hpp */
