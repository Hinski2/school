# zad 11

---

algorytm dijkstry
``` c++
// startujemy z wierzchołka V
void dijkstra(){
    priority_queue <pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // {dist, u}
    pq.insert({V, 0});

    while(!pq.empty()){
        auto [dist, v] = pq.top(); pq.pop();

        if(vis[v]) continue;
        vis[v] = 1;
        odl[v] = d;

        for(auto [d, u]: G[v]){ 
            if(vis[u]) continue;
            pq.insert({dist + d, u});
        }
    }
}

```