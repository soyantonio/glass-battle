#include <iostream>
#define TEAM_MAX_COMBINATIONS 1

using namespace std;

uint64_t combinations_of2(uint64_t n){
  if(n < 2) return 0;
  if(n == 2) return 1;

  uint64_t prev_n = n - 1;
  
  if(prev_n%2 == 0) return (prev_n/2)*n;
  else return (n/2)*prev_n;
}


int main(){
  uint64_t n, m, max_number;

  cin >> n >> m;
  max_number = n + 2;

  uint64_t max_n = n - (m - TEAM_MAX_COMBINATIONS);
  
  uint64_t min_members = n/m;
  uint64_t min_nextra = min_members + 1;
  uint64_t with_extra_member = n%m;
  uint64_t with_normal_size = m - with_extra_member;
  
  uint64_t min_friends_extra = combinations_of2(min_nextra)*with_extra_member;
  uint64_t min_friends_normal = combinations_of2(min_members)*with_normal_size;

  uint64_t max_friends = combinations_of2(max_n);
  uint64_t min_friends = min_friends_extra + min_friends_normal;

  cout << min_friends << ' ' << max_friends;

  return 0;
}