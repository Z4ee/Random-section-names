#pragma once
#include <random>

namespace utils {

    std::random_device r;
    int _int(int x, int y) {
        std::default_random_engine v1(r());
        std::uniform_int_distribution<int> v2(x, y);
        return v2(v1);
    }

	bool ReadFileToMemory(const std::string& file_path, std::vector<uint8_t>* out_buffer) {
		std::ifstream file_ifstream(file_path, std::ios::binary);

		if (!file_ifstream)
			return 0;

		out_buffer->assign((std::istreambuf_iterator<char>(file_ifstream)), std::istreambuf_iterator<char>());
		file_ifstream.close();

		return 1;
	}
};