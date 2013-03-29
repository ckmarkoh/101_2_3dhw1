#include "rasmgr.h"
void Rasmgr::fillTriangle(){
	for(size_t i=0;i<_triangle_list.size();i++){
		fillOneTriangle(_triangle_list[i]);
	}
}
void Rasmgr::fillOneTriangle(Triangle* t){
	sortVerticeY( t );
	float *x = new float[3];
	float *y = new float[3];
	float *z = new float[3];
	float xs1,xs2,ys,zs1,zs2;
	Vertex* c1=0;
	Vertex* c2=0;

	for(size_t i=0;i<3;i++){
		x[i]=t->getv(i)->getx(0);
		y[i]=t->getv(i)->getx(1);
		z[i]=t->getv(i)->getx(2);
	//	cout<<"i:"<<i<<endl;
	//	cout<<"x:"<<x[i]<<" y:"<<y[i]<<" z:"<<z[i]<<endl;
	}
	xs1=xs2=x[0]-1;
	ys=y[0]-1;
	zs1=zs2=z[0]-1;
	
	if( (y[0]==y[1]) && (y[0]==y[2]) ){
		return;
	}
	else{
		while (true){
			if(ys>y[1]){
				float yd=y[0]-ys;
				float yd1=y[0]-y[1];
				float yd2=y[0]-y[2];
				xs1=x[0]-(x[0]-x[1])*(yd/yd1);	
				zs1=z[0]-(z[0]-z[1])*(yd/yd1);
				xs2=x[0]-(x[0]-x[2])*(yd/yd2);
				zs2=z[0]-(z[0]-z[2])*(yd/yd2);
			}
			else if((ys<=y[1])&&(ys>y[2])){
				float yd=y[1]-ys;
				float yd0=y[0]-ys;
				float yd1=y[1]-y[2];
				float yd2=y[0]-y[2];
				xs1=x[1]-(x[1]-x[2])*(yd/yd1);	
				zs1=z[1]-(z[1]-z[2])*(yd/yd1);
				xs2=x[0]-(x[0]-x[2])*(yd0/yd2);
				zs2=z[0]-(z[0]-z[2])*(yd0/yd2);
			}
			else{
				break;
			}
		//	cout<<"ys:"<<ys<<endl;
		//	cout<<"xs1:"<<xs1<<" zs1:"<<zs1<<endl;
		//	cout<<"xs2:"<<xs2<<" zs2:"<<zs2<<endl;
			c1= new Vertex(xs1,ys,zs1);
			c2= new Vertex(xs2,ys,zs2);
			drawLine(c1,c2);
			ys=ys-1;
		}
	}
}
void Rasmgr::sortVerticeY(Triangle*t ){
   
	for (int i = 2; i > 0; --i){
		for (int j = 0; j < i; ++j){
			if ( t->getv(j)->getx(1) <  t->getv(j+1)->getx(1) ) {
				t->swap(j, j + 1);
			}
		}
	}
}

