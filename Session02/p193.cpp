#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <set>

using namespace std;

#define MAX 101
#define CONNECTED 1

#define BLACK 1
#define NOT_VISITED 2


int main(){
  char graph[MAX][MAX];
  int n, k, m, start, end, i, j;

  scanf("%i", &m);
  for(i = 0; i < m; ++i){
    scanf("%i %i", &n, &k);
    memset(graph, 0, sizeof(char)*MAX*MAX);
    
    for(j = 0; j < k; ++j){
      scanf("%i %i", &start, &end);
      graph[start][end] = CONNECTED;
      graph[end][start] = CONNECTED;
    }

    queue<int> q;
    set<int> visited;
    char colors[MAX];
    bool is_bipartite = true;
    int accum;

    memset(colors, NOT_VISITED, sizeof(char)*MAX);
    q.push(1);
    colors[1] = BLACK;
    accum = 1;

    while(!q.empty()){
      int ele = q.front();
      q.pop();
      if(visited.find(ele) != visited.end()){
        cout << "FF";
        continue;
      }
      visited.insert(ele);

      for(j = 0; j <=n; ++j){
        if(graph[ele][j] != CONNECTED) continue;
        if(colors[j] != NOT_VISITED) continue;
        
        colors[j] = 1 - colors[ele];
        q.push(j);
        if(colors[j] == BLACK){
          accum++;
        }
      }
    }

    for(j = 0; j < MAX; ++j){
      if(colors[j] == BLACK){
        cout << unsigned(j) << ' ';
      }
    }

  }

  return 0;
}