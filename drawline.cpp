#include "rasmgr.h"
#include "rasterize.h"
float Rasmgr::get_abs(float x){
	if(x>=0){
		return x;
	}
	else{
		return -x;
	}
}
void Rasmgr::drawTriangle(){
	for(size_t i=0;i<_triangle_list.size();i++){
		//cout<<i<<endl;
		drawLine(_triangle_list[i]->getv(0),_triangle_list[i]->getv(1));
		drawLine(_triangle_list[i]->getv(1),_triangle_list[i]->getv(2));
		drawLine(_triangle_list[i]->getv(2),_triangle_list[i]->getv(0));
	}
}
void Rasmgr::drawPoint(float xi,float yi,float zi){
	unsigned tempz=(unsigned)( ( (IMG_DEPTH-1)*COFFSET+zi*(100-COFFSET)   ) /100);
	int x=(int)xi;
	int y=(int)yi;
	//cout<<tempz<<" "<<xi<<" "<<yi<<endl;
	//cout<<tempz<<" "<<x<<" "<<y<<endl;
	//cout<<tempz<<" "<<(size_t)x<<" "<<(size_t)y<<endl;
	//assert( (xi>=0)&&(yi>=0)&&(zi>=0) );
	if(tempz > _bitmap[(size_t)get_abs(x)+MARGIN][(size_t)get_abs(y)+MARGIN]){
		_bitmap[(size_t)get_abs(x)+MARGIN][(size_t)get_abs(y)+MARGIN]=tempz;
	}
}
void Rasmgr::drawLine(Vertex* v1, Vertex* v2){
	float xd=v2->getx(0)-v1->getx(0);
	float yd=v2->getx(1)-v1->getx(1);
	float zd=v2->getx(2)-v1->getx(2);
	float xi=v1->getx(0);
	float yi=v1->getx(1);
	float zi=v1->getx(2);
	/*
	if(xd==0){
		while(  (  (yd>0) && ( yi < v2->getx(1)v) ) ||  (  (yd<0) && ( yi > v2->getx(1)v) ) ) {
			assert( (xi>=0)&&(yi>=0)&&(zi>=0) );
			yi+=yi+1;
			zi+=zi+(zd/yd);
			_bitmap[(size_t)xi][(size_t)yi]=128+(zi/2);
		}
	}
	else{
	*/
	//cout<<"v2 getx: "<<v2->getx(0)<<","<<v2->getx(1)<<","<<v2->getx(2)<<endl;
	//cout<<"v1 getx: "<<v1->getx(0)<<","<<v1->getx(1)<<","<<v1->getx(2)<<endl;
	//cout<<"xd: "<<xd<<","<<yd<<","<<zd<<endl;
	//cout<<"xi: "<<xi<<","<<yi<<","<<zi<<endl;
		if( get_abs(yd) > get_abs(xd) ){
			while(  (  (yd>0) && ( yi <= v2->getx(1)) ) ||  (  (yd<0) && ( yi >= v2->getx(1)) ) ) {
				drawPoint(xi,yi,zi);
				float sign=(get_abs(yd)/yd);
				xi=xi+(xd/yd)*sign;
				yi=yi+sign;
				zi=zi+(zd/yd)*sign;
			}
		}
		else if( get_abs(xd) > get_abs(yd) ){
			while(  (  (xd>0) && ( xi <= v2->getx(0)) ) ||  (  (xd<0) && ( xi >= v2->getx(0)) ) ) {
				drawPoint(xi,yi,zi);
				float sign=(get_abs(xd)/xd);
				xi=xi+sign;
				yi=yi+(yd/xd)*sign;
				zi=zi+(zd/xd)*sign;
			}
		}
		else if( get_abs(xd)==get_abs(yd) ){
			if(xd!=0){
				while(  (  (xd>0) && ( xi <= v2->getx(0)) ) ||  (  (xd<0) && ( xi >= v2->getx(0)) ) ) {
					drawPoint(xi,yi,zi);
					float sign=(get_abs(xd)/xd);
					xi=xi+sign;
					yi=yi+(yd/xd)*sign;
					zi=zi+(zd/xd)*sign;
				}
			}
			else{
					drawPoint(xi,yi,zi);
					drawPoint(xi,yi,zi+zd);
			}
		}
		else{
			assert(0);
		}
}
void Rasmgr::drawBitMap(){
ofstream fout("img.out");
	fout<<"P3"<<endl<<IMG_SIZE<<" "<<IMG_SIZE<<endl<<IMG_DEPTH<<endl;
	for(size_t i=0;i<IMG_SIZE;i++){
		for(size_t j=0;j<IMG_SIZE;j++){
			fout<<_bitmap[i][j]<<" "<<_bitmap[i][j]<<" "<<_bitmap[i][j]<<"   ";			
		}
		fout<<endl;
	}
fout.close();   // 關閉檔案
}
