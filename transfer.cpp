#include "rasmgr.h"
#include "matrix.h"
void Rasmgr::rotation(float i, float j, float k){

	Matrix mx(3,3);
	Matrix my(3,3);
	Matrix mz(3,3);
	
	mx[0][0]=1;
	mx[0][1]=0;
	mx[0][2]=0;
	mx[1][0]=0;
	mx[1][1]=cos(i);
	mx[1][2]=sin(i);
	mx[2][0]=0;
	mx[2][1]=-sin(i);
	mx[2][2]=cos(i);

	my[0][0]=cos(j);
	my[0][1]=0;
	my[0][2]=-sin(j);
	my[1][0]=0;
	my[1][1]=1;
	my[1][2]=0;
	my[2][0]=sin(j);
	my[2][1]=0;
	my[2][2]=cos(j);

	mz[0][0]=cos(k);
	mz[0][1]=sin(k);
	mz[0][2]=0;
	mz[1][0]=-sin(k);
	mz[1][1]=cos(k);
	mz[1][2]=0;
	mz[2][0]=0;
	mz[2][1]=0;
	mz[2][2]=1;

	for(size_t i=0;i<_vertex_list.size();i++){
			Matrix tx(3,1);
			for(size_t j=0;j<3;j++){
				tx[j][0]=_vertex_list[i]->getx(j);
			}
			Matrix tx2= ((mx*my)*mz)*tx;
			for(size_t j=0;j<3;j++){
				_vertex_list[i]->setx(j,tx2[j][0]);
			}		
		}
}

float* Rasmgr::get_min_max(){
	float* min_max = new float[6];
	for(size_t i=0;i<_vertex_list.size();i++){
		for(size_t j=0; j<3;j++){
			if(i==0){
				min_max[j]=_vertex_list[i]->getx(j);
				min_max[j+3]=_vertex_list[i]->getx(j);
			}
			else{
				float temp=_vertex_list[i]->getx(j);
				if(temp<min_max[j]){
					min_max[j]=temp;
				}
				if(temp>min_max[j+3]){
					min_max[j+3]=temp;
				}
			}
		}
	}
	return min_max;
}

void Rasmgr::normalize(){
	float * min_max=get_min_max();
	float xdist=0;
	for(size_t i=0;i<2;i++){
		float temp=min_max[i+3]-min_max[i];
		if(min_max[i+3]-min_max[i]>xdist){
			xdist=temp;
		}
	}
	float zdist=min_max[5]-min_max[2];
	for(size_t i=0;i<_vertex_list.size();i++){
		for(size_t j=0;j<2;j++){
			float temp=(IMG_SIZE-MARGIN*2-1)*(_vertex_list[i]->getx(j)-min_max[j])/xdist;
			_vertex_list[i]->setx(j,temp);
		}
		size_t j=2;

		if(zdist!=0){
			float temp=(IMG_DEPTH-1)*(_vertex_list[i]->getx(j)-min_max[j])/zdist;
			_vertex_list[i]->setx(j,temp);
		}else{
			float temp=IMG_DEPTH-1;
			_vertex_list[i]->setx(j,temp);

		}
	}
	
//	debug();
}

