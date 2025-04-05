#include <iostream>
#include <string>
#include <map>
#include <any>
#include <vector>
#include <fstream>

#include "inc/honSHA1.h"
#include "inc/BEncode/BEncode.h"
#include "inc/isDIR.h"
#include "inc/GetFileName.h"
#include "inc/GetFileSize.h"
#include "inc/UnixTimestamp.h"
#include "inc/WriteFile.h"
using namespace std;

string hTorrentCreatorCLI_ver = "0.0.1";

void show_help();
void show_ver();
int mkTorrent(const std::string& input_path, const bool& priv, std::string& out_path);
std::string PieceHashFile(const std::string& filename, const int& piece_size);

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
	bool priv=false;
	string out_path;

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
                }
	}

	mkTorrent(input_path, priv, out_path);
	
	return 0;
}

int mkTorrent(const std::string& input_path, const bool& priv, std::string& out_path){
	map<string, any> dict;
	dict["created by"]="hTorrentCreatorCLI "+hTorrentCreatorCLI_ver;
	dict["creation date"]=GetUnixTimestamp();
	int piece_size = 16384;

	map<string, any> info_dict;
	string fname=GetFileName(input_path);
	info_dict["length"]=GetFileSize(input_path);
	info_dict["name"]=fname;
	info_dict["piece length"]=piece_size;
	info_dict["pieces"]=PieceHashFile(input_path, piece_size);
	if (priv) {
		info_dict["private"]=1;
	}

	dict["info"]=std::any(info_dict);

	BEncode BEnc;

	if (out_path.empty()) {
		out_path=fname+".torrent";
	}

	WriteFile(out_path,BEnc.Encode(dict));
	cout << "Torrent File successfully created." << endl;
	return 0;
}

std::string PieceHashFile(const std::string& filename, const int& piece_size) {
    std::string ret;
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return ret;
    }

    std::string buffer(piece_size, '\0');
    while (file.read(&buffer[0], piece_size) || file.gcount() > 0) {
        buffer.resize(file.gcount());
        ret += honSHA1(buffer);
        buffer.resize(piece_size);
    }
    
    file.close();
    return ret;
}


void show_help(){
	printf("\nhTorrentCreatorCLI %s\n==========================\n-v  Show version info and exit.\n-h  Show this menu and exit.\n-i  Select input path.\n-p  Set private flag to torrent.\n-o  Select output file.\n\n",hTorrentCreatorCLI_ver.c_str());
}

void show_ver(){
	printf("\nhTorrentCreatorCLI %s\n==========================\nCoded by: hon\nLanguage: c++\n\n",hTorrentCreatorCLI_ver.c_str());
}
