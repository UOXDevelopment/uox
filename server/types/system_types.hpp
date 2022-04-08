//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef system_types_hpp
#define system_types_hpp

#include <cstdint>
#include <string>
#include <unordered_map>
#include <limits>


//=========================================================
/* ********************************************************
 general
 ****************************************************** */
using actnum_t = int ;
constexpr auto invalid_account = std::numeric_limits<int>::max() ;
constexpr auto max_characters = 7 ;
/* ********************************************************
serverstatus_t
****************************************************** */
enum class serverstatus_t {shutdown, idle, run};
/* ********************************************************
 priv_t
 ****************************************************** */
enum class priv_t {player,seer,admin};
//=========================================================
auto nameForPriv(priv_t priv) -> const std::string& ;
//=========================================================
//=========================================================
auto privForName(const std::string &name) ->priv_t ;
auto privNames() ->const std::unordered_map<priv_t,std::string>& ;

//=========================================================
/* ******************************************************
 servermod_t
 *******************************************************/
//=========================================================
enum class servmod_t {
	data,user,ultima
};
//=========================================================
auto nameForServMod(servmod_t modifier) -> const std::string& ;
//=========================================================
//=========================================================
auto servmodForName(const std::string &name) ->servmod_t ;
auto servmodNames() ->const std::unordered_map<servmod_t,std::string>& ;

//=========================================================
/* ******************************************************
 serverloc_t
 *******************************************************/
//=========================================================
enum class serverloc_t {
	configuration,definition,language,script
};
//=========================================================
auto nameForServerLoc(serverloc_t type) -> const std::string& ;
//=========================================================
auto serverlocForName(const std::string &name) ->serverloc_t ;
//=========================================================
auto serverlocNames() ->const std::unordered_map<serverloc_t,std::string>& ;

//=========================================================
/* ******************************************************
 userloc_t
 *******************************************************/
//=========================================================
enum class userloc_t {
	configuration,definition,language,script,log,msgboard,world,book,access,scriptdata
};
//=========================================================
auto nameForUserLoc(userloc_t type) -> const std::string& ;
//=========================================================
auto userlocForName(const std::string &name) ->userloc_t ;
//=========================================================
auto userlocNames() ->const std::unordered_map<userloc_t,std::string>& ;

/* *********************************************************************
 Lanaguage -
 Lanaguage is two part.  There are unicode "types", and those map to a language
 
 ********************************************************************* */
/* *****************************************************************
 unicode_t
 ******************************************************************* */
