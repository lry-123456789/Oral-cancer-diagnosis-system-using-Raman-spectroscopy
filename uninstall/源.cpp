#define _CRT_SECURE_NO_WARNINGS
#include<fstream>
#include<string>
#include<Windows.h>
#include<shlwapi.h>
#include<tchar.h>
#include<locale.h>
#pragma comment(lib,"Shlwapi.lib")
using namespace std;
void remove_control();
string remove_filepath(int a);
void remove_file0(string filepath);
bool remove_file(string filepath);
wstring StringToWstring(const std::string str);
void RemoveAllFiles(wstring wstrDir);
wstring StringToWstring(const std::string str)
{// string转wstring
	unsigned len = str.size() * 2;// 预留字节数
	setlocale(LC_CTYPE, "");     //必须调用此函数
	wchar_t* p = new wchar_t[len];// 申请一段内存存放转换后的字符串
	mbstowcs(p, str.c_str(), len);// 转换
	std::wstring str1(p);
	delete[] p;// 释放申请的内存
	return str1;
}

int main() 
{
	remove_control();
	char buf[0xFF];
	HMODULE hMod = GetModuleHandleA(NULL); //获取本exe文件模块句柄
	GetModuleFileNameA(hMod, buf, 0xFF);  //根据句柄获得文件路径
	PathStripPathA(buf); //去除路径得到文件名
	fstream f;
	f.open("selfDel.bat", ios::out); //创建批处理文件
	string data = string(":startExe\r\nif not exist ") + buf + " goto done\r\ndel /f /q " + buf + "\r\ngoto startExe\r\n:done\r\ndel /f /q %0";
	f.write(data.data(), data.size()); // 写入批处理命令
	f.close();
	ShellExecuteA(NULL, "open", "selfDel.bat", NULL, NULL, SW_HIDE);//执行批处理文件
}

bool remove_file(string filepath)
{
	if (remove(filepath.c_str()) == 0)
	{
		printf("%s删除成功\n", filepath.c_str());
		return true;
	}
	else
	{
		printf("%s删除失败\n", filepath.c_str());
		return false;
	}
}

string remove_filepath(int a)
{
	string str;
	if (a == 0)
	{
		str = "Qt6Widgets.dll";
	}
	else if(a==1)
	{
		str = "Qt6Svg.dll";
	}
	else if (a == 2)
	{
		str = "Qt6Sql.dll";
	}
	else if (a == 3)
	{
		str = "Qt6Gui.dll";
	}
	else if (a == 4)
	{
		str = "Qt6Core.dll";
	}
	else if (a == 5)
	{
		str = "patient_info.db";
	}
	else if (a == 6)
	{
		str = "opengl32sw.dll";
	}
	else if (a == 7)
	{
		str = "main_1_0_0.exe";
	}
	else if (a == 8)
	{
		str = "libwinpthread-1.dll";
	}
	else if (a == 9)
	{
		str = "libstdc++-6.dll";
	}
	else if (a == 10)
	{
		str = "libgcc_s_seh-1.dll";
	}
	else if (a == 11)
	{
		str = "data.png";
	}
	else if (a == 12)
	{
		str = "D3Dcompiler_47.dll";
	}
	else if (a == 13)
	{
		str = "account.db";
	}
	else if (a == 14)
	{
		str = "translations";
	}
	else if (a == 15)
	{
		str = "styles";
	}
	else if (a == 16)
	{
		str = "sqldrivers";
	}
	else if (a == 17)
	{
		str = "python_script";
	}
	else if (a == 18)
	{
		str = "platforms";
	}
	else if (a == 19)
	{
		str = "imageformats";
	}
	else if (a == 20)
	{
		str = "iconengines";
	}
	else if (a == 21)
	{
		str = "draw_picture";
	}
	return str;
}

void remove_file0(string filepath)
{
	RemoveDirectory((LPCWSTR)(filepath.c_str()));
}

void RemoveAllFiles(wstring wstrDir)
{
	if (wstrDir.empty())
	{
		return;
	}
	HANDLE hFind;
	WIN32_FIND_DATA findData;
	wstring wstrTempDir = wstrDir + (L"\\*");;
	hFind = FindFirstFile(wstrTempDir.c_str(), &findData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}
	do
	{
		// 忽略"."和".."两个结果
		if (wcscmp(findData.cFileName, L".") == 0 || wcscmp(findData.cFileName, L"..") == 0)
		{
			continue;
		}
		wstring wstrFileName;
		wstrFileName.assign(wstrDir);
		wstrFileName.append(L"\\");
		wstrFileName.append(findData.cFileName);
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)// 是否是目录
		{
			RemoveAllFiles(wstrFileName.c_str());
		}
		else
		{
			printf("remove %s\n",wstrFileName.c_str());
			DeleteFile(wstrFileName.c_str());
		}
	} while (FindNextFile(hFind, &findData));
	FindClose(hFind);
	RemoveDirectory(wstrDir.c_str());
}

void remove_control()
{
	int a = 0;
	for (a = 0; a <= 21; a++)
	{
		remove_file(remove_filepath(a));
		RemoveAllFiles(StringToWstring(remove_filepath(a)));
	}
}