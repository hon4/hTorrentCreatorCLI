#include <iostream>
#include <string>
#include <map>
#include <any>
#include <vector>
#include <fstream>

#include "inc/honSHA1.h"
#include "inc/BEncode/BEncode.h"
#include "inc/isDIR.h"
using namespace std;

string hTorrentCreatorCLI_ver = "0.0.1";

void show_help();
void show_ver();
int mkTorrent(const std::string& input_path);
std::string PieceHashFile(const std::string& filePath, const int& piece_size);

int main(int argc, char *argv[]){
	//BEncode BEncode;
	//map<string, any> dict;
	//string s="hello";
	//dict["key"] = std::any(s);
	//cout << BEncode.Encode(dict);
	
	if(argc==1){
		printf("hTorrentCreatorCLI: No command.\nType -h to show help.\n");
		return 0;
	}

	string input_path;

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
		}
	}

	mkTorrent(input_path);
	
	return 0;
}

int mkTorrent(const std::string& input_path){
	map<string, any> dict;
    PieceHashFile(input_path, 8);
    return 0;
}

std::string PieceHashFile(const std::string& filePath, const int& piece_size){
    std::string ret;

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return 0; // error
    }

    char buffer[piece_size + 1]; // +1 for null terminator
    while (file.read(buffer, piece_size)) {
        buffer[piece_size] = '\0'; // Ensure null termination
        std::string chunk(buffer);

        std::cout << "Chunk: " << chunk << " - "<< honSHA1(chunk) << std::endl;
    }

    if (file.gcount() > 0) {
        buffer[file.gcount()] = '\0'; // Null terminate the last chunk
        std::string lastChunk(buffer);

        std::cout << "Last Chunk: " << lastChunk <<  std::endl;
    }

    file.close();
}

void show_help(){
	printf("\nhTorrentCreatorCLI %s\n==========================\n-v  Show version info and exit.\n-h  Show this menu and exit.\n-i  Select input path.\n\n",hTorrentCreatorCLI_ver.c_str());
}

void show_ver(){
	printf("\nhTorrentCreatorCLI %s\n==========================\nCoded by: hon\nLanguage: c++\n\n",hTorrentCreatorCLI_ver.c_str());
}