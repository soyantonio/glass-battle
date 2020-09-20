#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

uint32_t gcd(uint32_t a, uint32_t b){
  if(a == b) return a;
  
  if(a < b) return gcd(a, b - a);
  else return gcd(a - b, b);
}

int main(){
  uint32_t n;
  
  cin >> n;
  vector<uint32_t> elements(n);
  
  uint32_t a = 1;
  uint32_t b = 1;

  for(uint32_t i = 0; i < n; ++i){
    cin >> elements[i];
    uint32_t aa = gcd(elements[i], a);
    uint32_t bb = gcd(elements[i], b);
    
    uint32_t extra_a, mod_a = a;
    uint32_t extra_b, mod_b  = b;

    if(aa == 1) extra_a = elements[i];
    else {
      extra_a = elements[i]/aa;
      mod_a = a/aa;
    }

    if(bb == 1) extra_b = elements[i];
    else {
      extra_b = elements[i]/bb;
      mod_b = b/bb;
    } 


    cout << unsigned(aa) << ' ' << unsigned(bb) << endl;
    cout << unsigned(extra_a) << ' ' << unsigned(extra_b) << endl;
    cout << unsigned(a) << ' ' << unsigned(b) << endl;
    
    if(extra_a == extra_b){
      if(mod_a < mod_b) a = extra_a;
      else b = extra_b;
    }
    else if(extra_a >= extra_b && extra_a > mod_a){
      a = extra_a;
    }
    else if(extra_b > mod_b){
      b = extra_b;
    }
    cout << unsigned(a) << ' ' << unsigned(b) << endl<< endl;
  }

  cout << unsigned(a) << endl;
  cout << unsigned(b) << endl;


  return 0;
}