#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
  uint32_t a, b, c, position = 1;
  unordered_set <uint32_t> known_numberators;
  
  cin >> a;
  cin >> b;
  cin >> c;

  known_numberators.insert(a);
  uint32_t numerator = a * 10;

  while(true) {
    uint32_t residue = numerator % b;
    uint32_t digit = numerator / b;

    if(digit == c){
      cout << position;
      return 0;
    }

    if(known_numberators.find(residue) != known_numberators.end()){
      cout << "-1";
      return 0;  
    }

    known_numberators.insert(residue);
    numerator = residue * 10;
    ++position;
  }

  return 0;
}