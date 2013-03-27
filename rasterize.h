
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
	Vertex(){}
	Vertex(float x,float y,float z):_x(x),_y(y),_z(z){ 
	}
	void print(){
		printf("%d\t%d\t%d\t\n",(int)_x,(int)_y,(int)_z);
	}
	void print_f(){
		printf("%f %f %f \n",_x,_y,_z);
	}
private:
	float _x,_y,_z;
};

class Color{
public:
	Color(){}
	Color(float x,float y,float z):_x(x),_y(y),_z(z){
	}
	void print(){
		printf("%d\t%d\t%d\t\n",(int)_x,(int)_y,(int)_z);
	}
	void print_f(){
		printf("%f %f %f \n",_x,_y,_z);
	}
private:
	float _x,_y,_z;
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
private:
	Vertex** _p;
	size_t * _i;
};
#endif 

