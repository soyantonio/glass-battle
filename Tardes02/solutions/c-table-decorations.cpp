#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void sort_colors(vector<uint32_t> &colors){
  uint32_t max_, min_, other_;
  bool seen_max = false, seen_min = false;

  max_ = max(colors[0], max(colors[1], colors[2]));
  min_ = min(colors[0], min(colors[1], colors[2]));

  // For the same values at the three positions
  other_ = colors[0];
  for(uint16_t i = 0; i < colors.size(); ++i){
    if(seen_min && colors[i] != max_) other_ = colors[i];
    if(seen_max && colors[i] != min_) other_ = colors[i];
    if(max_ == colors[i]) seen_max = true;
    if(min_ == colors[i]) seen_min = true;
  }

  colors[0] = max_;
  colors[1] = other_;
  colors[2] = min_;
}

uint32_t normalize(vector<uint32_t> &colors){
  uint32_t old_tables;
  uint32_t tables = 0;

  sort_colors(colors);
  // Make smaller largest ballons
  uint32_t k = (colors[0] - colors[1])/2;
  uint32_t tables_smaller = min(k, colors[2]);

  colors[2] -= tables_smaller;
  colors[0] -= tables_smaller*2;

  // Remove third group
  uint32_t tables_reducer = colors[2];
  colors[2] -= tables_reducer;
  colors[1] -= tables_reducer;
  colors[0] -= tables_reducer;

  do{
    old_tables = tables;
    uint32_t theta = (colors[0] - colors[1])/2;
    uint32_t rb = min(theta, colors[1]);
    tables += rb;
    colors[0] -= rb*2;
    colors[1] -= rb;
    sort_colors(colors);
  }while (old_tables != tables);

  return tables + tables_reducer + tables_smaller;
}

uint32_t tables_two_colors(uint32_t local_max, uint32_t local_min){
  if(local_min == 0) return 0;
  if(local_min*2 <= local_max) return local_min;
  
  uint32_t self_tables = local_max/2;
  uint32_t self_tables_residue = local_max%2;

  uint32_t left_ballons = local_min - self_tables;
  uint32_t extra_tables = (self_tables_residue + left_ballons)/3;
  
  return extra_tables + self_tables;
}


int main(){
  vector<uint32_t> colors;
  vector<uint32_t> init_colors(3);
  cin >> init_colors[0] >> init_colors[1] >> init_colors[2];

  uint32_t tables = normalize(init_colors);

  if(init_colors[0] != 0) colors.push_back(init_colors[0]);
  if(init_colors[1] != 0) colors.push_back(init_colors[1]);

  if(colors.size() == 0 || colors.size() == 1){
    cout << tables;
    return 0;
  }
  
  tables += tables_two_colors(colors[0], colors[1]);
  cout << tables;

  return 0;
}