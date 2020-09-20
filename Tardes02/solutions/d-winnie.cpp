#include <fstream> 

using namespace std;

int main(){
  uint16_t jars, k, weight, piglet = 0;
  ifstream finputs("input.txt");

  if(finputs.is_open()){
    finputs >> jars >> k;

    for(uint16_t i = 0; i < jars; ++i){
      finputs >> weight;
      uint16_t j = 0;

      while (true){
        if(weight < k || j == 3){
          piglet += weight;
          break;
        }
        j++;
        weight -= k;
      }
    }
  }

  ofstream file("output.txt");
  file << piglet;
  file.close();
  return 0;
}