#include "rasmgr.h"
void Rasmgr::whitespace(char str[]){
    int i;
    for(i=0; str[i+1]!='\0'; i++)
        while(isspace(str[i])) {
        str[i] = str[i+1];
        i++;
    }
}
vector<string> Rasmgr::parse_line(string line){
		//	cout<<"raw string"<<endl;
			vector<string> vstr;
			//line.erase( remove(line.begin(), line.end(), ' '), line.end() );
			string  whitespace = " \t\r\n\v\f";
			line.erase(line.find_last_not_of(whitespace.c_str()) + 1);
			char * str=const_cast<char*>(line.c_str());
			char*	pch = strtok (str," \t");
				while (pch != NULL)
				{
					string sstr(pch);
					vstr.push_back(sstr);
//					printf ("%s\n",pch);
					pch = strtok (NULL, " \t");
				}
			return vstr;
}
bool Rasmgr::store_line(ifstream& myfile,queue<string>& q,size_t s){
	while(q.size()<s){
		string line;
		getline (myfile,line);
		vector<string> vstr;
		if(!myfile.eof()){
			vstr=parse_line(line);
		}
		else{
			return true;
		}
		for(size_t i=0;i<vstr.size();i++){
			q.push(vstr[i]);
		}
	}
	return false;
}
string Rasmgr::get_queue_front(queue<string>& q){
	string vstr=q.front();
	q.pop();
	return vstr;
}
void Rasmgr::parser(char * filename){
	int count_temp;
	int* count_list = new int[3];
	READ_STATUS rstatus=R_TYPE;
	READ_TYPE rtype=T_VERTEX;
	string line;
	ifstream myfile (filename);
	queue<string> rqueue;
	bool eof=false;
	if (myfile.is_open())
	{
		while (true )
		{
	
			switch(rstatus){	
				case R_TYPE:{
					eof=store_line(myfile,rqueue,1);
				}break;
				case R_COUNT:{
					eof=store_line(myfile,rqueue,1);
				}break;	
				case R_BUILD:{
					eof=store_line(myfile,rqueue,3);
				}break;
				default:{
					assert(0);
				}break;
			}
			if(!eof){
			switch(rstatus){	
				case R_TYPE:{
					rstatus=R_COUNT;
					string vstr=get_queue_front(rqueue);
					if(vstr.find("Vertices")!=string::npos){
						rtype=T_VERTEX;	
					}
					else if(vstr.find("Colors")!=string::npos){
						rtype=T_COLOR;
					}
					else if(vstr.find("Triangle_list")!=string::npos){
						rtype=T_TRIANGLE;
					}
					else{
						//cout<<vstr<<endl;
						assert(0);
					}
				}break;
				case R_COUNT:{
					string vstr=get_queue_front(rqueue);
					count_temp=atoi(vstr.c_str());
					count_list[rtype]=count_temp;
					rstatus=R_BUILD;
				}break;	
				case R_BUILD:{
					string* vstr=new string[3];
					vstr[0]=get_queue_front(rqueue);
					vstr[1]=get_queue_front(rqueue);
					vstr[2]=get_queue_front(rqueue);
					float x=atof(vstr[0].c_str());
					float y=atof(vstr[1].c_str());
					float z=atof(vstr[2].c_str());
					//cout<<"count:"<<count_temp<<endl;
					//cout<<x<<","<<y<<","<<z<<endl;
					switch(rtype){
						case T_VERTEX:{
							Vertex* temp1=new Vertex( x,y,z );
							_vertex_list.push_back(temp1);
						}break;
						case T_COLOR:{
							Color* temp2=new Color( x,y,z );
							_color_list.push_back(temp2);
						}break;
						case T_TRIANGLE:{
							assert( ((size_t)x<_vertex_list.size()) && ((size_t)y<_vertex_list.size()) && ((size_t)z<_vertex_list.size()) );
							Triangle* temp3=new Triangle(
								_vertex_list[(size_t)x],_vertex_list[(size_t)y],_vertex_list[(size_t)z],
								(size_t)x,(size_t)y,(size_t)z
							);
							_triangle_list.push_back(temp3);
						}break;
						default:{
							assert(0);
						}break;
					}
					if(!(--count_temp)){
						rstatus=R_TYPE;
					}
				}break;
				default:{
					assert(0);
				}break;
			}
			}else{
				myfile.close();
				break;
			}
		}
	}
	else{
		cout << "Unable to open file"; 
	}

}
void Rasmgr::debug(){
	if(_vertex_list.size()>0){
		cout<<"Vertices"<<endl;
		cout<<_vertex_list.size()<<endl;;
		for(size_t i=0;i<_vertex_list.size();i++){
			_vertex_list[i]->print();
		}
	}
	if(_color_list.size()>0){
		cout<<"Colors"<<endl;
		cout<<_color_list.size()<<endl;
		for(size_t i=0;i<_color_list.size();i++){
			_color_list[i]->print();	
		}
	}
	if(_triangle_list.size()>0){
		cout<<"Triangle_list"<<endl;
		cout<<_triangle_list.size()<<endl;
		for(size_t i=0;i<_triangle_list.size();i++){
			_triangle_list[i]->print();	
		}
	}
}
