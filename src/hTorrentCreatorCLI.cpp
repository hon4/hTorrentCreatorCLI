#include <iostream>
#include <string>
#include <map>
#include <any>
#include <vector>
#include <fstream>
#include <cstring>
#include <cstdint>

#include "inc/honSHA1.h"
#include "inc/BEncode/BEncode.h"
#include "inc/isDIR.h"
#include "inc/GetFileName.h"
#include "inc/GetFileSize.h"
#include "inc/UnixTimestamp.h"
#include "inc/WriteFile.h"
#include "inc/GetPieceSize.h"
#include "inc/StringSplit.h"
#include "inc/ProgressBar.h"
#include "inc/ListFiles.h"
#include "inc/NormalizePath.h"
using namespace std;

string hTorrentCreatorCLI_ver = "0.0.5";

void show_help();
void show_ver();
int mkTorrent(const std::string& input_path, const bool& priv, std::string& out_path, const std::vector<std::string>& trackers, const uint32_t& piece_size_user, const std::vector<std::any>& webseeds, const std::string& comment);
std::string PieceHashFile(const std::string& filename, const uint32_t& piece_size, const uint64_t& filesize);
std::string PieceHashFolder(const std::string& input_path, const std::vector<std::string>& filelist, const uint32_t& piece_size);
std::string PieceHashFile4Folder(const std::string& filename, const uint32_t& piece_size, std::string& remain, const uint64_t& filesize);


int main(int argc, char *argv[]){
	if(argc==1){
		printf("hTorrentCreatorCLI: No command.\nType -h to show help.\n");
		return 0;
	}

	string input_path;
	bool priv=false;
	string out_path;
	vector<string> trackers;
	uint32_t piece_size;
	vector<any> webseeds;
	string comment;

	for(int i=1; i<argc; i++){
		if(!strcmp(argv[i],"-h")){
			show_help();
			return 0;
		}else if(!strcmp(argv[i],"-v")){
			show_ver();
			return 0;
		}else if(!strcmp(argv[i],"-i")){
			i++;
			if(argc>i){
				input_path = argv[i];
			}else{
				printf("hTorrentCreatorCLI: Error: -i is used but no input file specified.\n");
				return 0;
			}
		}else if(!strcmp(argv[i],"-p")){
			priv=true;
		}else if(!strcmp(argv[i],"-o")){
			i++;
			if(argc>i){
				out_path = argv[i];
			}else{
				printf("hTorrentCreatorCLI: Error: -o is used but no output file specified.\n");
				return 0;
			}
		}else if(!strcmp(argv[i],"-t")){
			i++;
			if(argc>i){
				trackers.push_back(std::string(argv[i]));
			}else{
				printf("hTorrentCreatorCLI: Error: -t is used but no tracker url specified.\n");
				return 0;
			}
		}else if(!strcmp(argv[i],"-s")){
			i++;
			if(argc>i){
				piece_size = atoi(argv[i]);
				if(piece_size<16384||piece_size>16777216){
					printf("hTorrentCreatorCLI: Error: -s The piece size must be greater than 16384 and less than 16777216.\n");
					return 0;
				}
			}else{
				printf("hTorrentCreatorCLI: Error: -s is used but no piece size specified.\n");
				return 0;
			}
		}else if(!strcmp(argv[i],"-w")){
			i++;
			if(argc>i){
				webseeds.push_back(std::string(argv[i]));
			}else{
				printf("hTorrentCreatorCLI: Error: -w is used but no tracker url specified.\n");
				return 0;
			}
		}else if(!strcmp(argv[i],"-c")){
			i++;
			if(argc>i){
				comment=argv[i];
			}else{
				printf("hTorrentCreatorCLI: Error: -c is used but no comment specified.\n");
				return 0;
			}
		}
	}

	return mkTorrent(input_path, priv, out_path, trackers, piece_size, webseeds, comment);
}

