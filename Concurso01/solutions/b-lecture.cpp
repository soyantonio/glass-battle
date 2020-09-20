#include <iostream>
#include <unordered_map> 

#include <string>


using namespace std;

int main(int argc, char const *argv[]){
  unordered_map<string, string> dictionay;
  uint16_t words_at_lecture, dictionary_words_number;

  cin >> words_at_lecture;
  cin >> dictionary_words_number;
  
  for(uint16_t i = 0; i < dictionary_words_number; i++){
    string first_lang_word;
    string second_lang_word;
    
    cin >> first_lang_word;
    cin >> second_lang_word;

    if(first_lang_word.length() <= second_lang_word.length()){
      dictionay[first_lang_word] = first_lang_word;
    }
    else {
      dictionay[first_lang_word] = second_lang_word;
    }
  }

  for(uint16_t i = 0; i < words_at_lecture; i++){
    string lecture_word;
    cin >> lecture_word;
    
    cout << dictionay.find(lecture_word) -> second;
    if (i + 1 < words_at_lecture) {
      cout << " ";
    }
  }

  return 0;
}
