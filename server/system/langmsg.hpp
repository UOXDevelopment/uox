//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef langmsg_hpp
#define langmsg_hpp

#include <cstdint>
#include <string>
#include <map>
#include <filesystem>

#include "secparser.hpp"
#include "system_types.hpp"
//=========================================================
class langmsg : public secparser_t {
	std::map<language_t,std::map<std::string,section_t> > messages ;
	auto processSection(section_t &section) ->void final ;
	language_t serverlanguage ;
public:
	langmsg(language_t language = language_t::english)  ;
	~langmsg() = default ;
	
	auto serverLanguage(language_t language) ->void ;
	auto serverLanguage() const -> language_t ;
	
	auto sections(language_t language) const -> const std::map<std::string,section_t>& ;
	auto languages() const -> const std::map<language_t,std::map<std::string,section_t> >&;
	
	auto size() const -> size_t ;
	auto size(language_t language) const ->size_t ;
	
	auto reset() ->void ;
	auto entry(language_t language,const std::string &secidentifier, const std::string &key)const ->const std::string&;
};
#endif /* langmsg_hpp */
