#ifndef RASMGR_H_
#define RASMGR_H_
#define IMG_SIZE 512
#define IMG_DEPTH 256
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
		_bitmap= new unsigned*[IMG_SIZE];
		for(size_t i=0;i<IMG_SIZE;i++){
			_bitmap[i]=new unsigned[IMG_SIZE];
			for(size_t j=0;j<IMG_SIZE;j++){
				_bitmap[i][j]=0;
			}
		}
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

	void debug();
	void parser(char * filename);
	void whitespace(char str[]);
	vector<string> parse_line(string line);
	float* get_min_max();
	void normalize();
	
	void drawLine(Vertex* v1, Vertex* v2);
	void drawTriangle();
	float get_abs(float x);
//	float get_max(float x,float y);
	void drawPoint(float xi,float yi,float zi);
	void drawBitMap();	
private:
	vector<Vertex*> _vertex_list;
	vector<Color*> _color_list;
	vector<Triangle*> _triangle_list;
	unsigned** _bitmap;
};
#endif
