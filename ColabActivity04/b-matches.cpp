#include <iostream>
#include <map>

using namespace std;

int main(){
  uint32_t n, containers;
  cin >> n >> containers;
  
  map<uint32_t, uint32_t, greater<uint32_t>> object;
  uint32_t matchebox, matches;

  for(uint32_t i = 0;  i< containers; ++i){
    cin >> matchebox >> matches;
    object[matches] += matchebox;
  }

  uint32_t reward = 0;
  for(auto i:object){
    uint32_t chosen = min(n, i.second);
    reward += chosen*i.first;
    n -= chosen;
    if(n == 0) break;
  }

  cout << reward;
  return  0;
}
