#include <iostream>
#include <string>
#include <map>
#include <any>
#include <vector>

#include "inc/honSHA1.h"
#include "inc/BEncode/BEncode.h"
#include "inc/isDIR.h"
using namespace std;

string hTorrentCreatorCLI_ver = "0.0.1";

void show_help();
void show_ver();
int mkTorrent();

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

	mkTorrent();
	
	return 0;
}

int mkTorrent(){
	map<string, any> dict;
	return 0;
}

void show_help(){
	printf("\nhTorrentCreatorCLI %s\n==========================\n-v  Show version info and exit.\n-h  Show this menu and exit.\n-i  Select input path.\n\n",hTorrentCreatorCLI_ver.c_str());
}

void show_ver(){
	printf("\nhTorrentCreatorCLI %s\n==========================\nCoded by: hon\nLanguage: c++\n\n",hTorrentCreatorCLI_ver.c_str());
}
