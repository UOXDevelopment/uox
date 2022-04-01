//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef position_types_hpp
#define position_types_hpp

#include <cstdint>
#include <string>

/* ******************************************************************
 point_t
 ***************************************************************** */
//=========================================================
struct point_t {
	int x ;
	int y ;
	int z ;
	int coordinates;
	point_t() ;
	point_t(int x,int y) ;
	point_t(int x, int y, int z);
	point_t(const std::string &value);
	auto value() const ->std::string ;
	auto equal(const point_t &value, int coordinate) const ->bool ;
	auto operator==(const point_t &value) const ->bool ;
	auto operator!=(const point_t &value) const ->bool ;

};
/* ******************************************************************
 rect_t
 ***************************************************************** */
//=========================================================
struct rect_t {
	point_t lleft ;
	point_t uright ;
	rect_t() = default ;
	rect_t(point_t lleft,point_t uright) ;
	rect_t(const std::string &value);
	auto value() const ->std::string ;
	auto bound(const point_t &point,bool inclusive = true )->bool;
	auto bound(const rect_t &rect,bool inclusive = true )->bool;
	auto width() const -> int ;
	auto height() const ->int ;
	auto size() const ->int ;
	auto operator==(const rect_t &value) const ->bool ;
	auto operator!=(const rect_t &value) const ->bool ;
	auto operator<(const rect_t &value) const ->bool ;
};
/* ******************************************************************
 location_t
 ***************************************************************** */
struct location_t {
	point_t position ;
	int world ;
	int realm ;
	
	location_t() ;
	location_t(point_t point, int world, int realm=0);
	location_t(const std::string &line);
	auto value() const ->std::string ;
	
};
#endif /* position_types_hpp */
