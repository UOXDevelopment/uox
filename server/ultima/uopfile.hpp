//Copyright © 2022 Charles Kerr. All rights reserved.

#ifndef uopfile_hpp
#define uopfile_hpp
/*******************************************************************************
 Acknowledgement
 This information was gleamed from Mythic LegacyMul Convertor and UOFiddler.
 Special thanks for those that deciphered that data, and allowing that
 source to be available for others to examine and learn.
 
 ******************************************************************************/
/*******************************************************************************
 Hashes
 Hashes are used to define who the data is used (what it represents).
 There are two types of hashes used (Alder32 and HashLittle2). For
 more information on these refer to http://burtleburtle.net/bob/c/lookup3.c
 In the hashstrings, {#} is used as subsitution placeholders.  The # represents
 the number of characters the final substituion should be (to pad leading 0).
 So a {2} would indicate that it should be two characters. So if one is reprenting
 a number 1, it would result in 01.
 
 The hash strings used for each file type are as follows(case is important).
 Some file types use two different hashes. In addition the number of keys(hashes)
 to be built can very.  Other programs that process UOP files use
 0x7FFFF as an entry.
 
 Art
 "build/artlegacymul/{8}.tga"
 The number being replaced essentially corresponds to the idx
 entry in artidx.mul.
 The number of keys to be built is around 0x13FDC.
 UOFiddler requires this exact idx length to recognize UOHS art files (it checks with == operator, not with >=)
 
 GumpArt
 "build/gumpartlegacymul/{8}.tga"
 "build/gumpartlegacymul/{7}.tga"
 The number being replaced essentially corresponds to the idx
 entry in gumpidx.mul.
 
 Map
 "build/map{1}legacymul/{8}.dat"
 The first substitution is the map number, the second one is the
 index.  An index represents index*C4000 location in a corresponding
 map mul file.
 
 Sound
 "build/soundlegacymul/{8}.dat"
 
 Multi
 "build/multicollection/{6}.bin"
 
 Embedded with the multi data is a file, housing.bin.  This
 is identifed has file hash : 0x126D1E99DDEDEE0A
 It is compressed, and that data should be treated as a
 not part of the multi.mul, but a separate file housing.bin.
 ******************************************************************************/

/*******************************************************************************
 Notes/Exceptions
 For the most part, when one access the data pointed to by that
 entry, it has the same format as the data in corresponding mul file.
 Exceptions:
 Gumps
 The first 8 bytes of the data represent the the width
 (bytes 0-4) and height (bytes 4-8) of the gump
 ******************************************************************************/

/*******************************************************************************
 UOP file format
 UOP format holds a variety of different data for Ultima Online.  The
 file contains table(s) of index entries , which contains information about where
 the data is in the file for that entry.  It also contains whether or not the data
 is compress (zlib compression), and a hash!  This hash is based on the original
 file name , and it format varies based on each file type.  The hash has a direct
 correlation of what "index" in an IDX (or mapblock for non idx files) the data
 is correlated with.
 
 A table entry has the following format
 
 UOP Table entry:
 
 std::int64_t	data_offset	;	// Offset to the data for this entry (actually, best I can tell
 // this is the offset to this header, for the data one adds the header length
 // to it.  So not sure if the TableEntry can actually not be right before
 // the data or not.  Some implementations may just assume.)
 std::uint32_t	header_length;	// Length of header
 std::uint32_t	compress_size;	// Compressed size of data
 std::uint32_t	decompress_size;	// Decompressed size of data
 std::uint64_t	identifer;		// Filename(index) hash (HashLittle2)
 std::uint32_t	data_hash;		// Data hash (Alder32)
 std::int16_t	compression;	// 0 = none, 1 = zlib
 
 
 Using the table entry, the file format is as follows
 
 UOP File Format (the table entry will be at offset 0x28 or greater):
 
 std::int32_t	signature;		// This signifies to be a UOP file
 // and has a fixed value of
 // 0x50594D  ('MYP')
 std::int32_t	version;		// Version of the format/file
 // At this time believe this documentation
 // is valid for versions below 5 inclusive
 std::int32_t	timestamp;		// ? Uknown, believed to be a timestamp or something
 // for the file (0xFD23EC43)
 
 std::uint64_t	table_offset;	// Offset to the next table
 // There can be multiple tables in the file!
 
 std::uint32_t	tablesize		// Only needed really for writing(table (block) size)
 // current value is 1000
 std::uint32_t	filecount		// Each entry is consider a file
 std::int32_t	unknown		// Value is 1, perhaps modified count?
 std::int32_t	unknown		// Value is 1
 std::int32_t	unknown		// Value is 0
 
 
 
 The following is repeated for each table
 
 std::uint32_t	number_entries;	// how many entries are in the table
 std::uint64_t	next_table;		// Offset to the next table
 
 UOPTable		table[number_entries];
 ******************************************************************************/
