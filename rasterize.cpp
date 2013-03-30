#include "rasterize.h"
#include "rasmgr.h"
using namespace std;

int main (int argc, char *argv[]){

	if(argc<2){
		cout<<"please enter input file name"<<endl;
	}
	else if(argc<3){
		cout<<"please enter output file name"<<endl;
	}
	else{
		int xr= (argc<4) ? 0 :atoi(argv[3]);
		int yr= (argc<5) ? 0 :atoi(argv[4]);
		int zr= (argc<6) ? 0 :atoi(argv[5]);
		bool fill = (argc<7) ? 0 : atoi(argv[6]);
		cout<<"xyzr: "<<xr<<","<<yr<<","<<zr<<","<<fill<<endl;
		Rasmgr* rasmgr= new Rasmgr();	
		
		rasmgr->_fillcolor=fill;

		rasmgr->parser(argv[1]);
		//rasmgr->debug();
		cout<<"rotation"<<endl;
		rasmgr->rotation(ARC(xr),ARC(yr),ARC(zr));

		cout<<"normalize"<<endl;
		rasmgr->normalize();

		cout<<"drawTriangle"<<endl;
		rasmgr->drawTriangle();
		

		if(fill){
	//		cout<<"bfCulling"<<endl;
	//		rasmgr->bfCulling();
			cout<<"fillTriangle"<<endl;
			rasmgr->fillTriangle();
		}
		cout<<"drawBitMap"<<endl;
		rasmgr->drawBitMap(argv[2]);
		return 0;
	}
}

