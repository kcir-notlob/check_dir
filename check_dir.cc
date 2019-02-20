
#include <string>
#include <iostream>
#include <map>
#include <dirent.h>
#include <sstream>  
using namespace std;


map<string, string> _map;

string to_upper(const string& s)
{
  string u="";
  for(long i=0;i<s.length();i++){
   u+=toupper(s[i]);
  }
  return u;
}

void dump_files(const string& name){
  DIR *d;
  string upper;
  long count=0;
  long duplicates=0;
  long index=0;
  struct dirent *dir;
  d=opendir(name.c_str());
  if(d){
    while(dir=readdir(d)){
      string s=dir->d_name;
      if(s=="." || s==".."){
      }
      else{
        cout <<  s << endl;
        string key=to_upper(s);
        if(_map.find(key)!=_map.end()){
         cout << "duplicate found:" << s << endl;
         duplicates++;
         index++;
         stringstream ss;
         ss << index << "_" << s;
         
         string new_name=ss.str();
         rename(s.c_str(),new_name.c_str());
         cout << "renaming:" << s << " to:" << new_name << endl;
        }
        _map.insert(make_pair(key,s));
        count++;
      }
    }
    closedir(d);
    cout << endl;
    cout << "total files found:" << count << " duplicates found:" << duplicates << endl;
  }
}


int main(int argc,char* args[])
{
  if(argc<2){
    cout << "expected the file path as first argument" << endl;
    return 1;
  }
  string path=args[1];
  dump_files(path);

  return 0;
}
