#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main(){
  uint32_t n;
  
  cin >> n;
  uint32_t elements[n];
  uint32_t prime_limit = 0;

  for(uint32_t i = 0; i < n; ++i){
    cin >> elements[i];
    prime_limit = max(prime_limit, elements[i]);
  }

  prime_limit = min(sqrt(prime_limit), sqrt(1e5))  + 1;
  bool non_primes[prime_limit] = {false};
  vector<uint32_t> primes;

  for(uint32_t i = 2;i <= prime_limit; ++i){
    if(non_primes[i]) continue;
    primes.push_back(i);

    for(uint32_t j = 2; j*i <= prime_limit; ++j){
      non_primes[j*i] = true;
    }
  }

  uint32_t factors[primes.size()] = {0};
  uint32_t max_index = 0;

  for(uint32_t i = 0; i < n; ++i){
    if(elements[i] == 1) continue;
    
    uint32_t helper = elements[i];
    for(uint32_t j = 0; j < primes.size(); ++j){
      
      uint32_t factor_counter = 0;
      while (helper % primes[j] == 0){
        ++factor_counter;
        helper /= primes[j];
      }

      if(factor_counter > 0){
        max_index = max(max_index, j);
        cout << unsigned(primes[j]) << endl;
        // Match with prime numbers
        factors[j] = max(factors[j], factor_counter);
      }
      
      if(helper == 1) break;
    }
  }

  cout << endl;
  uint32_t lcm = 1;

  for(uint32_t i = 0; i <= max_index; ++i){
    if(factors[i] == 0) continue;
    cout << unsigned(factors[i]) << endl;
    lcm *= pow(primes[i], factors[i]);
  }

  cout << unsigned(lcm) << ' ' << unsigned(max_index);

  return 0;
}