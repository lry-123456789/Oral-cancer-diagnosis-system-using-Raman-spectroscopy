// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"
#include <string.h>
#include <string>

#ifndef EXPORT_DLL
#define EXPORT_DLL __declspec(dllexport)
#else
#define EXPORT_DLL __declspec(dllexport)
#endif

extern "C" EXPORT_DLL double* resnet_model(std::string filepath);
extern "C" EXPORT_DLL double* inception_model(std::string filepath);
extern "C" EXPORT_DLL double* mobilenet_model(std::string filepath);
extern "C" EXPORT_DLL double* transformer_model(std::string filepath);
extern "C" EXPORT_DLL double* vgg_model(std::string filepath);
extern "C" EXPORT_DLL bool draw_picture(std::string input_filepath, std::string output_filepath);
#endif //PCH_H
