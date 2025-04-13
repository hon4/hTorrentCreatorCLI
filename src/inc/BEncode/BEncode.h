#include <string>
#include <map>
#include <any>
#include <vector>
#include <cstdint>

//modified

class BEncode {
	public:
		std::string Encode(std::map<std::string, std::any> d) {
			return BEncode_dict(d);
		}
		
	private:
		std::string BEncode_str(std::string s) {
			return std::to_string(s.size()) + ":" + s;
		}
		
		std::string BEncode_int(int i) {
			return "i" + std::to_string(i) + "e";
		}

		std::string BEncode_int_long(long i) {
			return "i" + std::to_string(i) + "e";
		}

		std::string BEncode_int_uint32_t(std::uint32_t i) {
			return "i" + std::to_string(i) + "e";
		}
		
		std::string BEncode_dict(std::map<std::string, std::any> d) {
			std::string ret = "d";
			for (const auto& x : d) {
				ret += BEncode_str(x.first);
				if (x.second.type() == typeid(std::string)) {
					ret += BEncode_str(std::any_cast<std::string>(x.second));
				} else if (x.second.type() == typeid(std::map<std::string, std::any>)) {
					ret += BEncode_dict(std::any_cast<std::map<std::string, std::any>>(x.second));
				} else if (x.second.type() == typeid(std::vector<std::any>)) {
					ret += BEncode_list(std::any_cast<std::vector<std::any>>(x.second));
				} else if (x.second.type() == typeid(long)) {
					ret += BEncode_int_long(std::any_cast<long>(x.second));
				} else if (x.second.type() == typeid(std::uint32_t)) {
					ret += BEncode_int_long(std::any_cast<std::uint32_t>(x.second));
				} else {
					ret += BEncode_int(std::any_cast<int>(x.second));
				}
			}
			return ret + "e";
		}
		
		std::string BEncode_list(std::vector<std::any> l) {
			std::string ret = "l";
			for (auto x : l) {
				if (x.type() == typeid(std::string)) {
					ret += BEncode_str(std::any_cast<std::string>(x));
				} else if (x.type() == typeid(std::map<std::string, std::any>)) {
					ret += BEncode_dict(std::any_cast<std::map<std::string, std::any>>(x));
				} else if (x.type() == typeid(std::vector<std::any>)) {
					ret += BEncode_list(std::any_cast<std::vector<std::any>>(x));
				} else if (x.type() == typeid(long)) {
					ret += BEncode_int_long(std::any_cast<long>(x));
				} else if (x.type() == typeid(std::uint32_t)) {
					ret += BEncode_int_long(std::any_cast<std::uint32_t>(x));
				} else {
					ret += BEncode_int(std::any_cast<int>(x));
				}
			}
			return ret + "e";
		}
};
