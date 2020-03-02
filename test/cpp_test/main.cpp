// #include <ctime>
// #include <iostream>
// #include <boost/filesystem.hpp>
// #include <chrono>
// #include <tuple>

// std::chrono::system_clock::time_point get_tp(int year, int month, int day)
// {
// 	std::tm timeinfo = std::tm();
// 	timeinfo.tm_year = year - 1900;
// 	timeinfo.tm_mon = month - 1;
// 	timeinfo.tm_mday = day;
// 	std::time_t tt = std::mktime(&timeinfo);
// 	return std::chrono::system_clock::from_time_t(tt);
// }
// #include <fstream>
//#include <flann/flann.hpp>

#include <iostream>
#include <vector>
#include <fstream>
#include <boost/filesystem.hpp>

// namespace sc_place_recognizer
// {
// 	struct pose
// 	{
// 		float x;
// 		float y;
// 		float z;
// 		float yaw;
// 	};
// }
//
// void parse_pose(const std::string &file, std::vector<sc_place_recognizer::pose> &poses)
// {
// 	std::ifstream map_pos_ifs(file, std::ifstream::binary);
// 	if (!map_pos_ifs) {
// 		std::cout << "Key frame is empty now." << std::endl;
// 		return;
// 	}
//
// 	map_pos_ifs.seekg(0, map_pos_ifs.end);
// 	auto fp_end = map_pos_ifs.tellg();
// 	size_t keyframe_size = fp_end / (4 * sizeof(float) + sizeof(int));
// 	map_pos_ifs.seekg(0, map_pos_ifs.beg);
// 	poses.resize(keyframe_size);
// 	int loaded_cnt = 0;
// 	for (int i = 0; i < keyframe_size; ++i)
// 	{
// 		map_pos_ifs.read(reinterpret_cast<char*>(poses.data() + i), sizeof(float) * 4);
// 		int tmp_cnt = 0;
// 		map_pos_ifs.read(reinterpret_cast<char*>(&tmp_cnt), sizeof(int));
// 		if (tmp_cnt != i) break;
// 		++loaded_cnt;
// 	}
// 	poses.resize(loaded_cnt);
// 	std::cout << "load " << loaded_cnt << " key frames" << std::endl;
// 	map_pos_ifs.close();
// }

int main()
{
	// std::vector<sc_place_recognizer::pose> poses;
	// parse_pose("F:/data/gz_system/grace/loc_zsw/keyframe/map_pos.txt", poses);
	// boost::filesystem::path p("F:/workspace/SSCCE/test/cpp_test/CMakeLists.txt");
	// std::cout << boost::filesystem::last_write_time(p) << std::endl;
	std::cout << atan2(-0.0000001, -1) << std::endl;
	return 0;
}