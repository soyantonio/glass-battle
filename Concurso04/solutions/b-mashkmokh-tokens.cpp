#include <iostream>

using namespace std;

uint64_t extra_tokens(const uint64_t &tokens, const uint64_t &a, const uint64_t &b){
  return (tokens*a%b)/a;
}

int main(){
  uint64_t days, a, b, tokens;
  cin >> days >> a >> b;

  for(uint64_t day = 0; day < days; ++day){
    cin >> tokens;
    cout << extra_tokens(tokens, a, b) << ' ';
  }
  return 0;
}
