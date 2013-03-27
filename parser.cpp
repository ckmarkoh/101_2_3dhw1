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
			vector<string> vstr;
			char * str=const_cast<char*>(line.c_str());
			char*	pch = strtok (str," \t");
				while (pch != NULL)
				{
					whitespace(pch);
					string sstr(pch);
					vstr.push_back(sstr);
	//				printf ("%s\n",pch);
					pch = strtok (NULL, " ,\t");
				}
			for(size_t i=0;i<vstr.size();i++){
				//string & str=vstr[i];
				//erase_all(vstr[i], " ");
				//remove_if(vstr[i].begin(), vstr[i].end(), isspace);
				//vstr[i].erase( remove(vstr[i].begin(), vstr[i].end(), ' '), vstr[i].end() );
			}
	return vstr;
}
void Rasmgr::parser(char * filename){
	READ_STATUS rstatus=R_TYPE;
	READ_TYPE rtype=T_VERTEX;
	string line;
	ifstream myfile (filename);
	if (myfile.is_open())
	{
		while (true )
		{
			getline (myfile,line);
			vector<string> vstr;
			if(!myfile.eof()){
				vstr=parse_line(line);
			}
			else{
				break;
			}
						switch(rstatus){	
				case R_TYPE:{
					rstatus=R_COUNT;
					if(vstr[0].find("Vertices")!=string::npos){
						rtype=T_VERTEX;	
					}
					else if(vstr[0].find("Colors")!=string::npos){
						rtype=T_COLOR;
					}
					else if(vstr[0].find("Triangle_list")!=string::npos){
						rtype=T_TRIANGLE;
					}
					else{
						assert(0);
					}
				}break;
				case R_COUNT:{
					count_temp=atoi(vstr[0].c_str());
					count_list[rtype]=count_temp;
					rstatus=R_BUILD;
				}break;	
				case R_BUILD:{
					float x=atof(vstr[0].c_str());
					float y=atof(vstr[1].c_str());
					float z=atof(vstr[2].c_str());
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
		}
		myfile.close();
	}
	else{
		cout << "Unable to open file"; 
	}
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
