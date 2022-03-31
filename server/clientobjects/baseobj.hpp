//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef baseobj_hpp
#define baseobj_hpp

#include <cstdint>
#include <string>
#include <vector>

#include "object_types.hpp"
#include "section.hpp"

class factory_t ;

//=========================================================
struct baseobj_t {
protected:
	std::vector<keyvalue_t> secondary ;
public:
	objecttype_t type  ;
	serial_t serial ;
	
	baseobj_t() ;
	virtual ~baseobj_t() = default ;
	
	auto save(std::ostream &output) ->void ;
	virtual auto saveContents(std::ostream &output) ->void ;

	auto loadWorldSection(section_t &section, factory_t *factory) ->bool ;
	virtual auto processWorldKey(keyvalue_t &keyvalue,factory_t *factory) ->bool ;

	auto secondaryLoad(factory_t *factory) ->void ;
	virtual auto secondaryLoad(keyvalue_t &keyvalue, factory_t *factory)->bool ;

	auto loadServerSection(section_t &section, factory_t *factory) ->bool ;
	virtual auto processServerKey(keyvalue_t &keyvalue, factory_t *factory) ->bool ;
	
};
#endif /* baseobj_hpp */
