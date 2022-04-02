//Copyright © 2022 Charles Kerr. All rights reserved.

#include "position_types.hpp"

#include <iostream>
#include <algorithm>

#include "strutil.hpp"

using namespace std::string_literals;
/* ******************************************************************
 point_t
 ***************************************************************** */
//=========================================================
point_t::point_t() {
	x=0;
	y=0;
	z=0 ;
	coordinates = 3 ;
}
//=========================================================
point_t::point_t(int x,int y) :point_t(){
	this->x = x ;
	this->y = y ;
	coordinates = 2 ;
}
//=========================================================
point_t::point_t(int x, int y, int z):point_t(){
	this->x = x ;
	this->y = y ;
	this->z = z ;
	coordinates = 3 ;
}
//=========================================================
point_t::point_t(const std::string &value):point_t(){
	if (!value.empty()) {
		auto values = strutil::parse(value,",") ;
		if (values.size() > 1) {
			coordinates = static_cast<int>(values.size()) ;
			switch(coordinates){
				default:
					coordinates = 3 ;
					[[fallthrough]];
				case 3:
					this->z = strutil::ston<int>(values[2]);
					[[fallthrough]] ;
				case 2:
					this->y = strutil::ston<int>(values[1]);
					[[fallthrough]] ;
				case 1:
					this->x = strutil::ston<int>(values[0]);
					coordinates = 2 ;
					[[fallthrough]] ;
				case 0:
					break;
			}
		}
	}
}
//=========================================================
auto point_t::value() const ->std::string {
	auto rvalue = strutil::ntos(x) ;
	rvalue += ","s + strutil::ntos(y);
	if (coordinates>2){
		rvalue += ","s + strutil::ntos(z);
	}
	return rvalue ;
}
//=========================================================
auto point_t::equal(const point_t &value, int coordinate) const ->bool {
	auto rvalue = true ;
	if ( coordinate >2) {
		rvalue = this->z == value.z ;
	}
	return rvalue && (this->x == value.x) && (this->y == value.y) ;
}
//=========================================================
auto point_t::operator==(const point_t &value) const ->bool {
	auto coord = std::min(coordinates,value.coordinates) ;
	return this->equal(value, coord) ;
}
//=========================================================
auto point_t::operator!=(const point_t &value) const ->bool {
	return !this->operator==(value) ;
}
/* ******************************************************************
 rect_t
 ***************************************************************** */
//=========================================================
rect_t::rect_t(point_t lleft,point_t uright):rect_t() {
	this->lleft = lleft ;
	this->uright = uright ;
}
//=========================================================
rect_t::rect_t(const std::string &value):rect_t(){
	auto [lline,rline] = strutil::split(value,":") ;
	lleft = point_t(lline) ;
	uright = point_t(rline) ;
}
//=========================================================
auto rect_t::value() const ->std::string {
	return lleft.value()+":"s+uright.value();
}
//=========================================================
auto rect_t::bound(const point_t &point,bool inclusive  )const ->bool{
	auto rvalue = false ;
	if (inclusive){
		rvalue = (point.x >= this->lleft.x) && (point.x <= this->uright.x) &&
		(point.y >= this->lleft.y) && (point.y <= this->uright.y) ;
	}
	else {
		rvalue = (point.x > this->lleft.x) && (point.x < this->uright.x) &&
		(point.y > this->lleft.y) && (point.y < this->uright.y) ;

	}
	return rvalue ;

}
//=========================================================
auto rect_t::bound(const rect_t &rect,bool inclusive  )const ->bool{
	return this->bound(rect.lleft,inclusive) && this->bound(rect.uright,inclusive);
}
//=========================================================
auto rect_t::width() const -> int {
	return (uright.x - lleft.x);
}
//=========================================================
auto rect_t::height() const ->int {
	return (uright.y - lleft.y);
}
//=========================================================
auto rect_t::size() const ->int {
	return (uright.x - lleft.x) * (uright.y - lleft.y);
}
//=========================================================
auto rect_t::operator==(const rect_t &value) const ->bool {
	return (lleft == value.lleft) && (uright == value.uright);
}
//=========================================================
auto rect_t::operator!=(const rect_t &value) const ->bool {
	return !this->operator==(value);
}
//=========================================================
auto rect_t::operator<(const rect_t &value) const ->bool {
	return this->size() < value.size() ;
}

/* ******************************************************************
 location_t
 ***************************************************************** */
//=========================================================
location_t::location_t() {
	world = -1 ;
}
//=========================================================
location_t::location_t(point_t point, int world):location_t(){
	this->position = point;
	this->world = world ;
	
}
//=========================================================
location_t::location_t(const std::string &line):location_t(){
	auto values = strutil::parse(line,":") ;
	if (!values.empty()){
		position = point_t(values[0]);
		if (values.size()>1){
			world = std::stoi(values[1]);
		}
	}
}
//=========================================================
auto location_t::value() const ->std::string {
	return position.value()+":"s+std::to_string(world);
}
	
/* ******************************************************************
 area_t
 ***************************************************************** */
//=========================================================
area_t::area_t(const std::string &value){
	belongs = nullptr;
	if (!value.empty()){
		boundary = rect_t(value) ;
	}
}


/* ******************************************************************
 region_t
 ***************************************************************** */
//=========================================================
auto region_t::appendTo(std::vector<area_t> &areas) ->void {
	areas.insert(std::end(areas),std::begin(this->areas),std::end(this->areas));
}
//=========================================================
auto region_t::add(area_t area) ->void {
	area.belongs = this ;
	this->areas.push_back(area);
}
//=========================================================
auto region_t::add(const std::string &value) ->void {
	auto area = area_t(value) ;
	area.belongs = this ;
	this->areas.push_back(area);
}
//=========================================================
auto region_t::save(std::ostream &output, const std::string &key )->void {
	for (const auto &entry : areas){
		output <<"\t"<<key<<" = "<<entry.boundary.value()<<"\n" ;
	}
}
//=========================================================
region_t::region_t(const region_t& regions)  {
	areas.clear() ;
	areas = regions.areas ;
	// We have to update the pointers!
	std::transform(areas.begin(), areas.end(), areas.begin(), [this](area_t &area) ->area_t{
		area.belongs = this ;
		return area ;
	});
}
//=========================================================
auto region_t::operator=(const region_t &regions) ->region_t& {
	areas.clear() ;
	areas = regions.areas ;
	// We have to update the pointers!
	std::transform(areas.begin(), areas.end(), areas.begin(), [this](area_t &area) ->area_t{
		area.belongs = this ;
		return area ;
	});
	return *this ;
}
