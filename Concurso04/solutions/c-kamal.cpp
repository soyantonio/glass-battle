#include <iostream>
#include <string>
#include <vector>
#define MAX_DISTANCE 1
#define NON_DETERMINED 2
#define NOT_POSSIBLE_BRUSH 3
#define ALTERED 'X'

using namespace std;

struct Brush{
  private:  
    uint32_t width;
    uint32_t height;
    uint32_t pointer_y;
    uint32_t pointer_x;

  public:
    Brush(
      const uint32_t &width, const uint32_t &height,
      const uint32_t &pointer_x, const uint32_t &pointer_y
    ){
      this -> width = width;
      this -> height = height;
      this -> pointer_x = pointer_x;
      this -> pointer_y = pointer_y;
    }

    void expand_width(const vector<vector<char>> &painting){
      while (painting[pointer_y][pointer_x + width + 1] == ALTERED){
        width++;
      }
    }

    void expand_height(const vector<vector<char>> &painting){
      while (painting[pointer_y + height + 1][pointer_x] == ALTERED){
        height++; 
      }
    }

    bool soft_update_height(const vector<vector<char>> &painting, const bool &updated){
      if(updated) return true;
      uint32_t limit_y = pointer_y + height;
      uint32_t limit_x = pointer_x + width;

      if(painting[pointer_y + 1][limit_x + 1] != ALTERED) return false;
      while (painting[pointer_y + 2 + height][pointer_x] == ALTERED){
        height++;
      }

      return true;
    }

    bool soft_update_width(const vector<vector<char>> &painting, const bool &updated){
      if(updated) return true;
      uint32_t limit_y = pointer_y + height;
      uint32_t limit_x = pointer_x + width;

      if(painting[limit_y + 1][pointer_x + 1] != ALTERED) return false;
      while (painting[pointer_y][pointer_x + 2 + width] == ALTERED){
        width++;
      }

      return true;      
    }

    pair<uint32_t, uint32_t> measures(){
      return pair<uint32_t, uint32_t>(this -> width, this -> height);
    }

    bool valid_in(const vector<vector<char>> &painting){
      uint32_t limit_y = pointer_y + height;
      uint32_t limit_x = pointer_x + width;
      
      if(painting[pointer_y][pointer_x] != ALTERED) return false;
      if(painting[pointer_y][limit_x] != ALTERED) return false;
      if(painting[limit_y][pointer_x] != ALTERED) return false;
      if(painting[limit_y][limit_x] != ALTERED) return false;

      return true;
    }

    bool move_in(const vector<vector<char>> &painting){
      uint32_t limit_x = pointer_x + width;
      uint32_t limit_y = pointer_y + height;
      bool top_move = painting[pointer_y][limit_x + 1] == ALTERED;
      bool bottom_move = painting[limit_y][limit_x + 1] == ALTERED;
      bool left_move = painting[limit_y + 1][pointer_x] == ALTERED;
      bool right_move = painting[limit_y + 1][limit_x] == ALTERED;

      bool can_move_horizontal = top_move && bottom_move;
      bool can_move_vertical = left_move && right_move;

      bool undetermined_move = can_move_vertical && can_move_horizontal;
      bool can_move = can_move_horizontal || can_move_vertical;
      bool alterations = top_move || bottom_move || left_move || right_move;

      if(undetermined_move) throw NON_DETERMINED;
      if(!can_move && alterations) throw NOT_POSSIBLE_BRUSH;
      if(!can_move) return false;

      if(can_move_horizontal) ++pointer_x;
      if(can_move_vertical) ++pointer_y;

      return true;
    }
    
};

