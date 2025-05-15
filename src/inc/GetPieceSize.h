#include <iostream>
#include <cstdint>

std::uint32_t GetPieceSize(uint64_t& size){
	if((size / 16384) < 0){ //16 KiB
		return 16384;
	}else if((size / 32768) < 0){ //32 KiB
		return 32768;
	}else if((size / 65536) < 0){ //64 KiB
		return 65536;
	}else if((size / 131072) < 0){ //128 KiB
		return 131072;
	}else if((size / 262144) < 0){ //256 KiB
		return 262144;
	}else if((size / 524288) < 0){ //512 KiB
		return 524288;
	}else if((size / 1048576) < 0){ //1024 KiB / 1 MiB
		return 1048576;
	}else if((size / 2097152) < 0){ //2048 KiB / 2 MiB
		return 2097152;
	}else if((size / 4194304) < 0){ //4096 KiB / 4 MiB
		return 4194304;
	}else if((size / 8388608) < 0){ //8192 KiB / 8 MiB
		return 8388608;
	}else{ //16384 KiB / 16 MiB
		return 16777216;
	}
}
