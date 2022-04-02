//Copyright © 2022 Charles Kerr. All rights reserved.

#include "system_types.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>
#include <stdexcept>

using namespace std::string_literals;




//=========================================================
/* ******************************************************
 servmod_t
 *******************************************************/
//=========================================================
const std::unordered_map<servmod_t,std::string> servmod_names{
	{servmod_t::data,"data"s},{servmod_t::user,"user"s},{servmod_t::ultima,"ultima"s}
};
//=========================================================
auto nameForServMod(servmod_t modifier) -> const std::string& {
	return servmod_names.at(modifier);
}
//=========================================================
auto servmodForName(const std::string &name) ->servmod_t {
	auto iter = std::find_if(servmod_names.begin(),servmod_names.end(),[&name](const std::pair<servmod_t,std::string> &entry){
		return entry.second == name ;
	});
	if (iter != servmod_names.end()){
		return iter->first ;
	}
	throw std::out_of_range(name +" is not a valid servmod_t type"s);
}
//=========================================================
auto servmodNames() ->const std::unordered_map<servmod_t,std::string>& {
	return servmod_names;
}

//=========================================================
/* ******************************************************
 serverloc_t
 *******************************************************/
//=========================================================
const std::unordered_map<serverloc_t,std::string> serverloc_names{
	{serverloc_t::configuration,"configuration"s},{serverloc_t::definition,"definition"s},
	{serverloc_t::language,"language"s},{serverloc_t::script,"script"s}
};
//=========================================================
auto nameForServerLoc(serverloc_t type) -> const std::string& {
	return serverloc_names.at(type);
}
//=========================================================
auto serverlocForName(const std::string &name) ->serverloc_t {
	auto iter = std::find_if(serverloc_names.begin(),serverloc_names.end(),[&name](const std::pair<serverloc_t,std::string> &entry){
		return entry.second == name ;
	});
	if (iter != serverloc_names.end()){
		return iter->first ;
	}
	throw std::out_of_range(name +" is not a valid serverloc_t type"s);
}
//=========================================================
auto serverlocNames() ->const std::unordered_map<serverloc_t,std::string>& {
	return serverloc_names;
}

//=========================================================
/* ******************************************************
 userloc_t
 *******************************************************/
//=========================================================
const std::unordered_map<userloc_t,std::string> userloc_names{
	{userloc_t::configuration,"configuration"s},	{userloc_t::definition,"definition"s},
	{userloc_t::language,"language"s},			{userloc_t::script,"script"s},
	{userloc_t::log,"log"s},				{userloc_t::msgboard,"msgboard"s},
	{userloc_t::world,"world"s},				{userloc_t::book,"book"s},
	{userloc_t::access,"access"s},			{userloc_t::scriptdata,"scriptdata"s}
};
//=========================================================
auto nameForUserLoc(userloc_t type) -> const std::string& {
	return userloc_names.at(type) ;
}
//=========================================================
auto userlocForName(const std::string &name) ->userloc_t {
	auto iter = std::find_if(userloc_names.begin(),userloc_names.end(),[&name](const std::pair<userloc_t,std::string> &entry){
		return entry.second == name ;
	});
	if (iter != userloc_names.end()){
		return iter->first ;
	}
	throw std::out_of_range(name +" is not a valid userloc_t type"s);
}
//=========================================================
auto userlocNames() ->const std::unordered_map<userloc_t,std::string>& {
	return userloc_names;
}

/* *****************************************************************
 unicode_t
 ******************************************************************* */
