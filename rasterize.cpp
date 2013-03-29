#include "rasterize.h"
#include "rasmgr.h"
using namespace std;

int main (int argc, char *argv[]){
	Rasmgr* rasmgr= new Rasmgr();	
	
	rasmgr->parser(argv[1]);
	//rasmgr->debug();
	
	rasmgr->rotation(ARC(atoi(argv[2])),ARC(atoi(argv[3])),ARC(atoi(argv[4])));
	rasmgr->normalize();
	rasmgr->drawTriangle();
	rasmgr->drawBitMap();
	return 0;
}

