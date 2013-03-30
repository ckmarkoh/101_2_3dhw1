#ifndef RASMGR_H_
#define RASMGR_H_
#define IMG_SIZE 512
#define IMG_DEPTH 256
#define COFFSET 20
#define PI 3.14159265
#define MARGIN 2
#define ARC(x) (x*PI/180)
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<cassert>
#include<vector>
#include<string>
#include <queue>
#include <math.h>
#include "rasterize.h"

using namespace std;

class Rasmgr{
public:
	struct BMPColor 
	{
		float r;
		float g;
		float b;
		float z;
	};
	Rasmgr(){
		_bitmap= new BMPColor*[IMG_SIZE];
		for(size_t i=0;i<IMG_SIZE;i++){
			_bitmap[i]=new BMPColor[IMG_SIZE];
			for(size_t j=0;j<IMG_SIZE;j++){
				_bitmap[i][j].r=1;
				_bitmap[i][j].g=1;
				_bitmap[i][j].b=1;
				_bitmap[i][j].z=0;
			}
		}
		_triangle_current=0;
	}
	~Rasmgr(){
		for(size_t i=0;i<IMG_SIZE;i++){
				delete _bitmap[i];
		}
		delete _bitmap;
		delete _triangle_current;
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
	bool store_line(ifstream& myfile,queue<string>& q,size_t s);
	string get_queue_front(queue<string>& q);
	float* get_min_max();
	void rotation(float i, float j, float k);
	void normalize();
	
	void drawLine(Vertex* v1, Vertex* v2);
	void drawTriangle();
	float get_abs(float x);
//	float get_max(float x,float y);
	void drawPoint(float xi,float yi,float zi);
	void drawBitMap();
	void bfCulling();
	void fillTriangle();
	void fillOneTriangle(Triangle* t);
	void sortVerticeY(Triangle*t );
	bool _fillcolor;
private:
	Triangle* _triangle_current;
	vector<Vertex*> _vertex_list;
	vector<Color*> _color_list;
	vector<Triangle*> _triangle_list;
	BMPColor** _bitmap;
};
#endif
