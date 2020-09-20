#include <iostream>
using namespace std;

int main() {
  int n, steps = 0;
  cin>>n;

  // Arreglo con los numeros a ordenar de forma ascendente
  // Operaciones validas unit shift 
  int arr[n];
  
  //Llenamos el arreglo
  for(int i=0; i<n;i++){
    cin>>arr[i];
  }

  int i=n-1;
  int max = arr[i];

  for(; i>0;i--){
    steps++;
    
    // The arr is not complete it in Asc Order
    if(arr[i] < arr[i-1]){
      // Move the cursor to the next position
      i--;
      break;
    }
    // All the elements are sorted in Asc Order
    if (steps == (n-1)){ 
      cout<< "0";
      return 0;
    }
  }

  // Handle case where the last element should be evaluated
  if(i == 0){
    bool seqOutOfRange = arr[i] < max;
    if(seqOutOfRange){
      cout<<"-1";
      return 0;
    }
  }
  
  for(;i>0;i--){
    // There is a mismatch in the second sequence
    bool breaksDescendingSeq = arr[i] < arr[i-1];
    // The max element of the first seq, is greater than
    // the current element of the second sequence
    bool seqOutOfRange = arr[i] < max || arr[i - 1] < max;

    if(breaksDescendingSeq || seqOutOfRange){
      cout<<"-1";
      return 0;
    }
  }

  cout<<steps; 
}
