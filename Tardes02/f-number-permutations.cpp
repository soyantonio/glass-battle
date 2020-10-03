#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

typedef map<uint32_t, vector<uint32_t>> group_t;
const uint64_t MOD = 998244353;

uint64_t mod_addition(const uint64_t &a, const uint64_t &b);
uint64_t mod_multiplication(const uint64_t &a, const uint64_t &b);
uint64_t mod_substraction(const uint64_t &a, const uint64_t &b);
void init_factorials(vector<uint64_t> &factorials);

pair<group_t, group_t> group_by_number(const vector<pair<uint32_t, uint32_t>> &pairs){
  pair<group_t, group_t> groups;

  for(uint32_t i = 0; i < pairs.size(); ++i){
    groups.first[pairs[i].first].push_back(i);
    groups.second[pairs[i].second].push_back(i);
  }

  return groups;
}

uint64_t subpermutations_of(const vector<uint64_t> &factorials, const group_t &group){
  uint64_t permutations = 1;
  for(auto hash_element:group){
    uint64_t subpermutation = factorials[hash_element.second.size()];
    permutations = mod_multiplication(permutations, subpermutation);
  }
  return permutations;
}

int main(){
  uint32_t n;
  cin >> n;

  vector<pair<uint32_t, uint32_t>> pairs(n);
  vector<uint64_t> factorials(n + 1);

  init_factorials(factorials);
  for(uint32_t i = 0; i < n; ++i){
    cin >> pairs[i].first >> pairs[i].second;
  }

  auto groups = group_by_number(pairs);
  const group_t &group_a = groups.first;
  const group_t &group_b = groups.second;

  bool is_mono_sequence_a = group_a.size() == 1;
  bool is_mono_sequence_b = group_b.size() == 1;


  if(is_mono_sequence_a || is_mono_sequence_b){
    cout << 0;
    return 0;
  }

  vector<pair<uint32_t, uint32_t>> sorted_pairs(n);
  uint32_t itemp = 0;
  uint64_t permutations_ab = 1;

  for(auto hash_element:group_a){
    auto indexes_of_number = hash_element.second;
    map<uint32_t, uint32_t> matched;
    multiset<uint32_t> complement_sorted;

    for(auto i:indexes_of_number){
      complement_sorted.insert(pairs[i].second);
      ++matched[pairs[i].second];
    }

    for(auto c:complement_sorted){
      sorted_pairs[itemp] = pair<uint32_t, uint32_t>(hash_element.first, c);
      ++itemp;
    }

    for(auto incidents:matched){
      const uint64_t combinations = factorials[incidents.second];
      permutations_ab = mod_multiplication(permutations_ab, combinations);
    }
  }

  // Detect if second group is sorted
  for(uint32_t i = 1; i < n; ++i){
    if(sorted_pairs[i - 1].second > sorted_pairs[i].second){
      permutations_ab = 0;
    }
  }

  // Get Subpermutations
  uint64_t permutations, total_permutations = factorials[n];
  uint64_t permutations_a = subpermutations_of(factorials, group_a);
  uint64_t permutations_b = subpermutations_of(factorials, group_b);

  permutations = mod_substraction(total_permutations, permutations_a);
  permutations = mod_substraction(permutations, permutations_b);
  permutations = mod_addition(permutations, permutations_ab);

  cout << permutations;
  return 0;
}


void init_factorials(vector<uint64_t> &factorials){
  factorials[0] = 1;
  factorials[1] = 1;
  for(size_t i = 2; i < factorials.size(); ++i){
    factorials[i] = mod_multiplication(i, factorials[i-1]);
  }
}

uint64_t mod_multiplication(const uint64_t &a, const uint64_t &b){
  return (a*b)%MOD;
}

uint64_t mod_substraction(const uint64_t &a, const uint64_t &b){
  return (a + MOD - b)%MOD;
}

uint64_t mod_addition(const uint64_t &a, const uint64_t &b){
  return (a + b)%MOD;
}