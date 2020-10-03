#include <iostream>
#include <string.h>
 
using namespace std;
 
int main2() {
	string dub;
	int inte=1;
	cin>>dub;
	for(int i=0;i<dub.size();i++){
    if(dub[i]=='W'&& dub[i+1]=='U' && dub[i+2]=='B'){
      i+=2;

      if(inte==0) cout<<" ";
      continue;
    }
    else {
      inte=0;
      cout<<dub[i];
    }   
	}
	return 0;
}