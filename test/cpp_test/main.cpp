#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
//#include "zsw_clock.h"

class TestC
{
public:
	TestC(std::unique_ptr<int> a): ma_(std::move(a))
	{

	}
private:
	std::unique_ptr<int> ma_;
};


int main(int argc, char *argv[])
{
	//if (argc != 2) {
	//	std::cout << "usage test_io [file_path]" << std::endl;
	//	return 0;
	//}
	//zsw::common::Clock clock;
	//FILE * file = fopen(argv[1], "rb");
	//fseek(file, 0, SEEK_END);
	//int size = ftell(file);
	//std::vector<char> data(size);
	//fread(data.data(), sizeof(char), size, file);
	//fclose(file);
	//std::cout << "read time cost:" << clock.totalTime() << std::endl;
	std::unique_ptr<int> a(new int);
	TestC tc(std::move(a));
	return 0;
}