//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef baseobj_hpp
#define baseobj_hpp

#include <cstdint>
#include <string>
#include <vector>

#include "object_types.hpp"
#include "position_types.hpp"
#include "section.hpp"

struct factory_t ;

//=========================================================
struct baseobj_t {
protected:
	std::vector<keyvalue_t> secondary ;
public:
	objecttype_t type  ;
	serial_t serial ;
	location_t location ;
	attrib_t attr ;
	
	baseobj_t() ;
	virtual ~baseobj_t() = default ;
	
	auto save(std::ostream &output) ->void ;
	virtual auto saveContents(std::ostream &output) ->void ;

	auto loadWorldSection(const section_t &section, factory_t *factory) ->bool ;
	virtual auto processWorldKey(const keyvalue_t &keyvalue,factory_t *factory) ->bool ;

	auto secondaryLoad(factory_t *factory) ->void ;
	virtual auto secondaryLoad(const keyvalue_t &keyvalue, factory_t *factory)->bool ;

	auto loadServerSection(const section_t &section, factory_t *factory) ->bool ;
	virtual auto processServerKey(const keyvalue_t &keyvalue, factory_t *factory) ->bool ;
	
};
#endif /* baseobj_hpp */