//=========================================================
const std::unordered_map<unicode_t,std::string> unicode_names {
	{unicode_t::ZERO, "ZERO"s}, {unicode_t::ARA, "ARA"s}, {unicode_t::ARI, "ARI"s},
	{unicode_t::ARE, "ARE"s}, {unicode_t::ARL, "ARL"s}, {unicode_t::ARG, "ARG"s},
	{unicode_t::ARM, "ARM"s}, {unicode_t::ART, "ART"s}, {unicode_t::ARO, "ARO"s},
	{unicode_t::ARY, "ARY"s}, {unicode_t::ARS, "ARS"s}, {unicode_t::ARJ, "ARJ"s},
	{unicode_t::ARB, "ARB"s}, {unicode_t::ARK, "ARK"s}, {unicode_t::ARU, "ARU"s},
	{unicode_t::ARH, "ARH"s}, {unicode_t::ARQ, "ARQ"s}, {unicode_t::BGR, "BGR"s},
	{unicode_t::CAT, "CAT"s}, {unicode_t::CHT, "CHT"s}, {unicode_t::CHS, "CHS"s},
	{unicode_t::ZHH, "ZHH"s}, {unicode_t::ZHI, "ZHI"s}, {unicode_t::ZHM, "ZHM"s},
	{unicode_t::CSY, "CSY"s}, {unicode_t::DAN, "DAN"s}, {unicode_t::DEU, "DEU"s},
	{unicode_t::DES, "DES"s}, {unicode_t::DEA, "DEA"s}, {unicode_t::DEL, "DEL"s},
	{unicode_t::DEC, "DEC"s}, {unicode_t::ELL, "ELL"s}, {unicode_t::ENU, "ENU"s},
	{unicode_t::ENG, "ENG"s}, {unicode_t::ENA, "ENA"s}, {unicode_t::ENC, "ENC"s},
	{unicode_t::ENZ, "ENZ"s}, {unicode_t::ENI, "ENI"s}, {unicode_t::ENS, "ENS"s},
	{unicode_t::ENJ, "ENJ"s}, {unicode_t::ENB, "ENB"s}, {unicode_t::ENL, "ENL"s},
	{unicode_t::ENT, "ENT"s}, {unicode_t::ENW, "ENW"s}, {unicode_t::ENP, "ENP"s},
	{unicode_t::ESP, "ESP"s}, {unicode_t::ESM, "ESM"s}, {unicode_t::ESN, "ESN"s},
	{unicode_t::ESG, "ESG"s}, {unicode_t::ESC, "ESC"s}, {unicode_t::ESA, "ESA"s},
	{unicode_t::ESD, "ESD"s}, {unicode_t::ESV, "ESV"s}, {unicode_t::ESO, "ESO"s},
	{unicode_t::ESR, "ESR"s}, {unicode_t::ESS, "ESS"s}, {unicode_t::ESF, "ESF"s},
	{unicode_t::ESL, "ESL"s}, {unicode_t::ESY, "ESY"s}, {unicode_t::ESZ, "ESZ"s},
	{unicode_t::ESB, "ESB"s}, {unicode_t::ESE, "ESE"s}, {unicode_t::ESH, "ESH"s},
	{unicode_t::ESI, "ESI"s}, {unicode_t::ESU, "ESU"s}, {unicode_t::FIN, "FIN"s},
	{unicode_t::FRA, "FRA"s}, {unicode_t::FRB, "FRB"s}, {unicode_t::FRC, "FRC"s},
	{unicode_t::FRS, "FRS"s}, {unicode_t::FRL, "FRL"s}, {unicode_t::FRM, "FRM"s},
	{unicode_t::HEB, "HEB"s}, {unicode_t::HUN, "HUN"s}, {unicode_t::ISL, "ISL"s},
	{unicode_t::ITA, "ITA"s}, {unicode_t::ITS, "ITS"s}, {unicode_t::JPN, "JPN"s},
	{unicode_t::KOR, "KOR"s}, {unicode_t::NLD, "NLD"s}, {unicode_t::NLB, "NLB"s},
	{unicode_t::NOR, "NOR"s}, {unicode_t::NON, "NON"s}, {unicode_t::PLK, "PLK"s},
	{unicode_t::PTB, "PTB"s}, {unicode_t::PTG, "PTG"s}, {unicode_t::ROM, "ROM"s},
	{unicode_t::RUS, "RUS"s}, {unicode_t::HRV, "HRV"s}, {unicode_t::SRL, "SRL"s},
	{unicode_t::SRB, "SRB"s}, {unicode_t::SKY, "SKY"s}, {unicode_t::SQI, "SQI"s},
	{unicode_t::SVE, "SVE"s}, {unicode_t::SVF, "SVF"s}, {unicode_t::THA, "THA"s},
	{unicode_t::TRK, "TRK"s}, {unicode_t::URP, "URP"s}, {unicode_t::IND, "IND"s},
	{unicode_t::UKR, "UKR"s}, {unicode_t::BEL, "BEL"s}, {unicode_t::SLV, "SLV"s},
	{unicode_t::ETI, "ETI"s}, {unicode_t::LVI, "LVI"s}, {unicode_t::LTH, "LTH"s},
	{unicode_t::LTC, "LTC"s}, {unicode_t::FARR, "FAR"s}, {unicode_t::VIT, "VIT"s},
	{unicode_t::HYE, "HYE"s}, {unicode_t::AZE, "AZE"s}, {unicode_t::EUQ, "EUQ"s},
	{unicode_t::MKI, "MKI"s}, {unicode_t::AFK, "AFK"s}, {unicode_t::KAT, "KAT"s},
	{unicode_t::FOS, "FOS"s}, {unicode_t::HIN, "HIN"s}, {unicode_t::MSL, "MSL"s},
	{unicode_t::MSB, "MSB"s}, {unicode_t::KAZ, "KAZ"s}, {unicode_t::SWK, "SWK"s},
	{unicode_t::UZB, "UZB"s}, {unicode_t::TAT, "TAT"s}, {unicode_t::BEN, "BEN"s},
	{unicode_t::PAN, "PAN"s}, {unicode_t::GUJ, "GUJ"s}, {unicode_t::ORI, "ORI"s},
	{unicode_t::TAM, "TAM"s}, {unicode_t::TEL, "TEL"s}, {unicode_t::KAN, "KAN"s},
	{unicode_t::MAL, "MAL"s}, {unicode_t::ASM, "ASM"s}, {unicode_t::MAR, "MAR"s},
	{unicode_t::SAN, "SAN"s}, {unicode_t::KOK, "KOK"s}
};
//=========================================================
auto nameForUnicode(unicode_t type) -> const std::string& {
	return unicode_names.at(type) ;
}
//=========================================================
auto unicodeForName(const std::string &name) ->unicode_t {
	auto iter = std::find_if(unicode_names.begin(),unicode_names.end(),[&name](const std::pair<unicode_t,std::string> &entry){
		return entry.second == name ;
	});
	if (iter != unicode_names.end()){
		return iter->first ;
	}
	throw std::out_of_range(name +" is not a valid unicode_t type"s);
}
//=========================================================
auto unicodeNames() ->const std::unordered_map<unicode_t,std::string>& {
	return unicode_names;
}
/* *****************************************************************
 language_t
 ******************************************************************* */
