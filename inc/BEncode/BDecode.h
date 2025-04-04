#include <string>
#include <map>
#include <any>
#include <vector>
#include <cctype> //for isdigit

class BDecode {
	public:
		std::map<std::string, std::any> Decode(std::string s) {
			unsigned int i = 0;
			return BDecode_dict(s, i);
		}
	
	private:
		std::map<std::string, std::any> BDecode_dict(std::string s, unsigned int &i) {
			std::map<std::string, std::any> ret;
			i += 1; //skp 'd'
			while (s[i] != 'e') {
				std::string key = BDecode_str(s, i);
				if (isdigit(s[i])) {
					ret[key] = BDecode_str(s, i);
				} else if (s[i] == 'i') {
					ret[key] = BDecode_int(s, i);
				} else if (s[i] == 'd') {
					ret[key] = BDecode_dict(s, i);
				} else if (s[i] == 'l') {
					ret[key] = BDecode_list(s, i);
				}
			}
			i += 1; //skp 'e'
			return ret;
		}
		
		std::string BDecode_str(std::string s, unsigned int &i) {
			std::string lenstr;
			while (isdigit(s[i])) {
				lenstr += s[i];
				i += 1;
			}
			i += 1; //skp ':'
			unsigned int len = std::stoul(lenstr);
			std::string ret;
			unsigned int ito = i + len;
			while (i < ito) {
				ret += s[i];
				i += 1;
			}
			return ret;
		}
		
		long BDecode_int(std::string s, unsigned int &i) {
			i += 1; //skp 'i'
			std::string retstr;
			while (s[i] != 'e') {
				retstr += s[i];
				i += 1;
			}
			i += 1; //skp 'e'
			return std::stol(retstr);
		}
		
		std::vector<std::any> BDecode_list(std::string s, unsigned int &i) {
			std::vector<std::any> ret;
			i += 1; //skp 'l'
			while (s[i] != 'e') {
				if (isdigit(s[i])) {
					ret.push_back(BDecode_str(s, i));
				} else if (s[i] == 'i') {
					ret.push_back(BDecode_int(s, i));
				} else if (s[i] == 'd') {
					ret.push_back(BDecode_dict(s, i));
				} else if (s[i] == 'l') {
					ret.push_back(BDecode_list(s, i));
				}
			}
			i += 1; //skp 'e'
			return ret;
		}
};
