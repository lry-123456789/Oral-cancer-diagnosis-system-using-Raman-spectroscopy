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
{// stringתwstring
	unsigned len = str.size() * 2;// Ԥ���ֽ���
	setlocale(LC_CTYPE, "");     //������ô˺���
	wchar_t* p = new wchar_t[len];// ����һ���ڴ���ת������ַ���
	mbstowcs(p, str.c_str(), len);// ת��
	std::wstring str1(p);
	delete[] p;// �ͷ�������ڴ�
	return str1;
}

int main() 
{
	remove_control();
	char buf[0xFF];
	HMODULE hMod = GetModuleHandleA(NULL); //��ȡ��exe�ļ�ģ����
	GetModuleFileNameA(hMod, buf, 0xFF);  //���ݾ������ļ�·��
	PathStripPathA(buf); //ȥ��·���õ��ļ���
	fstream f;
	f.open("selfDel.bat", ios::out); //�����������ļ�
	string data = string(":startExe\r\nif not exist ") + buf + " goto done\r\ndel /f /q " + buf + "\r\ngoto startExe\r\n:done\r\ndel /f /q %0";
	f.write(data.data(), data.size()); // д������������
	f.close();
	ShellExecuteA(NULL, "open", "selfDel.bat", NULL, NULL, SW_HIDE);//ִ���������ļ�
}

bool remove_file(string filepath)
{
	if (remove(filepath.c_str()) == 0)
	{
		printf("%sɾ���ɹ�\n", filepath.c_str());
		return true;
	}
	else
	{
		printf("%sɾ��ʧ��\n", filepath.c_str());
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
		// ����"."��".."�������
		if (wcscmp(findData.cFileName, L".") == 0 || wcscmp(findData.cFileName, L"..") == 0)
		{
			continue;
		}
		wstring wstrFileName;
		wstrFileName.assign(wstrDir);
		wstrFileName.append(L"\\");
		wstrFileName.append(findData.cFileName);
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)// �Ƿ���Ŀ¼
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