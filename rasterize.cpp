#include "rasterize.h"
#include "rasmgr.h"
using namespace std;

int main (int argc, char *argv[]){
	int xr= (argc<5) ? 0 :atoi(argv[2]);
	int yr= (argc<5) ? 0 :atoi(argv[3]);
	int zr= (argc<5) ? 0 :atoi(argv[4]);
	bool fill = (argc<6) ? 0 : atoi(argv[5]);
	cout<<"xyzr: "<<xr<<","<<yr<<","<<zr<<","<<fill<<endl;
	Rasmgr* rasmgr= new Rasmgr();	
	
	rasmgr->parser(argv[1]);

	//rasmgr->debug();
	cout<<"rotation"<<endl;
	rasmgr->rotation(ARC(xr),ARC(yr),ARC(zr));

	cout<<"normalize"<<endl;
	rasmgr->normalize();

	cout<<"drawTriangle"<<endl;
	rasmgr->drawTriangle();
	if(fill){
		cout<<"fillTriangle"<<endl;
		rasmgr->fillTriangle();
	}
	cout<<"drawBitMap"<<endl;
	rasmgr->drawBitMap();
	return 0;
}

