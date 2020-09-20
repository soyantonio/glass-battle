#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int main(){
  uint16_t tests;
  cin >> tests;

  string s[tests];
  for (uint16_t t = 0; t < tests; ++t) {
    cin >> s[t];
  }

  for (uint16_t t = 0; t < tests; ++t) {
    uint32_t original_length = s[t].size();
    uint32_t largest_digit_counter = 0;
    uint32_t largest_pair_counter = 0;

    uint32_t digits_counters[10];
    uint32_t pair_table[10][10];
    bool available_table[10][10];

    for (int i = 0; i < 10; ++i) {
      digits_counters[i] = 0;
      for (int j = 0; j < 10; ++j) {
        available_table[i][j] = false;
        pair_table[i][j] = 0;
      }
    }

    uint8_t first_digit = s[t][0] - '0';
    uint32_t first_digit_counter = digits_counters[first_digit] + 1;
    digits_counters[first_digit] = first_digit_counter;
    largest_digit_counter = max(largest_digit_counter, first_digit_counter);

    for (uint32_t i = 1; i < original_length; ++i) {
      uint8_t prev_digit = s[t][i - 1] - '0';
      uint8_t digit = s[t][i] - '0';

      uint32_t digit_counter = digits_counters[digit] + 1;
      digits_counters[digit] = digit_counter;
      largest_digit_counter = max(largest_digit_counter, digit_counter);

      for (uint32_t j = 0; j < 10; ++j) {
        available_table[prev_digit][j] = true;
      }

      for (uint32_t j = 0; j < 10; ++j) {
        if (available_table[j][digit] && j != digit) {
          available_table[j][digit] = false;
          pair_table[j][digit] += 1;

          largest_pair_counter = max(largest_pair_counter, pair_table[j][digit]);
        };
      }
    }

    uint32_t steps_for_mono_seq = original_length - largest_digit_counter;
    uint32_t steps_for_two_seq = original_length - 2;
    uint32_t steps_for_pair_seq = original_length - 2 * largest_pair_counter;

    uint32_t min_steps = min(steps_for_pair_seq, min(steps_for_two_seq, steps_for_mono_seq));

    cout << unsigned(min_steps) << '\n';
  }
}
