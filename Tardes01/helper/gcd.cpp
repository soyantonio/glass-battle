#include <iostream>

using namespace std;

uint32_t gcd(uint32_t a, uint32_t b){
  if(a == b) return a;
  
  if(a < b) return gcd(a, b - a);
  else return gcd(a - b, b);
}

int main(){
  uint32_t a, b;
  cin >> a >> b;
  cout << unsigned(gcd(a, b));
}