//=========================================================
const std::unordered_map<language_t,std::string> language_names  {
	{language_t::none,"none"s},		{language_t::english,"english"s},
	{language_t::german,"german"s},	{language_t::spanish,"spanish"s},
	{language_t::french,"french"s},	{language_t::portuguese,"portuguese"s},
	{language_t::italian,"italian"s},	{language_t::czech,"czech"s},
	{language_t::polish,"polish"s},	{language_t::russian,"russian"s},
	{language_t::japanese,"japanese"s}
} ;
//=========================================================
auto nameForLanguage(language_t value) ->const std::string&{
	return language_names.at(value) ;
}
//=========================================================
auto languageForName(const std::string &name) ->language_t {
	auto iter = std::find_if(language_names.begin(),language_names.end(),[&name](const std::pair<language_t,std::string> &entry){
		return entry.second == name ;
	});
	if (iter != language_names.end()){
		return iter->first ;
	}
	throw std::out_of_range(name +" is not a valid language_t type"s);
}
//=========================================================
auto languageNames() ->const std::unordered_map<language_t,std::string>& {
	return language_names ;
}
//===========================================================
const std::unordered_map<unicode_t,language_t> unicodelang_map {
	{unicode_t::ZERO, language_t::none},	{unicode_t::ARA, language_t::none},
	{unicode_t::ARI, language_t::none},		{unicode_t::ARE, language_t::none},
	{unicode_t::ARL, language_t::none}, 	{unicode_t::ARG, language_t::none},
	{unicode_t::ARM, language_t::none},		{unicode_t::ART, language_t::none},
	{unicode_t::ARO, language_t::none},		{unicode_t::ARY, language_t::none},
	{unicode_t::ARS, language_t::none}, 	{unicode_t::ARJ, language_t::none},
	{unicode_t::ARB, language_t::none},		{unicode_t::ARK, language_t::none},
	{unicode_t::ARU, language_t::none},		{unicode_t::ARH, language_t::none},
	{unicode_t::ARQ, language_t::none}, 	{unicode_t::BGR, language_t::none},
	{unicode_t::CAT, language_t::none}, 	{unicode_t::CHT, language_t::none},
	{unicode_t::CHS, language_t::none},		{unicode_t::ZHH, language_t::none},
	{unicode_t::ZHI, language_t::none}, 	{unicode_t::ZHM, language_t::none},
	{unicode_t::CSY, language_t::czech}, 	{unicode_t::DAN, language_t::none},
	{unicode_t::DEU, language_t::german},	{unicode_t::DES, language_t::german},
	{unicode_t::DEA, language_t::german}, 	{unicode_t::DEL, language_t::german},
	{unicode_t::DEC, language_t::german},	{unicode_t::ELL, language_t::none},
	{unicode_t::ENU, language_t::english},	{unicode_t::ENG, language_t::english},
	{unicode_t::ENA, language_t::english},	{unicode_t::ENC, language_t::english},
	{unicode_t::ENZ, language_t::english}, 	{unicode_t::ENI, language_t::english},
	{unicode_t::ENS, language_t::english},	{unicode_t::ENJ, language_t::english},
	{unicode_t::ENB, language_t::english}, 	{unicode_t::ENL, language_t::english},
	{unicode_t::ENT, language_t::english}, 	{unicode_t::ENW, language_t::english},
	{unicode_t::ENP, language_t::english},	{unicode_t::ESP, language_t::spanish},
	{unicode_t::ESM, language_t::spanish}, 	{unicode_t::ESN, language_t::spanish},
	{unicode_t::ESG, language_t::spanish}, 	{unicode_t::ESC, language_t::spanish},
	{unicode_t::ESA, language_t::spanish},	{unicode_t::ESD, language_t::spanish},
	{unicode_t::ESV, language_t::spanish}, 	{unicode_t::ESO, language_t::spanish},
	{unicode_t::ESR, language_t::spanish}, 	{unicode_t::ESS, language_t::spanish},
	{unicode_t::ESF, language_t::spanish},	{unicode_t::ESL, language_t::spanish},
	{unicode_t::ESY, language_t::spanish}, 	{unicode_t::ESZ, language_t::spanish},
	{unicode_t::ESB, language_t::spanish}, 	{unicode_t::ESE, language_t::spanish},
	{unicode_t::ESH, language_t::spanish},	{unicode_t::ESI, language_t::spanish},
	{unicode_t::ESU, language_t::spanish}, 	{unicode_t::FIN, language_t::none},
	{unicode_t::FRA, language_t::french}, 	{unicode_t::FRB, language_t::french},
	{unicode_t::FRC, language_t::french},	{unicode_t::FRS, language_t::french},
	{unicode_t::FRL, language_t::french}, 	{unicode_t::FRM, language_t::french},
	{unicode_t::HEB, language_t::none}, 	{unicode_t::HUN, language_t::none},
	{unicode_t::ISL, language_t::none},		{unicode_t::ITA, language_t::italian},
	{unicode_t::ITS, language_t::italian}, 	{unicode_t::JPN, language_t::japanese},
	{unicode_t::KOR, language_t::none}, 	{unicode_t::NLD, language_t::none},
	{unicode_t::NLB, language_t::none},		{unicode_t::NOR, language_t::none},
	{unicode_t::NON, language_t::none}, 	{unicode_t::PLK, language_t::polish},
	{unicode_t::PTB, language_t::portuguese}, {unicode_t::PTG, language_t::portuguese},
	{unicode_t::ROM, language_t::none},		{unicode_t::RUS, language_t::russian},
	{unicode_t::HRV, language_t::none}, 	{unicode_t::SRL, language_t::none},
	{unicode_t::SRB, language_t::none}, 	{unicode_t::SKY, language_t::none},
	{unicode_t::SQI, language_t::none},		{unicode_t::SVE, language_t::none},
	{unicode_t::SVF, language_t::none}, 	{unicode_t::THA, language_t::none},
	{unicode_t::TRK, language_t::none}, 	{unicode_t::URP, language_t::none},
	{unicode_t::IND, language_t::none},		{unicode_t::UKR, language_t::none},
	{unicode_t::BEL, language_t::none}, 	{unicode_t::SLV, language_t::none},
	{unicode_t::ETI, language_t::none}, 	{unicode_t::LVI, language_t::none},
	{unicode_t::LTH, language_t::none},		{unicode_t::LTC, language_t::none},
	{unicode_t::FARR, language_t::none}, 	{unicode_t::VIT, language_t::none},
	{unicode_t::HYE, language_t::none}, 	{unicode_t::AZE, language_t::none},
	{unicode_t::EUQ, language_t::none},		{unicode_t::MKI, language_t::none},
	{unicode_t::AFK, language_t::none}, 	{unicode_t::KAT, language_t::none},
	{unicode_t::FOS, language_t::none}, 	{unicode_t::HIN, language_t::none},
	{unicode_t::MSL, language_t::none},		{unicode_t::MSB, language_t::none},
	{unicode_t::KAZ, language_t::none}, 	{unicode_t::SWK, language_t::none},
	{unicode_t::UZB, language_t::none}, 	{unicode_t::TAT, language_t::none},
	{unicode_t::BEN, language_t::none},		{unicode_t::PAN, language_t::none},
	{unicode_t::GUJ, language_t::none}, 	{unicode_t::ORI, language_t::none},
	{unicode_t::TAM, language_t::none}, 	{unicode_t::TEL, language_t::none},
	{unicode_t::KAN, language_t::none},		{unicode_t::MAL, language_t::none},
	{unicode_t::ASM, language_t::none}, 	{unicode_t::MAR, language_t::none},
	{unicode_t::SAN, language_t::none}, 	{unicode_t::KOK, language_t::none}
};
//=========================================================
auto languageForUnicode(unicode_t value) ->language_t{
	return unicodelang_map.at(value) ;
}
