//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef object_types_hpp
#define object_types_hpp

#include <cstdint>
#include <unordered_map>

//=========================================================
using serial_t = std::uint32_t ;
constexpr auto invalid_serial = serial_t(0xFFFFFFFF) ;

/* ***************************************************************
 objecttype_t
 ***************************************************************** */
enum class objecttype_t {base,item,mob,player,spawner,multi};
auto objecttypeForName(const std::string &name) ->objecttype_t ;
auto nameForObjecttype(objecttype_t objecttype) ->const std::string& ;
auto objecttypeNames() ->const std::unordered_map<objecttype_t,std::string>& ;
#endif /* object_types_hpp */
