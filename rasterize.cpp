#include "rasterize.h"
#include "rasmgr.h"
using namespace std;

int main (int argc, char *argv[]){
	Rasmgr* rasmgr= new Rasmgr();	
	if(argc>=3){
		string temp(argv[2]);
	}
	rasmgr->parser(argv[1]);
	rasmgr->normalize();
	rasmgr->debug();
	rasmgr->drawTriangle();
	rasmgr->drawBitMap();
	return 0;
}

