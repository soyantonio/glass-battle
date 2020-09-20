#include <iostream>
#include <vector>

using namespace std;

int main(){
  uint16_t n;
  cin >> n;
  vector<uint16_t> who_give_to_person(n);

  for(uint16_t giver = 0; giver < n; ++giver){
    uint16_t receiver;

    cin >> receiver;
    who_give_to_person[receiver - 1] = giver + 1;
  }

  for(uint16_t giver = 0; giver < n; ++giver){
    cout << who_give_to_person[giver] << ' ';
  }

  return 0;
}
