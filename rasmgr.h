#ifndef RASMGR_H_
#define RASMGR_H_
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<cassert>
#include<vector>
#include<string>
#include "rasterize.h"

using namespace std;

class Rasmgr{
public:
	Rasmgr(){

	count_list= new int[3];
	
	}
	enum READ_STATUS
	{
		R_TYPE=0,
		R_COUNT,
		R_BUILD,

	};
	enum READ_TYPE
	{
		T_VERTEX=0, 
		T_COLOR, 
		T_TRIANGLE,
	};
	void parser(char * filename);
	void whitespace(char str[]);
	vector<string> parse_line(string line);
private:
	int count_temp;
	int* count_list;
	vector<Vertex*> _vertex_list;
	vector<Color*> _color_list;
	vector<Triangle*> _triangle_list;
};
#endif