#include <cstdint>
#include <string>
#include <vector>
#include <zlib.h>
class tileinfo;

class uopfile {
private:
	static constexpr 	std::uint32_t _uop_identifer = 0x50594D;
	static constexpr	std::uint32_t _uop_version = 5 ;
	
	struct table_entry {
		std::int64_t	offset ;
		std::uint32_t	header_length ;
		std::uint32_t	compressed_length ;
		std::uint32_t	decompressed_length ;
		std::uint64_t	identifer ;
		std::uint32_t	data_block_hash ;
		std::int16_t	compression ;
		table_entry();
		auto 	load(std::istream &input) ->table_entry & ;
		auto	save(std::ostream &output) ->table_entry & ;
		// 34 bytes for a table entry
		/*********************** Constants used ******************/
		static constexpr unsigned int _entry_size = 34 ;
		
	};
	
	std::vector<std::uint64_t> _hash1 ;
	std::vector<std::uint64_t> _hash2 ;
	
	/************************************************************************
	 Hash routines
	 ***********************************************************************/
	static auto hashLittle2(const std::string& s) ->std::uint64_t ;
	static auto hashAdler32(const std::vector<std::uint8_t> &data) ->std::uint32_t ;
	auto findIndex(const std::vector<std::uint64_t> &hashdata, std::uint64_t hash) ->std::size_t;
	
	/****************** zlib compression wrappers *********************/
	auto zcompress(const std::vector<std::uint8_t> &data) const ->std::vector<unsigned char>;
	auto zdecompress(const std::vector<std::uint8_t> &source, std::size_t decompressed_size) const ->std::vector<unsigned char>;
	
	
	auto buildIndexHashes(const std::string &hashformat, std::size_t max_index) ->std::vector<std::uint64_t>;
	auto hashLittleFor(const std::string &hashstring, std::size_t index) const ->std::uint64_t;

	
protected:
	//==============================================================================
	// Virtual routines, modify based on uop file processing
	//==============================================================================
	virtual auto processEntry(std::size_t entry, std::size_t index, std::vector<std::uint8_t> &data,tileinfo *info=nullptr) ->bool {return true;}
	virtual auto processHash(std::uint64_t hash,std::size_t entry , std::vector<std::uint8_t> &data) ->bool {return true;}
	virtual auto nonIndexHash(std::uint64_t hash, std::size_t entry, std::vector<std::uint8_t> &data)->bool;
	virtual auto endUOPProcessing() ->bool {return true ;};

	virtual auto entriesToWrite()const ->int {return 0;}
	virtual auto writeCompress() const ->bool {return false ;}
	virtual auto entryForWrite(int entry)->std::vector<unsigned char>{return std::vector<unsigned char>();}
	virtual auto writeHash(int entry)->std::string{return std::string();} ;
	//========================================================================
	auto isUOP(const std::string &filepath) const ->bool ;
	
	auto loadUOP(const std::string &filepath, std::size_t max_hashindex, const std::string &hashformat1, tileinfo * info=nullptr ,const std::string &hashformat2 ="") ->bool ;
	
	auto writeUOP(const std::string &filepath)  ->bool ;
	
public:
	virtual ~uopfile() = default ;

};

#endif /* UOPFile_hpp */
