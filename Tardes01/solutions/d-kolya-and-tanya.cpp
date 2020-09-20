#include <iostream>
#include <math.h>

using namespace std;
const uint64_t mod = 1e9 + 7;

uint64_t fast_power(uint64_t base, uint64_t n){
  if(n == 0) return 1;
  if(n == 1) return base;

  uint64_t half = fast_power(base, n/2);
  uint64_t result = (half*half)%mod;

  if(n%2 == 0) 
    return result;
  else
    return (result*base)%mod;
}


int main(){
  uint64_t n, combinations, resultA, resultB;


  cin >> n;

  resultA = fast_power(3, 3*n);
  resultB = mod - fast_power(7, n);
  combinations = (resultB + resultA)%mod;
  
  cout << unsigned(combinations);

  return 0;
}