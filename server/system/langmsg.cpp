//Copyright © 2022 Charles Kerr. All rights reserved.

#include "langmsg.hpp"
#include "section.hpp"

#include <iostream>

using namespace std::string_literals ;
//=========================================================
langmsg::langmsg(language_t language) :secparser_t(){
	serverlanguage = language ;
}
//=========================================================
auto langmsg::processSection(section_t &section) ->void{
	if (section.header().type() == "dictionary"s){
		auto lang = language_t::none ;
		try {
			auto identifier = section.header().identifier() ;
			auto language = section.header().parent();
			if (!language.empty()){
				lang = languageForName(language) ;
			}
			messages[lang][identifier] = section ;
		}
		catch(...) {
			std::cerr <<"Invalid language for section " << section.header().identifier() <<std::endl;
		}

	}
}
//=========================================================
auto langmsg::serverLanguage(language_t language) ->void {
	serverlanguage = language ;
}
//=========================================================
auto langmsg::serverLanguage() const -> language_t {
	return serverlanguage;
}

//=========================================================
auto langmsg::sections(language_t language) const -> const std::map<std::string,section_t>& {
	return messages.at(language) ;
}
//=========================================================
auto langmsg::languages() const -> const std::map<language_t,std::map<std::string,section_t> >&{
	return messages;
}

//=========================================================
auto langmsg::size() const -> size_t {
	return messages.size();
}
//=========================================================
auto langmsg::size(language_t language) const ->size_t {
	return messages.at(language).size();
}

//=========================================================
auto langmsg::reset() ->void {
	messages.clear();
}
//=========================================================
auto langmsg::entry(language_t language,const std::string &secidentifier, const std::string &key)const ->const std::string&{
	if (!key.empty() && (key != "*"s)){
		// We want the specific key
		return messages.at(language).at(secidentifier).first(key)->value();
	}
	else {
		return messages.at(language).at(secidentifier).any()->value();

	}
}
