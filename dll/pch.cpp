﻿// pch.cpp: 与预编译标头对应的源文件

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
			data_x[14] = 57.444;
			data_x[15] = 63.6;
			data_x[16] = 69.75;
			data_x[17] = 75.893;
			data_x[18] = 82.029;
			data_x[19] = 88.159;
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
			data_x[38] = 203.341;
			data_x[39] = 209.337;
			data_x[40] = 215.326;
			data_x[41] = 221.309;
			data_x[42] = 227.285;
			data_x[43] = 233.254;
			data_x[44] = 239.218;
			data_x[45] = 245.174;
			data_x[46] = 251.124;
			data_x[47] = 257.068;
			data_x[48] = 263.005;
			data_x[49] = 268.935;
			data_x[50] = 274.86;
			data_x[51] = 280.777;
			data_x[52] = 286.689;
			data_x[53] = 292.593;
			data_x[54] = 298.492;
			data_x[55] = 304.384;
			data_x[56] = 310.27;
			data_x[57] = 316.149;
			data_x[58] = 322.022;
			data_x[59] = 327.888;
			data_x[60] = 333.748;
			data_x[61] = 339.602;
			data_x[62] = 345.45;
			data_x[63] = 351.291;
			data_x[64] = 357.125;
			data_x[65] = 362.954;
			data_x[66] = 368.776;
			data_x[67] = 374.592;
			data_x[68] = 380.402;
			data_x[69] = 386.205;
			data_x[70] = 392.002;
			data_x[71] = 397.793;
			data_x[72] = 403.578;
			data_x[73] = 409.356;
			data_x[74] = 415.128;
			data_x[75] = 420.894;
			data_x[76] = 426.654;
			data_x[77] = 432.408;
			data_x[78] = 438.155;
			data_x[79] = 443.896;
			data_x[80] = 449.631;
			data_x[81] = 455.36;
			data_x[82] = 461.083;
			data_x[83] = 466.8;
			data_x[84] = 472.51;
			data_x[85] = 478.215;
			data_x[86] = 483.913;
			data_x[87] = 489.605;
			data_x[88] = 495.292;
			data_x[89] = 500.972;
			data_x[90] = 506.646;
			data_x[91] = 512.314;
			data_x[92] = 517.976;
			data_x[93] = 523.631;
			data_x[94] = 529.281;
			data_x[95] = 534.925;
			data_x[96] = 540.563;
			data_x[97] = 546.195;
			data_x[98] = 551.821;
			data_x[99] = 557.441;
			data_x[100] = 563.055;
			data_x[101] = 568.663;
			data_x[102] = 574.265;
			data_x[103] = 579.861;
			data_x[104] = 585.451;
			data_x[105] = 591.035;
			data_x[106] = 596.613;
			data_x[107] = 602.186;
			data_x[108] = 607.752;
			data_x[109] = 613.313;
			data_x[110] = 618.868;
			data_x[111] = 624.417;
			data_x[112] = 629.96;
			data_x[113] = 635.497;
			data_x[114] = 641.028;
			data_x[115] = 646.554;
			data_x[116] = 652.074;
			data_x[117] = 657.587;
			data_x[118] = 663.096;
			data_x[119] = 668.598;
			data_x[120] = 674.094;
			data_x[121] = 679.585;
			data_x[122] = 685.07;
			data_x[123] = 690.549;
			data_x[124] = 696.023;
			data_x[125] = 701.49;
			data_x[126] = 706.952;
			data_x[127] = 712.409;
			data_x[128] = 717.859;
			data_x[129] = 723.304;
			data_x[130] = 728.743;
			data_x[131] = 734.177;
			data_x[132] = 739.605;
			data_x[133] = 745.027;
			data_x[134] = 750.443;
			data_x[135] = 755.854;
			data_x[136] = 761.259;
			data_x[137] = 766.659;
			data_x[138] = 772.053;
			data_x[139] = 777.441;
			data_x[140] = 782.824;
			data_x[141] = 788.201;
			data_x[142] = 793.572;
			data_x[143] = 798.938;
			data_x[144] = 804.298;
			data_x[145] = 809.653;
			data_x[146] = 815.002;
			data_x[147] = 820.346;
			data_x[148] = 825.684;
			data_x[149] = 831.017;
			data_x[150] = 836.344;
			data_x[151] = 841.665;
			data_x[152] = 846.981;
			data_x[153] = 852.292;
			data_x[154] = 857.597;
			data_x[155] = 862.896;
			data_x[156] = 868.191;
			data_x[157] = 873.479;
			data_x[158] = 878.762;
			data_x[159] = 884.04;
			data_x[160] = 889.312;
			data_x[161] = 894.579;
			data_x[162] = 899.841;
			data_x[163] = 905.097;
			data_x[164] = 910.347;
			data_x[165] = 915.592;
			data_x[166] = 920.832;
			data_x[167] = 926.067;
			data_x[168] = 931.296;
			data_x[169] = 936.519;
			data_x[170] = 941.738;
			data_x[171] = 946.951;
			data_x[172] = 952.158;
			data_x[173] = 957.361;
			data_x[174] = 962.558;
			data_x[175] = 967.749;
			data_x[176] = 972.936;
			data_x[177] = 978.117;
			data_x[178] = 983.292;
			data_x[179] = 988.463;
			data_x[180] = 993.628;
			data_x[181] = 998.788;
			data_x[182] = 1003.943;
			data_x[183] = 1009.092;
			data_x[184] = 1014.236;
			data_x[185] = 1019.375;
			data_x[186] = 1024.509;
			data_x[187] = 1029.637;
			data_x[188] = 1034.76;
			data_x[189] = 1039.878;
			data_x[190] = 1044.991;
			data_x[191] = 1050.099;
			data_x[192] = 1055.201;
			data_x[193] = 1060.299;
			data_x[194] = 1065.391;
			data_x[195] = 1070.478;
			data_x[196] = 1075.56;
			data_x[197] = 1080.636;
			data_x[198] = 1085.708;
			data_x[199] = 1090.774;
			data_x[200] = 1095.835;
			data_x[201] = 1100.891;
			data_x[202] = 1105.942;
			data_x[203] = 1110.988;
			data_x[204] = 1116.029;
			data_x[205] = 1121.065;
			data_x[206] = 1126.096;
			data_x[207] = 1131.121;
			data_x[208] = 1136.142;
			data_x[209] = 1141.157;
			data_x[210] = 1146.168;
			data_x[211] = 1151.173;
			data_x[212] = 1156.174;
			data_x[213] = 1161.169;
			data_x[214] = 1166.159;
			data_x[215] = 1171.145;
			data_x[216] = 1176.125;
			data_x[217] = 1181.1;
			data_x[218] = 1186.071;
			data_x[219] = 1191.036;
			data_x[220] = 1195.996;
			data_x[221] = 1200.952;
			data_x[222] = 1205.902;
			data_x[223] = 1210.848;
			data_x[224] = 1215.788;
			data_x[225] = 1220.724;
			data_x[226] = 1225.654;
			data_x[227] = 1230.58;
			data_x[228] = 1235.501;
			data_x[229] = 1240.417;
			data_x[230] = 1245.328;
			data_x[231] = 1250.234;
			data_x[232] = 1255.135;
			data_x[233] = 1260.032;
			data_x[234] = 1264.923;
			data_x[235] = 1269.81;
			data_x[236] = 1274.692;
			data_x[237] = 1279.569;
			data_x[238] = 1284.441;
			data_x[239] = 1289.308;
			data_x[240] = 1294.17;
			data_x[241] = 1299.028;
			data_x[242] = 1303.881;
			data_x[243] = 1308.729;
			data_x[244] = 1313.572;
			data_x[245] = 1318.41;
			data_x[246] = 1323.244;
			data_x[247] = 1328.073;
			data_x[248] = 1332.897;
			data_x[249] = 1337.716;
			data_x[250] = 1342.531;
			data_x[251] = 1347.34;
			data_x[252] = 1352.145;
			data_x[253] = 1356.946;
			data_x[254] = 1361.741;
			data_x[255] = 1366.532;
			data_x[256] = 1371.318;
			data_x[257] = 1376.099;
			data_x[258] = 1380.876;
			data_x[259] = 1385.648;
			data_x[260] = 1390.415;
			data_x[261] = 1395.178;
			data_x[262] = 1399.936;
			data_x[263] = 1404.689;
			data_x[264] = 1409.438;
			data_x[265] = 1414.182;
			data_x[266] = 1418.921;
			data_x[267] = 1423.655;
			data_x[268] = 1428.385;
			data_x[269] = 1433.111;
			data_x[270] = 1437.832;
			data_x[271] = 1442.548;
			data_x[272] = 1447.259;
			data_x[273] = 1451.966;
			data_x[274] = 1456.668;
			data_x[275] = 1461.366;
			data_x[276] = 1466.059;
			data_x[277] = 1470.748;
			data_x[278] = 1475.432;
			data_x[279] = 1480.111;
			data_x[280] = 1484.786;
			data_x[281] = 1489.456;
			data_x[282] = 1494.122;
			data_x[283] = 1498.783;
			data_x[284] = 1503.44;
			data_x[285] = 1508.092;
			data_x[286] = 1512.74;
			data_x[287] = 1517.383;
			data_x[288] = 1522.021;
			data_x[289] = 1526.656;
			data_x[290] = 1531.285;
			data_x[291] = 1535.91;
			data_x[292] = 1540.531;
			data_x[293] = 1545.147;
			data_x[294] = 1549.759;
			data_x[295] = 1554.366;
			data_x[296] = 1558.969;
			data_x[297] = 1563.567;
			data_x[298] = 1568.161;
			data_x[299] = 1572.751;
			data_x[300] = 1577.336;
			data_x[301] = 1581.916;
			data_x[302] = 1586.492;
			data_x[303] = 1591.064;
			data_x[304] = 1595.632;
			data_x[305] = 1600.195;
			data_x[306] = 1604.753;
			data_x[307] = 1609.307;
			data_x[308] = 1613.857;
			data_x[309] = 1618.402;
			data_x[310] = 1622.944;
			data_x[311] = 1627.48;
			data_x[312] = 1632.013;
			data_x[313] = 1636.541;
			data_x[314] = 1641.064;
			data_x[315] = 1645.584;
			data_x[316] = 1650.099;
			data_x[317] = 1654.609;
			data_x[318] = 1659.115;
			data_x[319] = 1663.618;
			data_x[320] = 1668.115;
			data_x[321] = 1672.609;
			data_x[322] = 1677.098;
			data_x[323] = 1681.583;
			data_x[324] = 1686.063;
			data_x[325] = 1690.539;
			data_x[326] = 1695.011;
			data_x[327] = 1699.479;
			data_x[328] = 1703.943;
			data_x[329] = 1708.402;
			data_x[330] = 1712.857;
			data_x[331] = 1717.307;
			data_x[332] = 1721.754;
			data_x[333] = 1726.196;
			data_x[334] = 1730.634;
			data_x[335] = 1735.068;
			data_x[336] = 1739.498;
			data_x[337] = 1743.923;
			data_x[338] = 1748.344;
			data_x[339] = 1752.761;
			data_x[340] = 1757.174;
			data_x[341] = 1761.583;
			data_x[342] = 1765.987;
			data_x[343] = 1770.387;
			data_x[344] = 1774.783;
			data_x[345] = 1779.175;
			data_x[346] = 1783.563;
			data_x[347] = 1787.947;
			data_x[348] = 1792.326;
			data_x[349] = 1796.702;
			data_x[350] = 1801.073;
			data_x[351] = 1805.44;
			data_x[352] = 1809.803;
			data_x[353] = 1814.162;
			data_x[354] = 1818.517;
			data_x[355] = 1822.867;
			data_x[356] = 1827.214;
			data_x[357] = 1831.556;
			data_x[358] = 1835.895;
			data_x[359] = 1840.229;
			data_x[360] = 1844.559;
			data_x[361] = 1848.886;
			data_x[362] = 1853.208;
			data_x[363] = 1857.526;
			data_x[364] = 1861.84;
			data_x[365] = 1866.15;
			data_x[366] = 1870.456;
			data_x[367] = 1874.757;
			data_x[368] = 1879.055;
			data_x[369] = 1883.349;
			data_x[370] = 1887.639;
			data_x[371] = 1891.925;
			data_x[372] = 1896.206;
			data_x[373] = 1900.484;
			data_x[374] = 1904.758;
			data_x[375] = 1909.028;
			data_x[376] = 1913.294;
			data_x[377] = 1917.555;
			data_x[378] = 1921.813;
			data_x[379] = 1926.067;
			data_x[380] = 1930.317;
			data_x[381] = 1934.563;
			data_x[382] = 1938.805;
			data_x[383] = 1943.043;
			data_x[384] = 1947.277;
			data_x[385] = 1951.507;
			data_x[386] = 1955.733;
			data_x[387] = 1959.956;
			data_x[388] = 1964.174;
			data_x[389] = 1968.389;
			data_x[390] = 1972.599;
			data_x[391] = 1976.806;
			data_x[392] = 1981.009;
			data_x[393] = 1985.207;
			data_x[394] = 1989.402;
			data_x[395] = 1993.593;
			data_x[396] = 1997.781;
			data_x[397] = 2001.964;
			data_x[398] = 2006.143;
			data_x[399] = 2010.319;
			data_x[400] = 2014.491;
			data_x[401] = 2018.659;
			data_x[402] = 2022.823;
			data_x[403] = 2026.983;
			data_x[404] = 2031.139;
			data_x[405] = 2035.292;
			data_x[406] = 2039.44;
			data_x[407] = 2043.585;
			data_x[408] = 2047.726;
			data_x[409] = 2051.864;
			data_x[410] = 2055.997;
			data_x[411] = 2060.127;
			data_x[412] = 2064.253;
			data_x[413] = 2068.375;
			data_x[414] = 2072.493;
			data_x[415] = 2076.607;
			data_x[416] = 2080.718;
			data_x[417] = 2084.825;
			data_x[418] = 2088.928;
			data_x[419] = 2093.028;
			data_x[420] = 2097.123;
			data_x[421] = 2101.215;
			data_x[422] = 2105.303;
			data_x[423] = 2109.388;
			data_x[424] = 2113.468;
			data_x[425] = 2117.545;
			data_x[426] = 2121.619;
			data_x[427] = 2125.688;
			data_x[428] = 2129.754;
			data_x[429] = 2133.816;
			data_x[430] = 2137.874;
			data_x[431] = 2141.929;
			data_x[432] = 2145.98;
			data_x[433] = 2150.027;
			data_x[434] = 2154.071;
			data_x[435] = 2158.111;
			data_x[436] = 2162.147;
			data_x[437] = 2166.18;
			data_x[438] = 2170.208;
			data_x[439] = 2174.234;
			data_x[440] = 2178.255;
			data_x[441] = 2182.273;
			data_x[442] = 2186.287;
			data_x[443] = 2190.298;
			data_x[444] = 2194.305;
			data_x[445] = 2198.308;
			data_x[446] = 2202.308;
			data_x[447] = 2206.304;
			data_x[448] = 2210.297;
			data_x[449] = 2214.286;
			data_x[450] = 2218.271;
			data_x[451] = 2222.253;
			data_x[452] = 2226.231;
			data_x[453] = 2230.205;
			data_x[454] = 2234.176;
			data_x[455] = 2238.143;
			data_x[456] = 2242.107;
			data_x[457] = 2246.067;
			data_x[458] = 2250.024;
			data_x[459] = 2253.977;
			data_x[460] = 2257.926;
			data_x[461] = 2261.872;
			data_x[462] = 2265.814;
			data_x[463] = 2269.753;
			data_x[464] = 2273.689;
			data_x[465] = 2277.62;
			data_x[466] = 2281.548;
			data_x[467] = 2285.473;
			data_x[468] = 2289.394;
			data_x[469] = 2293.312;
			data_x[470] = 2297.226;
			data_x[471] = 2301.136;
			data_x[472] = 2305.044;
			data_x[473] = 2308.947;
			data_x[474] = 2312.847;
			data_x[475] = 2316.744;
			data_x[476] = 2320.637;
			data_x[477] = 2324.526;
			data_x[478] = 2328.413;
			data_x[479] = 2332.295;
			data_x[480] = 2336.174;
			data_x[481] = 2340.05;
			data_x[482] = 2343.922;
			data_x[483] = 2347.791;
			data_x[484] = 2351.657;
			data_x[485] = 2355.518;
			data_x[486] = 2359.377;
			data_x[487] = 2363.232;
			data_x[488] = 2367.084;
			data_x[489] = 2370.932;
			data_x[490] = 2374.776;
			data_x[491] = 2378.618;
			data_x[492] = 2382.456;
			data_x[493] = 2386.29;
			data_x[494] = 2390.121;
			data_x[495] = 2393.949;
			data_x[496] = 2397.773;
			data_x[497] = 2401.594;
			data_x[498] = 2405.412;
			data_x[499] = 2409.226;
			data_x[500] = 2413.036;
			data_x[501] = 2416.844;
			data_x[502] = 2420.648;
			data_x[503] = 2424.448;
			data_x[504] = 2428.246;
			data_x[505] = 2432.04;
			data_x[506] = 2435.83;
			data_x[507] = 2439.617;
			data_x[508] = 2443.401;
			data_x[509] = 2447.182;
			data_x[510] = 2450.959;
			data_x[511] = 2454.733;
			data_x[512] = 2458.503;
			data_x[513] = 2462.27;
			data_x[514] = 2466.034;
			data_x[515] = 2469.795;
			data_x[516] = 2473.552;
			data_x[517] = 2477.306;
			data_x[518] = 2481.057;
			data_x[519] = 2484.804;
			data_x[520] = 2488.548;
			data_x[521] = 2492.289;
			data_x[522] = 2496.026;
			data_x[523] = 2499.76;
			data_x[524] = 2503.491;
			data_x[525] = 2507.219;
			data_x[526] = 2510.943;
			data_x[527] = 2514.664;
			data_x[528] = 2518.382;
			data_x[529] = 2522.097;
			data_x[530] = 2525.808;
			data_x[531] = 2529.516;
			data_x[532] = 2533.221;
			data_x[533] = 2536.923;
			data_x[534] = 2540.621;
			data_x[535] = 2544.316;
			data_x[536] = 2548.008;
			data_x[537] = 2551.697;
			data_x[538] = 2555.382;
			data_x[539] = 2559.064;
			data_x[540] = 2562.743;
			data_x[541] = 2566.419;
			data_x[542] = 2570.092;
			data_x[543] = 2573.761;
			data_x[544] = 2577.427;
			data_x[545] = 2581.09;
			data_x[546] = 2584.75;
			data_x[547] = 2588.407;
			data_x[548] = 2592.06;
			data_x[549] = 2595.711;
			data_x[550] = 2599.358;
			data_x[551] = 2603.002;
			data_x[552] = 2606.642;
			data_x[553] = 2610.28;
			data_x[554] = 2613.915;
			data_x[555] = 2617.546;
			data_x[556] = 2621.174;
			data_x[557] = 2624.799;
			data_x[558] = 2628.421;
			data_x[559] = 2632.04;
			data_x[560] = 2635.655;
			data_x[561] = 2639.268;
			data_x[562] = 2642.877;
			data_x[563] = 2646.484;
			data_x[564] = 2650.087;
			data_x[565] = 2653.687;
			data_x[566] = 2657.284;
			data_x[567] = 2660.877;
			data_x[568] = 2664.468;
			data_x[569] = 2668.056;
			data_x[570] = 2671.64;
			data_x[571] = 2675.222;
			data_x[572] = 2678.8;
			data_x[573] = 2682.375;
			data_x[574] = 2685.948;
			data_x[575] = 2689.517;
			data_x[576] = 2693.083;
			data_x[577] = 2696.646;
			data_x[578] = 2700.206;
			data_x[579] = 2703.763;
			data_x[580] = 2707.316;
			data_x[581] = 2710.867;
			data_x[582] = 2714.415;
			data_x[583] = 2717.96;
			data_x[584] = 2721.501;
			data_x[585] = 2725.04;
			data_x[586] = 2728.575;
			data_x[587] = 2732.108;
			data_x[588] = 2735.638;
			data_x[589] = 2739.164;
			data_x[590] = 2742.688;
			data_x[591] = 2746.208;
			data_x[592] = 2749.726;
			data_x[593] = 2753.24;
			data_x[594] = 2756.751;
			data_x[595] = 2760.26;
			data_x[596] = 2763.765;
			data_x[597] = 2767.268;
			data_x[598] = 2770.767;
			data_x[599] = 2774.264;
			data_x[600] = 2777.757;
			data_x[601] = 2781.248;
			data_x[602] = 2784.736;
			data_x[603] = 2788.22;
			data_x[604] = 2791.702;
			data_x[605] = 2795.181;
			data_x[606] = 2798.656;
			data_x[607] = 2802.129;
			data_x[608] = 2805.599;
			data_x[609] = 2809.066;
			data_x[610] = 2812.53;
			data_x[611] = 2815.991;
			data_x[612] = 2819.449;
			data_x[613] = 2822.904;
			data_x[614] = 2826.356;
			data_x[615] = 2829.806;
			data_x[616] = 2833.252;
			data_x[617] = 2836.695;
			data_x[618] = 2840.136;
			data_x[619] = 2843.574;
			data_x[620] = 2847.008;
			data_x[621] = 2850.44;
			data_x[622] = 2853.869;
			data_x[623] = 2857.295;
			data_x[624] = 2860.718;
			data_x[625] = 2864.138;
			data_x[626] = 2867.556;
			data_x[627] = 2870.97;
			data_x[628] = 2874.382;
			data_x[629] = 2877.791;
			data_x[630] = 2881.197;
			data_x[631] = 2884.6;
			data_x[632] = 2888;
			data_x[633] = 2891.397;
			data_x[634] = 2894.791;
			data_x[635] = 2898.183;
			data_x[636] = 2901.572;
			data_x[637] = 2904.957;
			data_x[638] = 2908.34;
			data_x[639] = 2911.721;
			data_x[640] = 2915.098;
			data_x[641] = 2918.473;
			data_x[642] = 2921.844;
			data_x[643] = 2925.213;
			data_x[644] = 2928.579;
			data_x[645] = 2931.942;
			data_x[646] = 2935.303;
			data_x[647] = 2938.66;
			data_x[648] = 2942.015;
			data_x[649] = 2945.367;
			data_x[650] = 2948.716;
			data_x[651] = 2952.063;
			data_x[652] = 2955.406;
			data_x[653] = 2958.747;
			data_x[654] = 2962.085;
			data_x[655] = 2965.42;
			data_x[656] = 2968.753;
			data_x[657] = 2972.082;
			data_x[658] = 2975.409;
			data_x[659] = 2978.733;
			data_x[660] = 2982.055;
			data_x[661] = 2985.373;
			data_x[662] = 2988.689;
			data_x[663] = 2992.002;
			data_x[664] = 2995.312;
			data_x[665] = 2998.62;
			data_x[666] = 3001.925;
			data_x[667] = 3005.227;
			data_x[668] = 3008.526;
			data_x[669] = 3011.823;
			data_x[670] = 3015.117;
			data_x[671] = 3018.408;
			data_x[672] = 3021.696;
			data_x[673] = 3024.982;
			data_x[674] = 3028.265;
			data_x[675] = 3031.545;
			data_x[676] = 3034.822;
			data_x[677] = 3038.097;
			data_x[678] = 3041.369;
			data_x[679] = 3044.639;
			data_x[680] = 3047.905;
			data_x[681] = 3051.169;
			data_x[682] = 3054.431;
			data_x[683] = 3057.689;
			data_x[684] = 3060.945;
			data_x[685] = 3064.198;
			data_x[686] = 3067.449;
			data_x[687] = 3070.697;
			data_x[688] = 3073.942;
			data_x[689] = 3077.184;
			data_x[690] = 3080.424;
			data_x[691] = 3083.661;
			data_x[692] = 3086.896;
			data_x[693] = 3090.128;
			data_x[694] = 3093.357;
			data_x[695] = 3096.583;
			data_x[696] = 3099.807;
			data_x[697] = 3103.029;
			data_x[698] = 3106.247;
			data_x[699] = 3109.463;
			data_x[700] = 3112.676;
			data_x[701] = 3115.887;
			data_x[702] = 3119.095;
			data_x[703] = 3122.3;
			data_x[704] = 3125.503;
			data_x[705] = 3128.703;
			data_x[706] = 3131.901;
			data_x[707] = 3135.096;
			data_x[708] = 3138.288;
			data_x[709] = 3141.478;
			data_x[710] = 3144.665;
			data_x[711] = 3147.849;
			data_x[712] = 3151.031;
			data_x[713] = 3154.211;
			data_x[714] = 3157.387;
			data_x[715] = 3160.561;
			data_x[716] = 3163.733;
			data_x[717] = 3166.902;
			data_x[718] = 3170.068;
			data_x[719] = 3173.232;
			data_x[720] = 3176.393;
			data_x[721] = 3179.552;
			data_x[722] = 3182.708;
			data_x[723] = 3185.861;
			data_x[724] = 3189.012;
			data_x[725] = 3192.161;
			data_x[726] = 3195.306;
			data_x[727] = 3198.45;
			data_x[728] = 3201.59;
			data_x[729] = 3204.728;
			data_x[730] = 3207.864;
			data_x[731] = 3210.997;
			data_x[732] = 3214.127;
			data_x[733] = 3217.255;
			data_x[734] = 3220.381;
			data_x[735] = 3223.504;
			data_x[736] = 3226.624;
			data_x[737] = 3229.742;
			data_x[738] = 3232.857;
			data_x[739] = 3235.97;
			data_x[740] = 3239.08;
			data_x[741] = 3242.188;
			data_x[742] = 3245.293;
			data_x[743] = 3248.396;
			data_x[744] = 3251.496;
			data_x[745] = 3254.594;
			data_x[746] = 3257.689;
			data_x[747] = 3260.782;
			data_x[748] = 3263.872;
			data_x[749] = 3266.96;
			data_x[750] = 3270.045;
			data_x[751] = 3273.128;
			data_x[752] = 3276.209;
			data_x[753] = 3279.286;
			data_x[754] = 3282.362;
			data_x[755] = 3285.435;
			data_x[756] = 3288.505;
			data_x[757] = 3291.573;
			data_x[758] = 3294.638;
			data_x[759] = 3297.701;
			data_x[760] = 3300.762;
			data_x[761] = 3303.82;
			data_x[762] = 3306.876;
			data_x[763] = 3309.929;
			data_x[764] = 3312.98;
			data_x[765] = 3316.028;
			data_x[766] = 3319.074;
			data_x[767] = 3322.117;
			data_x[768] = 3325.158;
			data_x[769] = 3328.197;
			data_x[770] = 3331.233;
			data_x[771] = 3334.267;
			data_x[772] = 3337.298;
			data_x[773] = 3340.327;
			data_x[774] = 3343.353;
			data_x[775] = 3346.377;
			data_x[776] = 3349.399;
			data_x[777] = 3352.418;
			data_x[778] = 3355.435;
			data_x[779] = 3358.449;
			data_x[780] = 3361.461;
			data_x[781] = 3364.471;
			data_x[782] = 3367.478;
			data_x[783] = 3370.482;
			data_x[784] = 3373.485;
			data_x[785] = 3376.485;
			data_x[786] = 3379.482;
			data_x[787] = 3382.478;
			data_x[788] = 3385.471;
			data_x[789] = 3388.461;
			data_x[790] = 3391.449;
			data_x[791] = 3394.435;
			data_x[792] = 3397.418;
			data_x[793] = 3400.399;
			data_x[794] = 3403.378;
			data_x[795] = 3406.354;
			data_x[796] = 3409.328;
			data_x[797] = 3412.299;
			data_x[798] = 3415.269;
			data_x[799] = 3418.235;
			data_x[800] = 3421.2;
			data_x[801] = 3424.162;
			data_x[802] = 3427.122;
			data_x[803] = 3430.079;
			data_x[804] = 3433.034;
			data_x[805] = 3435.987;
			data_x[806] = 3438.938;
			data_x[807] = 3441.886;
			data_x[808] = 3444.832;
			data_x[809] = 3447.775;
			data_x[810] = 3450.716;
			data_x[811] = 3453.655;
			data_x[812] = 3456.592;
			data_x[813] = 3459.526;
			data_x[814] = 3462.458;
			data_x[815] = 3465.387;
			data_x[816] = 3468.314;
			data_x[817] = 3471.239;
			data_x[818] = 3474.162;
			data_x[819] = 3477.082;
			data_x[820] = 3480.001;
			data_x[821] = 3482.916;
			data_x[822] = 3485.83;
			data_x[823] = 3488.741;
			data_x[824] = 3491.65;
			data_x[825] = 3494.557;
			data_x[826] = 3497.461;
			data_x[827] = 3500.363;
			data_x[828] = 3503.263;
			data_x[829] = 3506.16;
			data_x[830] = 3509.056;
			data_x[831] = 3511.949;
			data_x[832] = 3514.839;
			data_x[833] = 3517.728;
			data_x[834] = 3520.614;
			data_x[835] = 3523.498;
			data_x[836] = 3526.38;
			data_x[837] = 3529.259;
			data_x[838] = 3532.136;
			data_x[839] = 3535.011;
			data_x[840] = 3537.884;
			data_x[841] = 3540.754;
			data_x[842] = 3543.623;
			data_x[843] = 3546.489;
			data_x[844] = 3549.352;
			data_x[845] = 3552.214;
			data_x[846] = 3555.073;
			data_x[847] = 3557.93;
			data_x[848] = 3560.785;
			data_x[849] = 3563.638;
			data_x[850] = 3566.488;
			data_x[851] = 3569.336;
			data_x[852] = 3572.182;
			data_x[853] = 3575.026;
			data_x[854] = 3577.867;
			data_x[855] = 3580.707;
			data_x[856] = 3583.544;
			data_x[857] = 3586.379;
			data_x[858] = 3589.212;
			data_x[859] = 3592.042;
			data_x[860] = 3594.87;
			data_x[861] = 3597.697;
			data_x[862] = 3600.521;
			data_x[863] = 3603.342;
			data_x[864] = 3606.162;
			data_x[865] = 3608.979;
			data_x[866] = 3611.795;
			data_x[867] = 3614.608;
			data_x[868] = 3617.419;
			data_x[869] = 3620.227;
			data_x[870] = 3623.034;
			data_x[871] = 3625.838;
			data_x[872] = 3628.64;
			data_x[873] = 3631.44;
			data_x[874] = 3634.238;
			data_x[875] = 3637.034;
			data_x[876] = 3639.827;
			data_x[877] = 3642.619;
			data_x[878] = 3645.408;
			data_x[879] = 3648.195;
			data_x[880] = 3650.98;
			data_x[881] = 3653.763;
			data_x[882] = 3656.544;
			data_x[883] = 3659.322;
			data_x[884] = 3662.099;
			data_x[885] = 3664.873;
			data_x[886] = 3667.645;
			data_x[887] = 3670.415;
			data_x[888] = 3673.183;
			data_x[889] = 3675.949;
			data_x[890] = 3678.712;
			data_x[891] = 3681.474;
			data_x[892] = 3684.233;
			data_x[893] = 3686.99;
			data_x[894] = 3689.746;
			data_x[895] = 3692.499;
			data_x[896] = 3695.25;
			data_x[897] = 3697.998;
			data_x[898] = 3700.745;
			data_x[899] = 3703.49;
			data_x[900] = 3706.232;
			data_x[901] = 3708.973;
			data_x[902] = 3711.711;
			data_x[903] = 3714.447;
			data_x[904] = 3717.181;
			data_x[905] = 3719.913;
			data_x[906] = 3722.643;
			data_x[907] = 3725.371;
			data_x[908] = 3728.097;
			data_x[909] = 3730.821;
			data_x[910] = 3733.543;
			data_x[911] = 3736.262;
			data_x[912] = 3738.98;
			data_x[913] = 3741.695;
			data_x[914] = 3744.408;
			data_x[915] = 3747.12;
			data_x[916] = 3749.829;
			data_x[917] = 3752.536;
			data_x[918] = 3755.241;
			data_x[919] = 3757.944;
			data_x[920] = 3760.645;
			data_x[921] = 3763.344;
			data_x[922] = 3766.041;
			data_x[923] = 3768.736;
			data_x[924] = 3771.429;
			data_x[925] = 3774.12;
			data_x[926] = 3776.808;
			data_x[927] = 3779.495;
			data_x[928] = 3782.18;
			data_x[929] = 3784.862;
			data_x[930] = 3787.543;
			data_x[931] = 3790.222;
			data_x[932] = 3792.898;
			data_x[933] = 3795.573;
			data_x[934] = 3798.245;
			data_x[935] = 3800.916;
			data_x[936] = 3803.584;
			data_x[937] = 3806.251;
			data_x[938] = 3808.915;
			data_x[939] = 3811.577;
			data_x[940] = 3814.238;
			data_x[941] = 3816.896;
			data_x[942] = 3819.553;
			data_x[943] = 3822.207;
			data_x[944] = 3824.859;
			data_x[945] = 3827.51;
			data_x[946] = 3830.158;
			data_x[947] = 3832.804;
			data_x[948] = 3835.449;
			data_x[949] = 3838.091;
			data_x[950] = 3840.732;
			data_x[951] = 3843.37;
			data_x[952] = 3846.007;
			data_x[953] = 3848.641;
			data_x[954] = 3851.274;
			data_x[955] = 3853.904;
			data_x[956] = 3856.533;
			data_x[957] = 3859.159;
			data_x[958] = 3861.784;
			data_x[959] = 3864.406;
			data_x[960] = 3867.027;
			data_x[961] = 3869.646;
			data_x[962] = 3872.262;
			data_x[963] = 3874.877;
			data_x[964] = 3877.49;
			data_x[965] = 3880.101;
			data_x[966] = 3882.71;
			data_x[967] = 3885.317;
			data_x[968] = 3887.922;
			data_x[969] = 3890.525;
			data_x[970] = 3893.126;
			data_x[971] = 3895.725;
			data_x[972] = 3898.322;
			data_x[973] = 3900.917;
			data_x[974] = 3903.511;
			data_x[975] = 3906.102;
			data_x[976] = 3908.692;
			data_x[977] = 3911.279;
			data_x[978] = 3913.865;
			data_x[979] = 3916.448;
			data_x[980] = 3919.03;
			data_x[981] = 3921.61;
			data_x[982] = 3924.188;
			data_x[983] = 3926.764;
			data_x[984] = 3929.338;
			data_x[985] = 3931.91;
			data_x[986] = 3934.48;
			data_x[987] = 3937.049;
			data_x[988] = 3939.615;
			data_x[989] = 3942.18;
			data_x[990] = 3944.742;
			data_x[991] = 3947.303;
			data_x[992] = 3949.862;
			data_x[993] = 3952.419;
			data_x[994] = 3954.974;
			data_x[995] = 3957.527;
			data_x[996] = 3960.078;
			data_x[997] = 3962.627;
			data_x[998] = 3965.175;
			data_x[999] = 3967.72;
			data_x[1000] = 3970.264;
			data_x[1001] = 3972.806;
			data_x[1002] = 3975.346;
			data_x[1003] = 3977.884;
			data_x[1004] = 3980.42;
			data_x[1005] = 3982.954;
			data_x[1006] = 3985.487;
			data_x[1007] = 3988.017;
			data_x[1008] = 3990.546;
			data_x[1009] = 3993.073;
			data_x[1010] = 3995.598;
			data_x[1011] = 3998.121;
			data_x[1012] = 4000.642;
			data_x[1013] = 4003.161;
			data_x[1014] = 4005.679;
			data_x[1015] = 4008.194;
			data_x[1016] = 4010.708;
			data_x[1017] = 4013.22;
			data_x[1018] = 4015.73;
			data_x[1019] = 4018.238;
			data_x[1020] = 4020.745;
			data_x[1021] = 4023.249;
			data_x[1022] = 4025.752;
			data_x[1023] = 4028.253;
			data_x[1024] = 4030.752;
			data_x[1025] = 4033.249;
			data_x[1026] = 4035.745;
			data_x[1027] = 4038.238;
			data_x[1028] = 4040.73;
			data_x[1029] = 4043.22;
			data_x[1030] = 4045.708;
			data_x[1031] = 4048.194;
			data_x[1032] = 4050.678;
			data_x[1033] = 4053.161;
			data_x[1034] = 4055.642;
			data_x[1035] = 4058.121;
			data_x[1036] = 4060.598;
			data_x[1037] = 4063.073;
			data_x[1038] = 4065.547;
			data_x[1039] = 4068.018;
			data_x[1040] = 4070.488;
			data_x[1041] = 4072.956;
			data_x[1042] = 4075.423;
			data_x[1043] = 4077.887;

		}
	}
}
