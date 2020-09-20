#include <iostream>
#include <map>

using namespace std;

int main(){
  uint32_t weightA, weightB, operations;
  map <uint32_t, uint32_t, greater<uint32_t>> queueA;
  map <uint32_t, uint32_t, greater<uint32_t>> queueB;

  cin >> weightA >> weightB;
  
  queueA.insert(make_pair(weightA, 0));
  queueB.insert(make_pair(weightB, 0));

  for(auto itr = queueA.begin(); itr != queueA.end(); ++itr){
    uint32_t parent = itr -> first;
    uint32_t newPosition = (itr -> second) + 1;
    if(parent % 2 == 0) queueA.insert(make_pair(parent/2, newPosition));
    if(parent % 3 == 0) queueA.insert(make_pair(parent/3, newPosition));
    if(parent % 5 == 0) queueA.insert(make_pair(parent/5, newPosition));
  }
  for(auto itr = queueB.begin(); itr != queueB.end(); ++itr){
    uint32_t parent = itr -> first;
    uint32_t newPosition = (itr -> second) + 1;
    if(parent % 2 == 0) queueB.insert(make_pair(parent/2, newPosition));
    if(parent % 3 == 0) queueB.insert(make_pair(parent/3, newPosition));
    if(parent % 5 == 0) queueB.insert(make_pair(parent/5, newPosition));
  }

  auto itrA = queueA.begin();
  auto itrB = queueB.begin();

  while (true){
    if(itrA == queueA.end() || itrB == queueB.end()){
      cout << "-1";
      return 0;
    } 
    if(itrA -> first == itrB -> first){
      operations = itrA -> second + itrB -> second;
      std::cout << unsigned(operations);
      return 0;
    }

    if(itrA -> first > itrB -> first) ++itrA;
    else ++itrB;
  }

  return 0;
}
