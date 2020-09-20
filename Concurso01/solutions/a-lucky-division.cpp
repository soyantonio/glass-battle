#include <iostream>

using namespace std;

// As the possible numbers are small, only fixed numbers are considered
// The alg is 2^(digits) + ... + 2^1
const uint16_t lucky_numbers_to_1000[] = {
  4, 7, 44, 47, 74, 77, 444, 447, 474, 477, 744, 747, 774, 777
};


int main(){
  uint16_t number_to_evaluate;
  cin >> number_to_evaluate;
  
  for(uint16_t lucky_number:lucky_numbers_to_1000){
    if(lucky_number > number_to_evaluate) break;
    if(number_to_evaluate % lucky_number == 0){
      cout << "YES";
      return 0;
    }
  }

  cout << "NO";
  return 0;
}

