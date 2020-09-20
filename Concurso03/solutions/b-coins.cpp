#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

template <typename T>
void set_primes(vector<T> &primes, const T &n){
  T limit = sqrt(n) + 1;
  vector<bool> visited(limit, false);

  for(T i = 2; i < limit; ++i){
    if(visited[i]) continue;
    primes.push_back(i);
    
    for(T j = 2; j*i <= limit; ++j){
      visited[j*i] = true;
    }
  }
}

typedef uint32_t prime_t;

int main(){  
  uint32_t n, coin;
  vector<prime_t> primes;
  
  set_primes<prime_t>(primes, 1e6);
  cin >> n;
  coin = n;

  while (coin != 1){
    cout << coin << ' ';
    
    uint32_t i = 0;
    for(; i < primes.size(); ++i){
      if(primes[i] > coin) break;
      if(coin%primes[i] == 0){
        coin /= primes[i];
        break;
      }
    }

    if(i == primes.size()){
      coin = 1;
    }
  }
  
  cout << 1;
  return 0;
}