enum class unicode_t {
	// default,Arabic Saudi Arabia,Arabic Iraq,Arabic Egypt, Arabic Libya, Arabic Algeri
	ZERO = 0, ARA, ARI, ARE, ARL, ARG,
	// Arabic Morocco, Arabic Tunisia, Arabic Oman,Arabic Yemen, Arabic Syria, Arabic Jordan
	ARM, ART, ARO, ARY, ARS, ARJ,
	// Arabic Lebanon,Arabic Kuwait,Arabic U.A.E.,Arabic Bahrain, Arabic Qatar, Bulgarian Bulgaria
	ARB, ARK, ARU, ARH, ARQ, BGR,
	// Catalan Spain, Chinese Taiwan, Chinese PRC, Chinese Hong Kong, Chinese Singapore, Chinese Macau
	CAT, CHT, CHS, ZHH, ZHI, ZHM,
	// Czech Czech Republic, Danish Denmark,  German Germany, German Switzerland, German Austria, German Luxembourg
	CSY, DAN, DEU, DES, DEA, DEL,
	// German Liechtenstein, Greek Greece, English United States, English United Kingdom, English Australia, English Canada
	DEC, ELL, ENU, ENG, ENA, ENC,
	// English New Zealand, English Ireland, English South Africa, English Jamaica, English Caribbean, English Belize
	ENZ, ENI, ENS, ENJ, ENB, ENL,
	// English Trinidad, English Zimbabwe, English Philippines, Spanish Spain (Traditional Sort), Spanish Mexico, Spanish Spain (International Sort)
	ENT, ENW, ENP, ESP, ESM, ESN,
	// Spanish Guatemala, Spanish Costa Rica, Spanish Panama, Spanish Dominican Republic, Spanish Venezuela, Spanish Colombia
	ESG, ESC, ESA, ESD, ESV, ESO,
	// Spanish Peru, Spanish Argentina, Spanish Ecuador, Spanish Chile, Spanish Uruguay, Spanish Paraguay
	ESR, ESS, ESF, ESL, ESY, ESZ,
	// Spanish Bolivia, Spanish El Salvador, Spanish Honduras, Spanish Nicaragua, Spanish Puerto Rico, Finnish Finland
	ESB, ESE, ESH, ESI, ESU, FIN,
	// French France, French Belgium, French Canada, French Switzerland, French Luxembourg, French Monaco
	FRA, FRB, FRC, FRS, FRL, FRM,
	// Hebrew Israel, Hungarian Hungary, Icelandic Iceland, Italian Italy, Italian Switzerland, Japanese Japan
	HEB, HUN, ISL, ITA, ITS, JPN,
	// Korean (Extended Wansung) Korea, Dutch Netherlands, Dutch Belgium, Norwegian Norway (BokmÂl), Norwegian Norway (Nynorsk), Polish Poland
	KOR, NLD, NLB, NOR, NON, PLK,
	// Portuguese Brazil, Portuguese Portugal, Romanian Romania, Russian Russia,  Croatian Croatia, Serbian Serbia (Latin)
	PTB, PTG, ROM, RUS, HRV, SRL,
	// Serbian Serbia (Cyrillic), Slovak Slovakia, Albanian Albania, Swedish Sweden, Swedish Finland, Thai Thailand
	SRB, SKY, SQI, SVE, SVF, THA,
	// Turkish Turkey, Urdu Pakistan, Indonesian Indonesia, Ukrainian Ukraine, Belarusian Belarus, Slovene Slovenia
	TRK, URP, IND, UKR, BEL, SLV,
	// Estonian Estonia, Latvian Latvia, Lithuanian Lithuania, Classic Lithuanian Lithuania, Farsi Iran, Vietnamese Viet Nam
	ETI, LVI, LTH, LTC, FARR, VIT,  // We do FARR versus FAR because FAR is a compilier keyword
	// Armenian Armenia, Azeri Azerbaijan (Latin), Basque Spain, Macedonian Macedonia, Afrikaans South Africa, Georgian Georgia
	HYE, AZE, EUQ, MKI, AFK, KAT,
	// Faeroese Faeroe Islands, Hindi India, Malay Malaysia, Malay Brunei Darussalam, Kazak Kazakstan, Swahili Kenya
	FOS, HIN, MSL, MSB, KAZ, SWK,
	// Uzbek Uzbekistan (Cyrillic), Tatar Tatarstan, Bengali India, Punjabi India, Gujarati India, Oriya India
	UZB, TAT, BEN, PAN, GUJ, ORI,
	// Tamil India, Telugu India, Kannada India, Malayalam India, Assamese India, Marathi India
	TAM, TEL, KAN, MAL, ASM, MAR,
	// Sanskrit India, Konkani India
	SAN, KOK
};
auto nameForUnicode(unicode_t value) ->const std::string&;
auto unicodeForName(const std::string &name) ->unicode_t ;
//=========================================================
auto unicodeNames() ->const std::unordered_map<unicode_t,std::string>& ;

/* *****************************************************************
 language_t
 ******************************************************************* */
enum class language_t {none,english,german,spanish,french,portuguese,italian,czech,polish,russian,japanese} ;
auto nameForLanguage(language_t value) ->const std::string&;
auto languageForName(const std::string &name) ->language_t ;
auto languageNames() ->const std::unordered_map<language_t,std::string>&;
auto languageForUnicode(unicode_t value) ->language_t ;
#endif /* system_types_hpp */
