
#ifndef RASTERIZE_H_
#define RASTERIZE_H_

#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<cassert>
#include<cstring>
#include<vector>
/*
#define V3_COMMAND(element, type)                      \
class element : public ResElement                       \
{                                                  \
   public:                                         \
      cmd() : V3CmdExec(type) {}                   \
      ~cmd() {}                                    \
      V3CmdExecStatus exec(const string& option);  \
      void usage() const;                          \
      void help() const;                           \
};                                                 \
*/
class Vertex;
class Triangle;
class Color;

class Vertex{
public:
//	friend class Rasmgr;
	Vertex(){}
	Vertex(float x,float y,float z){
		_x = new float[3];
		_x[0]=x;
		_x[1]=y;
		_x[2]=z;
	}
	void print(){
		printf("%f\t%f\t%f\t\n",_x[0],_x[1],_x[2]);
	
	}
	float getx(size_t i){
		return _x[i];
	}
	void setx(size_t i,float x){
		_x[i]=x;
	}
private:
	float* _x;
};

class Color{
public:
	Color(){}
	Color(float x,float y,float z){
		_x = new float[3];
		_x[0]=x;
		_x[1]=y;
		_x[2]=z;
	}
	void print(){
		printf("%f\t%f\t%f\t\n",_x[0],_x[1],_x[2]);
	}
	float getx(size_t i){
		return _x[i];
	}
	void setx(size_t i,float x){
		_x[i]=x;
	}
private:
	float* _x;
};

class Triangle{
public:
	Triangle(){}
	Triangle(Vertex* p0,Vertex* p1,Vertex* p2,size_t x0,size_t x1,size_t x2){
		_p = new Vertex*[3];
		_p[0]=p0;
		_p[1]=p1;
		_p[2]=p2;
		_i= new size_t[3];
		_i[0]=x0;
		_i[1]=x1;
		_i[2]=x2;
	}
	void print(){
		printf("%d\t%d\t%d\t\n",(int)_i[0],(int)_i[1],(int)_i[2]);
	}
	Vertex* getv(size_t i){
		return _p[i];
	}
private:
	Vertex** _p;
	size_t * _i;
};

#endif 

