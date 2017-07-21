#include <cstdint>
#include <string>
#include <fstream>

using namespace std;

class LocalFileHeader {
private:
    const uint32_t signature = 0x04034b50;
    uint16_t version;
    uint16_t flag;
    uint16_t compression_method;
    uint16_t mod_file_time;
    uint16_t mod_file_date;
    uint32_t crc32;
    uint32_t compressed_size;
    uint32_t uncompressed_size;
    uint16_t file_name_length;
    uint16_t extra_field_length;
    string filename;

public:
	LocalFileHeader(string filename, uint32_t size, uint32_t crc32);
	void dump(ofstream& stream);
	uint32_t size() { return 30 + filename.size(); }
};

class CentralDirectoryHeader {
private:
    const uint32_t signature = 0x02014b50;
    uint16_t version;
    uint16_t version_needed_to_extract;
    uint16_t flag;
    uint16_t compression_method;
    uint16_t mod_file_time;
    uint16_t mod_file_date;
    uint32_t crc32;
    uint32_t compressed_size;
    uint32_t uncompressed_size;
    uint16_t file_name_length;
    uint16_t extra_field_length;
    uint16_t file_comment_length;
    uint16_t disk_number_start;
    uint16_t internal_file_attributes;
    uint32_t external_file_attributes;
    uint32_t offset_of_local_header;
    string filename;

public:
	CentralDirectoryHeader(string filename, uint32_t size, uint32_t crc32);
	void dump(ofstream& stream);
	uint32_t size() { return 46 + filename.size(); }
};

class EndofCentralDirectoryRecord {
private:
    const uint32_t signature = 0x06054b50;
    uint16_t num_of_this_disk; //このディスクの番号
    uint16_t num_of_start_central_directory;
    uint16_t total_number_on_this_disk;
    uint16_t total_number;
    uint32_t sizeof_central_directory;
    uint32_t starting_disk_number; //offset
    uint16_t comment_length;

public:
	EndofCentralDirectoryRecord(uint32_t size, uint32_t offset);
	void dump(ofstream& stream);
};

struct discripter {
	uint32_t signature = 0x08074b50;
    uint32_t crc32;
    uint32_t compressed_size;
    uint32_t uncompressed_size;
};

void create_single_zip(string src, string dist);
// void create_empty_zip(string path);
// local_file_header create_local_file_header(uint16_t size, uint32_t file_name_size, uint32_t crc32);
// central_directory_header create_central_directory_header(uint16_t size, uint32_t file_name_size, uint32_t crc32);

unsigned long crc(unsigned char *buf, int len);
