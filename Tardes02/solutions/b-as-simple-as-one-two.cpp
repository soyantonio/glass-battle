#include <iostream>
#include <vector>

using namespace std;

int main(){
  string one = "one";
  string two = "two";
  
  uint16_t t;
  cin >> t;
  vector<string> ss(t);

  for(uint16_t i = 0; i < t; ++i){
    cin >> ss[i];
  }

  for(uint16_t i = 0; i < t; ++i){
    string &s = ss[i];

    uint32_t head_one = 0;
    uint32_t pointer_one = 0;
    uint32_t head_two = 0;
    uint32_t pointer_two = 0;
    
    vector<uint32_t> heads;
    vector<uint32_t> tails;
    vector<bool> supressed;
    
    for(uint32_t i = 0; i < s.size(); ++i){
      if(one[0] == s[i]) {
        head_one = i;
        pointer_one = 1;
      }
      if(two[0] == s[i]) {
        head_two = i;
        pointer_two = 1;
      }

      bool same_char = one[pointer_one] == s[i];
      bool second_element = i == (head_one + 1) && pointer_one == 1;
      bool third_element = i == (head_one + 2) && pointer_one == 2;

      if(same_char && second_element) pointer_one = 2;
      else if(same_char && third_element){
        heads.push_back(head_one);
        tails.push_back(i);
        supressed.push_back(false);
        pointer_one = 0;
      }

      bool same_char_ = two[pointer_two] == s[i];
      bool second_element_ = i == (head_two + 1) && pointer_two == 1;
      bool third_element_ = i == (head_two + 2) && pointer_two == 2;

      if(same_char_ && second_element_) pointer_two = 2;
      else if(same_char_ && third_element_){
        heads.push_back(head_two);
        tails.push_back(i);
        supressed.push_back(false);
        pointer_two = 0;
      }
    }

    vector<uint32_t> ith_to_remove;
    for(uint32_t i = 0; i < heads.size(); ++i){
      if(supressed[i]) continue;
      
      if(i + 1 < heads.size() && tails[i] == heads[i + 1]){
        ith_to_remove.push_back(tails[i] + 1);
        supressed[i] = true;
        supressed[i + 1] = true;
      }
      else{
        ith_to_remove.push_back(heads[i] + 2);
        supressed[i] = true;
      }
    }

    cout << ith_to_remove.size() << endl;
    for(uint32_t i = 0; i < ith_to_remove.size(); ++i){
      cout << ith_to_remove[i] << ' ';
    }
    
    cout << endl;
  }
  return 0;
}