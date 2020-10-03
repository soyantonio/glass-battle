#include <iostream>
#include <string>
#include <vector>
#include <queue>
#define MAX_DISTANCE 1

using namespace std;

struct Rectangle{
  uint16_t start_x;
  uint16_t start_y;
  uint16_t end_x;
  uint16_t end_y;

  uint16_t rows(){
    return end_y - start_y + 1;
  }

  uint16_t cols(){
    return end_x - start_x + 1;
  }
};


void altered_rectangles_in(
  const vector<vector<char>> &painting,
  // queue<vector<uint16_t>> &rectangles
  queue<Rectangle> &rectangles
){
  // x_s, y_s,  x_e, y_e
  // vector<uint16_t> rectangle(4, 0);
  Rectangle rectangle;

  const uint16_t painting_height = painting.size();
  const uint16_t painting_width = painting[0].size();
  uint16_t last_row = 0;
  uint16_t last_col = 0;  
  bool is_row_set = false;
  bool is_col_set = false;
  bool are_rows_continuos;
  bool are_cols_continuos;

  for(uint16_t row = 0; row < painting_height; ++row){
    is_col_set = false;
    last_col = 0;

    uint16_t line_start, line_end;

    // per line
    for(uint16_t col = 0; col < painting_width; ++col){
      const char &cell = painting[row][col];
      
      if(cell != 'X') continue;
      if(!is_col_set) last_col = col;
      if(!is_row_set) last_row = row;

      are_rows_continuos = row - last_row <= MAX_DISTANCE;
      are_cols_continuos = col - last_col <= MAX_DISTANCE;

      if(!are_cols_continuos || !are_rows_continuos){
        throw -1;
      }

      if(!is_col_set) line_start = col;
      
      line_end = col;
      is_col_set = true;
      is_row_set = true;
      last_row = row;
      last_col = col;
    }

    if(!is_col_set) continue;

    if(rectangles.size() == 0){
      rectangle.start_x = line_start;
      rectangle.start_y = row;
      rectangle.end_x = line_end;
      rectangle.end_y = row;
      rectangles.push(rectangle);
    }

    const uint16_t &prev_line_start = rectangles.back().start_x;
    const uint16_t &prev_line_end = rectangles.back().end_x;

    if(line_start < prev_line_start || line_end < prev_line_end){
      throw -1;
    }

    if(line_start != prev_line_start || line_end != prev_line_end){
      rectangle.start_x = line_start;
      rectangle.start_y = row;
      rectangle.end_x = line_end;
      rectangle.end_y = row;
      rectangles.push(rectangle);
    }

    // For the lines that belongs to the same rectangle
    rectangles.back().end_x = line_end;
    rectangles.back().end_y = row;
  }
}

int main(){
  queue<Rectangle> rectangles;
  uint16_t n, m;
  cin >> n >> m;

  vector<vector<char>> painting(n, vector<char>(m));
  for(uint16_t i = 0; i < n; ++i){
    for(uint16_t j = 0; j < m; ++j){
      cin >> painting[i][j];
    }
  }

  try{
    altered_rectangles_in(painting, rectangles);
  }
  catch(int error){
    cout << "-1";
    return 0;
  }

  Rectangle &rect = rectangles.front();
  if(rectangles.size() == 1){
    cout << min(rect.rows(), rect.cols());
    return 0;
  }
  
  uint16_t rows_old = rect.rows();
  uint16_t start_old = rect.start_x;
  uint16_t end_old = rect.end_x;
  rectangles.pop();
  uint16_t width = 0;
  uint16_t height = 0;

  while (!rectangles.empty()){
    Rectangle &current_rect = rectangles.front();
    uint16_t rows_new = current_rect.rows();
    uint16_t cols_new = current_rect.cols();
    uint16_t start_new = current_rect.start_x;
    uint16_t common = end_old - start_new + 1;

    if(start_new == start_old){
      
    }

    // if(rows2 > rows_old && cols2 > common && start2 != start_old){
    //   cout << "-1";
    //   return 0;
    // }

    // if(rows2 < rows_old && start2 != start_old){
    //   cout << "-1";
    //   return 0;
    // }

    // width = common;
    // height = min(rows_old, rows2);
    // cout << "Amaxing" << endl;
    // cout << algo.start_x << ' ' << algo.start_y << endl;
    // cout << algo.end_x << ' ' << algo.end_y << endl;

    rectangles.pop();
  }
  
  cout << width*height;
  return 0;
}