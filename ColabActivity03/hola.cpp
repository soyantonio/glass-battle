#include <iostream>
#include <vector>

using namespace std;

int main() {
  uint16_t nsoldier;
  
  cin >> nsoldier;
  vector<uint16_t> heights(nsoldier);

  uint16_t max = 0;
  uint16_t index_max = 0;

  uint16_t min = 100;
  uint16_t index_min = 0;
  uint16_t steps = 0;

  for(uint16_t i = 0; i < nsoldier; ++i){
    cin >> heights[i];
    
    // 1 4  7 80 80 {1}
    if (heights[i] <= min){
      //if (index_min )
      index_min = i;
      min = heights[i];
      
    }

    // 1 4  7 {80} 80
    if (heights[i] > max){
      index_max = i;
      max = heights[i];
    }
  }
  
  
  steps = index_max + (nsoldier - 1 - index_min);
  if(index_max > index_min){
    steps -= 1;
  }

  cout << steps;
  return 0;
}
