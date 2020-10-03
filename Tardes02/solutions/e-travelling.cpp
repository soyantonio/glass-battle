#include <iostream>
#include <vector>
#include <string>

using namespace std;

const uint64_t MOD = 1e9 + 7;
vector<vector<uint64_t>> ones_per_bits(1001, vector<uint64_t>(1001, 0));
vector<uint16_t> steps_by_ones(1001, 0);

uint16_t count_ones(uint16_t number);
uint64_t mod_addition(const uint64_t &a, const uint64_t &b);
uint64_t mod_substraction(const uint64_t &a, const uint64_t &b);


void set_combinations_bits_locations(){
  const uint16_t rows_of_bits = ones_per_bits.size();
  ones_per_bits[0][0] = 1;

  // Combinations filled -> rows(bits) -> cols(number_of_ones)
  for(uint16_t row = 1; row < rows_of_bits; ++row){
    ones_per_bits[row][0] = 1;
    ones_per_bits[row][1] = row;

    for(uint16_t j = 2; j <= row; ++j){
      if(row == j){
        ones_per_bits[row][j] = 1;
        break;
      }
      const uint64_t &prev_bit_same_loc = ones_per_bits[row - 1][j];
      const uint64_t &prev_bit_prev_loc = ones_per_bits[row - 1][j - 1];
      ones_per_bits[row][j] = mod_addition(prev_bit_same_loc, prev_bit_prev_loc);
    }
  }
}

void set_required_steps_by_ones(){
  const uint16_t MAX_BITS = 1000;

  steps_by_ones[1] = 0;
  for(uint16_t i = 2; i <= MAX_BITS; i++) {
    steps_by_ones[i] = steps_by_ones[count_ones(i)] + 1;
  }
}

uint64_t special_calc(
  const uint16_t &bits, 
  const uint16_t &k,
  const uint16_t &previous_ones
){
  const uint16_t reduced_steps = k - 1;
  uint64_t special_numbers = 0;

  for(uint16_t j = max(previous_ones, (uint16_t)1); j < 1000; j++) {
    // Look given number of ones(j) if it can converge in k-1 steps
    if(steps_by_ones[j] == reduced_steps) {
      uint64_t combinations = ones_per_bits[bits][j-previous_ones];
      special_numbers = mod_addition(special_numbers, combinations);

      if(combinations == 0) break;
    }
  }

  return special_numbers;
}

int main(){
  set_combinations_bits_locations();
  set_required_steps_by_ones();
  
  string max_number;
  uint16_t k;
  
  cin >> max_number;
  cin >> k;

  if(k == 0) {
    cout << "1\n";
    return 0;
  }

  uint16_t ones_counter = 0;
  uint64_t special_numbers = 0;

  if(max_number[0] == '1' && k == 1){
    // As it can be double content for the self case, it is a self-guard
    special_numbers = mod_substraction(special_numbers, 1);
  }

  for(uint16_t i = 0; i < max_number.size(); i++) {
    if(max_number[i] == '0') continue;

    uint16_t reduced_bits = max_number.size()-i-1;
    uint64_t numbers_in_reduced_bits = special_calc(reduced_bits, k, ones_counter);
    special_numbers = mod_addition(special_numbers, numbers_in_reduced_bits);

    ones_counter++;
  }

  // This case is for the self maximum number can converge
  if(steps_by_ones[ones_counter] == k-1){
    special_numbers =  mod_addition(special_numbers, 1);
  }

  cout << special_numbers << endl;
  return 0;  
}

uint16_t count_ones(uint16_t number){
  uint16_t ones = 0;
  
  while (number){
    if(number%2 == 1) ones++;
    number /= 2;
  }

  return ones;
}

uint64_t mod_addition(const uint64_t &a, const uint64_t &b){
  return (a + b)%MOD;
}

uint64_t mod_substraction(const uint64_t &a, const uint64_t &b){
  return (a+MOD-b)%MOD;
}