bool is_valid_painting(
  const vector<vector<char>> &painting,
  const uint32_t &painting_height,
  const uint32_t &painting_width
){
  uint32_t last_row = 0;
  uint32_t last_col = 0;  
  bool is_row_set = false;
  bool is_col_set = false;
  bool are_rows_continuos;
  bool are_cols_continuos;
  uint32_t prev_line_start = 0;
  uint32_t prev_line_end = 0;

  for(uint32_t row = 0; row < painting_height; ++row){
    is_col_set = false;
    last_col = 0;

    uint32_t line_start, line_end;

    // per line
    for(uint32_t col = 0; col < painting_width; ++col){
      const char &cell = painting[row][col];
      
      if(cell != 'X') continue;
      if(!is_col_set) last_col = col;
      if(!is_row_set) last_row = row;

      are_rows_continuos = row - last_row <= MAX_DISTANCE;
      are_cols_continuos = col - last_col <= MAX_DISTANCE;

      if(!are_cols_continuos || !are_rows_continuos){
        return false;
      }

      if(!is_col_set) line_start = col;
      
      line_end = col;
      is_col_set = true;
      is_row_set = true;
      last_row = row;
      last_col = col;
    }

    if(!is_col_set) continue;

    if(line_start < prev_line_start || line_end < prev_line_end){
      return false;
    }
    
    prev_line_start = line_start;
    prev_line_end = line_end;
  }
  return true;
}


pair<uint32_t, uint32_t> down_first(
  const vector<vector<char>> &painting,
  const uint32_t &start_y,
  const uint32_t &start_x
){
  Brush *brush = new Brush(0, 0, start_x, start_y);
  bool is_height_set = false;
  brush -> expand_width(painting);

  while(true){
    bool valid_position = brush -> valid_in(painting);
    if(!valid_position) throw 1;

    is_height_set = brush -> soft_update_height(painting, is_height_set);

    try{
      bool brush_moved = brush -> move_in(painting);
      if(!brush_moved) break;
    }
    catch(int x){
      throw 1;
    }
  }
  return brush -> measures();
}


pair<uint32_t, uint32_t> right_first(
  const vector<vector<char>> &painting,
  const uint32_t &start_y,
  const uint32_t &start_x
){
  Brush *brush = new Brush(0, 0, start_x, start_y);
  bool is_width_set = false;
  brush -> expand_height(painting);

  while(true){
    bool valid_position = brush -> valid_in(painting);
    if(!valid_position) throw 1;

    is_width_set = brush -> soft_update_width(painting, is_width_set);

    try{
      bool brush_moved = brush -> move_in(painting);
      if(!brush_moved) break;
    }
    catch(int x){
      throw 1;
    }
  }
  return brush -> measures();
}


int main(){
  uint32_t n, m;
  uint32_t start_x, start_y;
  bool checkpoint_set = false;
  cin >> n >> m;

  vector<vector<char>> painting(n + 5, vector<char>(m + 5));
  for(uint32_t i = 0; i < n; ++i){
    for(uint32_t j = 0; j < m; ++j){
      cin >> painting[i][j];
      if(!checkpoint_set && painting[i][j] == 'X'){
        start_x = j;
        start_y = i;
        checkpoint_set = true;
      }
    }
  }

  bool valid = is_valid_painting(painting, n, m);

  if(!valid){
    cout << "-1";
    return 0;
  }

  bool not_possible_down = false;
  bool not_possible_right = false;
  uint32_t down_height = 0, down_width = 0;
  uint32_t right_height = 0, right_width = 0;
  uint32_t area;
 
  try{
    auto dfirst = down_first(painting, start_y, start_x);
    down_height = dfirst.first + 1;
    down_width = dfirst.second + 1;
  }
  catch(int x){
    not_possible_down = true;
  }
  
  try{
    auto rfirst = right_first(painting, start_y, start_x);
    right_height = rfirst.first + 1;
    right_width = rfirst.second + 1;
  }
  catch(int x){
    not_possible_right = true;
  }
  
  if(not_possible_right && not_possible_down){
    cout << "-1";
    return 0;
  }

  if(right_height*right_width == 0) area = down_height*down_width;
  else if(down_height*down_width == 0) area = right_height*right_width;
  else area = min(right_height*right_width, down_height*down_width);

  cout << area;
  return 0;
}
