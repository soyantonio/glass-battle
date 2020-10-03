#include <iostream>
#include <string>

using namespace std;

int main(){
  string players;
  cin >> players;

  uint8_t counter[2];
  for(char player:players){
    const uint8_t team = player - '0';
    counter[1-team] = 0;
    counter[team] += 1;

    if(counter[team] >= 7){
      cout << "YES";
      return 0;
    }
  }

  cout << "NO";
  return 0;
}