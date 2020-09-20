#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main(){
  uint32_t tests;

  cin >> tests;

  vector<uint32_t> total_tables_group(tests);
  vector<uint32_t> minimum_distance_group(tests);
  vector<string> distribution_group(tests);

  for(uint32_t i = 0; i < tests; ++i){
    cin >> total_tables_group[i] >> minimum_distance_group[i];
    cin >> distribution_group[i];
  }
  


  for(uint32_t t = 0; t < tests; ++t){
    uint32_t minimum_distance = minimum_distance_group[t];
  
    int32_t last_table = -1*minimum_distance - 1;
    stack<uint32_t> available_tables;

    for(uint32_t i = 0; i < total_tables_group[t]; ++i){
      bool comply_distance = i - last_table > minimum_distance;
      
      if(distribution_group[t][i] == '0'){
        if(comply_distance){
          last_table = i;
          available_tables.push(i);
        }
      }
      else {
        if(!comply_distance && available_tables.top() == last_table){
          available_tables.pop();
        }
        last_table = i;
      }
    }

    cout << available_tables.size() << '\n';
  }

  return 0;
}
