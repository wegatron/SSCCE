#include <iostream>
//#include <Eigen/Dense>
#include <vector>
#include <memory>
//#include <boost/filesystem.hpp>
#include <thread>
#include <fstream>

int main()
{
	int offset[75];
	std::ifstream ifs("f:/tmp_zsw/zsw_offset.txt");
	int val[2];
	ifs >> val[0];
	for (int i = 1; i < 75; ++i)
	{
		ifs >> val[1];
		offset[i] = val[1] - val[0];
		if (offset[i] < 0) offset[i] += 36000;
		std::cout << offset[i] << " ";
		val[0] = val[1];
	}

	//while (!ifs.eof())
	//{
	//	ifs >> val[0];
	//	for (int i = 1; i < 75; ++i)
	//	{
	//		ifs >> val[1];
	//		if (offset[i] != val[1] - val[0])
	//		{
	//			std::cout << "diff" << std::endl;
	//		}
	//		val[0] = val[1];
	//	}
	//	std::cout << "fine!!!" << std::endl;
	//}
	return 0;
}
