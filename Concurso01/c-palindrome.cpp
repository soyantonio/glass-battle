#include <iostream>

using namespace std;

uint32_t delta(uint32_t x, uint32_t y){
  if(x < y) return y - x;
  return x - y;
}

int main(){
  uint32_t sentence_lenght, cursor_position, normalized_cursor;  
  string nam_sentence;
  uint32_t start_limiter = 0;
  uint32_t end_limiter = 0;
  bool is_limiter_set = false;
  uint32_t horizontal_steps = 0;
  uint32_t vertical_steps = 0;
  

  cin >> sentence_lenght;
  cin >> cursor_position;
  cin >> nam_sentence;

  uint32_t middle_of_sentence = sentence_lenght/2;
  uint32_t end_of_sentence = sentence_lenght - 1;
  uint8_t zsize = 'z' - 'a' + 1;


  normalized_cursor = cursor_position - 1;
  if(normalized_cursor >= middle_of_sentence){
    normalized_cursor = end_of_sentence - normalized_cursor;
  }

  for(size_t i = 0; i < middle_of_sentence; i++){
    uint8_t upper_char = nam_sentence[i] - 'a' + 1;
    uint8_t lower_char = nam_sentence[end_of_sentence - i] - 'a' + 1;
    uint8_t helper_char;

    if(upper_char == lower_char) continue;
    if(!is_limiter_set) start_limiter = i;

    is_limiter_set = true;
    end_limiter = i;

    if(lower_char > upper_char){
      helper_char = upper_char;
      upper_char = lower_char;
      lower_char = helper_char;
    }

    uint8_t down_steps = delta(upper_char, lower_char);
    uint8_t up_steps = delta(zsize, upper_char) + lower_char;
    
    if(down_steps < up_steps) vertical_steps += down_steps;
    else vertical_steps += up_steps;
  }

  if(!is_limiter_set){
    cout << 0;
    return 0;
  }
  
  uint32_t end_delta = delta(end_limiter, normalized_cursor);
  uint32_t start_delta = delta(start_limiter, normalized_cursor);
  

  if(end_delta < start_delta){
    horizontal_steps = end_delta;
    horizontal_steps += delta(start_limiter, end_limiter);
  }
  else {
    horizontal_steps = start_delta;
    horizontal_steps += delta(end_limiter, start_limiter);
  }

  cout << horizontal_steps + vertical_steps;
  return 0;
}
