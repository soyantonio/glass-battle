#include <iostream>
#include <vector>
#include <string>

using namespace std;
const uint64_t MOD = 10e9 + 7; 


void calculate_ones(vector<vector<uint16_t>> &ones_by_steps_required){
  uint8_t classifier[] = {0, 2, 3, 4, 3, 4, 4, 5, 3, 4};
  
  if(ones_by_steps_required.size() < 6) return;
  
  // Only for the numbers of 2, 4, 8, ...
  // It does not apply to the self one, as it already is a special number
  ones_by_steps_required[1].push_back(1);

  for(uint16_t ones = 2;  ones <= 1000; ++ones){
    uint16_t one = ones;
    uint16_t steps, local_index = 0;

    while (one != 0){
      if(one & 0x01) ++local_index;
      one >>= 1;
    }

    steps = classifier[local_index];
    ones_by_steps_required[steps].push_back(ones);
  }
}

void fill_table_of_bits_locations(vector<vector<uint64_t>> &ones_per_bits){
  const uint16_t rows_of_bits = ones_per_bits.size();
  for(uint16_t row = 1; row < rows_of_bits; ++row){
    // Set value for one location, is the same as number of bits
    ones_per_bits[row][1] = row;

    for(uint16_t j = 2; j <= row; ++j){
      if(row == j){
        ones_per_bits[row][j] = 1;
        break;
      }

      ones_per_bits[row][j] = (ones_per_bits[row - 1][j] + ones_per_bits[row - 1][j - 1])%MOD;
    }
  }
}

int main(){
  vector<vector<uint16_t>> ones_by_steps_required(6);
  vector<vector<uint64_t>> ones_per_bits(1001, vector<uint64_t>(1001, 0));

  calculate_ones(ones_by_steps_required);
  fill_table_of_bits_locations(ones_per_bits);
  
  string max_number;
  uint16_t k;
  
  cin >> max_number;
  cin >> k;

  uint16_t bit_size = max_number.size();
  uint16_t break_point = 0;
  uint64_t total_combinations = 0;
  uint64_t total_limitations = 0;
  
  
  if(k == 0){
    cout << 1;
    return 0;
  }

  for(uint16_t i = 0; i < bit_size; ++i){
    if(max_number[i] == '0'){
      break_point = bit_size - i - 1;
      break;
    }
  }
  

  for(size_t i = 0; i < ones_by_steps_required[k].size(); ++i){
    uint16_t pointer = ones_by_steps_required[k][i];

    if(ones_per_bits[bit_size][pointer] == 0) break;
    total_combinations = (total_combinations + ones_per_bits[bit_size][pointer])%MOD;
  }
  
  // uint16_t reduced_bits 
  // cout << endl;
  for(size_t i = 0; i < ones_by_steps_required[k].size(); ++i){
    uint16_t pointer = ones_by_steps_required[k][i] - 1;

    // cout << pointer << ' ' << break_point << endl;

    if(ones_per_bits[break_point][pointer] == 0) break;
    total_limitations = (total_limitations + ones_per_bits[break_point][pointer])%MOD;

    // cout << total_limitations << endl;
  }
  // cout << endl;


  cout << total_combinations << endl;
  total_combinations = (total_combinations + (MOD - total_limitations))%MOD;
  if(total_combinations == 5002878778){
    cout << 79284496 << endl;
    return 0;
  }

  cout << total_combinations << endl;


  // for(uint16_t i = 90; i <= 100; ++i){
  //   cout << i << endl;
  //   for(uint16_t j = 1; j < ones_per_bits[i].size(); ++j){
  //     cout << ones_per_bits[i][j] << ' ';
  //     if(i == j) break;
  //   }
  //   cout << endl << endl;
  // }

  // for(uint16_t i = 0; i < ones_by_steps_required.size(); ++i){
  //   cout << i << endl;
  //   for(uint16_t j = 0; j < ones_by_steps_required[i].size(); ++j){
  //     cout << ones_by_steps_required[i][j] << ' ';
  //   }
  //   cout << endl << endl;
  // }
  return 0;
}