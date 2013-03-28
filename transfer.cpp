#include "rasmgr.h"
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
			float temp=(IMG_SIZE-1)*(_vertex_list[i]->getx(j)-min_max[j])/xdist;
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

