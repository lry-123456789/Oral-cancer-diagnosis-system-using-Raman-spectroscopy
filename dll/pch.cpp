// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<cstdio>
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
using namespace std;


EXPORT_DLL double* resnet_model(std::string filepath)
{
	return nullptr;
}

EXPORT_DLL double* inception_model(std::string filepath)
{
	return nullptr;
}

EXPORT_DLL double* mobilenet_model(std::string filepath)
{
	return nullptr;
}

EXPORT_DLL double* transformer_model(std::string filepath)
{
	return nullptr;
}

EXPORT_DLL double* vgg_model(std::string filepath)
{
	return nullptr;
}

EXPORT_DLL bool draw_picture(std::string input_filepath, std::string output_filepath)
{
	FILE* f1 = fopen(input_filepath.c_str(), "rb");
	if (f1 == NULL)
	{
		//无法打开文件（只读模式）,文件不存在
		std::cerr << "failed to open the file:" << input_filepath.c_str() << std::endl;
		//返回错误(操作未完成)
		return false;
	}
	else
	{
		//可以打开文件
		//释放文件指针
		free(f1);
		std::cout << "can able to open the file:" << input_filepath.c_str() << std::endl;
		//下面开始读取文件信息
		FILE* f2 = fopen(input_filepath.c_str(), "rb");
		if (f2 == NULL)
		{
			//系统故障，无法在打开文件成功后释放指针后重新打开文件
			std::cerr << "failed to open the file:" << input_filepath.c_str() << std::endl;
			return false;
		}
		else
		{
			//成功打开文件，可以进行下一步操作
			free(f2);
			std::ifstream file0(input_filepath.c_str(), std::ios::in);
			std::string linestr;
			std::vector <std::vector<std::string>> strArray;
			while (getline(file0, linestr))
			{
				std::stringstream ss(linestr);
				std::string str;
				std::vector<std::string> lineArray;
				//按照都好将数据分开
				while (getline(ss, str, ','))
				{
					lineArray.push_back(str);
				}
				strArray.push_back(lineArray);
			}
			double data_y[1044];
			//数据读取完成，现在是将数据转换成double类型数据
			for (int i = 0; i < 1044; i++)
			{
				data_y[i] = std::stod(strArray[i][0]);
			}
			//数据准备完成
			//下面开始准备横坐标数据
			double data_x[1024];
			//下面为光谱横坐标信息
			data_x[0] = -29.472;
			data_x[1] = -23.219;
			data_x[2] = -16.972;
			data_x[3] = -10.733;
			data_x[4] = -4.5;
			data_x[5] = 1.725;
			data_x[6] = 7.944;
			data_x[7] = 14.155;
			data_x[8] = 20.36;
			data_x[9] = 26.558;
			data_x[10] = 32.749;
			data_x[11] = 38.933;
			data_x[12] = 45.11;
			data_x[13] = 51.28;
			data_x[14] = 37.444;
			data_x[15] = 63.6;
			data_x[16] = 69.75;
			data_x[17] = 75.893;
			data_x[18] = 82.029;
			data_x[19] = 88.195;
			data_x[20] = 94.281;
			data_x[21] = 100.397;
			data_x[22] = 106.506;
			data_x[23] = 112.609;
			data_x[24] = 118.704;
			data_x[25] = 124.793;
			data_x[26] = 130.875;
			data_x[27] = 136.951;
			data_x[28] = 143.019;
			data_x[29] = 149.081;
			data_x[30] = 155.137;
			data_x[31] = 161.185;
			data_x[32] = 167.228;
			data_x[33] = 173.263;
			data_x[34] = 179.292;
			data_x[35] = 185.314;
			data_x[36] = 191.33;
			data_x[37] = 197.339;
		}
	}
}