int mkTorrent(const std::string& input_path, const bool& priv, std::string& out_path, const std::vector<std::string>& trackers, const uint32_t& piece_size_user, const std::vector<std::any>& webseeds, const std::string& comment){
	if(input_path.empty()){
		std::cout << "hTorrentCreatorCLI: No input file specified.\n";
		return 0;
	}else{
		std::ifstream file(input_path);
		if(file.is_open()){
			file.close();
		}else{
			std::cout << "hTorrentCreatorCLI: Input file/directory does not exist.\n";
			return 0;
		}
	}

	map<string, any> dict;
	//Announce
	if(!trackers.empty()){
		dict["announce"]=StringSplit(trackers[0],'|')[0];

		//Announce list
		if(trackers.size()>1||trackers[0].find('|') != string::npos){
			vector<any> announce_list;
			for (int i=0; i < trackers.size(); i++) {
				vector<any> tmp_trck_vctr=StringSplit(trackers[i],'|');
				announce_list.push_back(tmp_trck_vctr);
			}
			dict["announce-list"]=announce_list;
		}
	}
	
	//Comment
	if(!comment.empty()){
		dict["comment"]=comment;
	}

	dict["created by"]="hTorrentCLI "+hTorrentCreatorCLI_ver;
	dict["creation date"]=GetUnixTimestamp();
	uint64_t filesize = GetFileSize(input_path);
	uint32_t piece_size;
	if(piece_size_user==0){
		piece_size = GetPieceSize(filesize);
	}else{
		piece_size = piece_size_user;
	}

	map<string, any> info_dict;
	string fname=GetFileName(input_path);

	vector<string> files;
	if(!isDIR(input_path)){
		info_dict["length"]=filesize;
	}else{
		files=ListFiles(const_cast<string&>(input_path));
		string prefix_path=NormalizePath(input_path);
		vector<any> file_lst;
		for (string tfile : files) {
			map<string, any> tmp;
			tmp["length"]=GetFileSize(NormalizePath(input_path)+tfile);
			tmp["path"]=StringSplit(tfile, '/');
			file_lst.push_back(tmp);
		}
		info_dict["files"]=file_lst;
	}
	info_dict["name"]=fname;
	info_dict["piece length"]=piece_size;
	if(!isDIR(input_path)){
		info_dict["pieces"]=PieceHashFile(input_path, piece_size, filesize);
	}else{
		info_dict["pieces"]=PieceHashFolder(NormalizePath(input_path), files, piece_size);
	}
	cout << "\n"; //for newline after progress bar(s)
	if(priv){
		info_dict["private"]=1;
	}

	dict["info"]=std::any(info_dict);

	//WebSeeds
	if(!webseeds.empty()){
		dict["url-list"]=webseeds;
	}

	BEncode BEnc;

	if(out_path.empty()){
		out_path=fname+".torrent";
	}

	if(WriteFile(out_path,BEnc.Encode(dict))){
		cout << "Torrent File successfully created.\n";
	}else{
		return 1;
	}
	return 0;
}

std::string PieceHashFolder(const std::string& input_path, const std::vector<std::string>& filelist, const uint32_t& piece_size){
	std::string ret;
	std::string remain;

	for (string tfile : filelist) {
		std::string filename=input_path+tfile;
		ret+=PieceHashFile4Folder(filename, piece_size, remain, GetFileSize(filename));
	}

	if(!remain.empty()){
		ret+=honSHA1(remain);
	}

	return ret;
}

std::string PieceHashFile4Folder(const std::string& filename, const uint32_t& piece_size, std::string& remain, const uint64_t& filesize){
	std::string ret;
    std::ifstream file(filename, std::ios::binary);
	std::cout << "\nHashing: " << filename << std::endl;

	if (!file) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return ret;
	}

	uint64_t total_hashed = 0;
    std::string buffer(piece_size, '\0');
	std::memcpy(&buffer[0], remain.data(), remain.size());
    while (file.read(&buffer[remain.size()], piece_size-remain.size()) || file.gcount() > 0) {
		buffer.resize(remain.size()+file.gcount());
        total_hashed += file.gcount();
		if(buffer.size()==piece_size){
        	ret += honSHA1(buffer);
			remain="";
		}else{
			buffer.resize(file.gcount());
			remain+=buffer;
		}
		ShowProgressBar(const_cast<uint64_t&>(filesize), total_hashed);
		buffer.resize(piece_size);
    }

	file.close();
	return ret;
}

std::string PieceHashFile(const std::string& filename, const uint32_t& piece_size, const uint64_t& filesize) {
	std::string ret;
	std::ifstream file(filename, std::ios::binary);
	std::cout << "Hashing: " << filename << std::endl;

	if (!file) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return ret;
	}

	uint64_t total_hashed = 0;
	std::string buffer(piece_size, '\0');
	while (file.read(&buffer[0], piece_size) || file.gcount() > 0) {
		buffer.resize(file.gcount());
		total_hashed += file.gcount();
		ret += honSHA1(buffer);
		buffer.resize(piece_size);
		ShowProgressBar(const_cast<uint64_t&>(filesize), total_hashed);
	}

	file.close();
	return ret;
}


void show_help(){
	printf("\nhTorrentCreatorCLI %s\n==========================\n-v         Show version info and exit.\n-h         Show this menu and exit.\n-i <path>  Select input path.\n-p         Set private flag to torrent.\n-o <path>  Select output file.\n-t <url>   Add tracker announce url. (can be used multiple times)\n-s <size>  Set piece size in bytes. (calculated automatically if unset)\n-w <url>   Add WebSeed url. (can be used multiple times)\n-c <text>  Add comment in torrent file.\n\n",hTorrentCreatorCLI_ver.c_str());
}

void show_ver(){
	printf("\nhTorrentCreatorCLI %s\n==========================\nCoded by: hon\nLanguage: c++\n\n",hTorrentCreatorCLI_ver.c_str());
}
