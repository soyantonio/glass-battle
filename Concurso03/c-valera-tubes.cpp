#include <iostream>
#define LEFT_TO_RIGHT true
#define RIGHT_TO_LEFT false

using namespace std;

int main(){
  uint16_t rows, columns, tubes;
  cin >> rows >> columns >> tubes;

  bool direction = LEFT_TO_RIGHT;
  uint32_t total_cells = rows*columns;
  uint16_t rowp = 1;
  uint16_t colp = 1;
  

  for(uint16_t t = 0; t < tubes; ++t){
    uint32_t tube_cells = 2;

    if(t + 1 == tubes) {
      uint32_t prev_cells = 2*(tubes - 1);
      tube_cells = total_cells - prev_cells;
    }

    cout << tube_cells << ' ';

    for(uint32_t c = 0; c < tube_cells; ++c){
      cout << rowp << ' ' << colp << ' ';
      
      if(direction == LEFT_TO_RIGHT) ++colp;
      else --colp;

      
      if(colp > columns){
        direction = RIGHT_TO_LEFT;
        colp = columns;
        rowp++;
      }
      else if(colp == 0){
        direction = LEFT_TO_RIGHT;
        colp = 1;
        rowp++;
      }
    }

    cout << endl;
  }

  return 0;
}