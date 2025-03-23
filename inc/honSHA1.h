//honSHA1 function | Last Update: 23-03-2025
#include <iostream>
#include <openssl/sha.h>

std::string honSHA1(std::string s){
	unsigned char str[s.size()+1];
	std::memcpy(str,s.c_str(),s.size()+1);
	unsigned char hash[SHA_DIGEST_LENGTH];
	SHA1(reinterpret_cast<const unsigned char*>(s.c_str()),s.size(),hash);
	return std::string(reinterpret_cast<const char*>(hash), SHA_DIGEST_LENGTH);
}
