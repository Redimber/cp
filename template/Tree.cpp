
struct Tree {
  
    int n;
    vector<vector<int>> adj;
    vector<vector<int>> up;
    vector<int> parent;
    vector<int> depth;

    int LOG = 22;

    
    Tree(int n):n(n){
        adj.resize(n);
        up.resize(n,vector<int>(LOG));
        depth.resize(n);
        parent.resize(n);
    }

    
    void read() {
        for(int i=0;i<n-1;i++) {
            int u,v;
            cin>>u>>v;
            u--,v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        dfs(0,-1);
        build();
    }

    void dfs(int i, int p) {
        if(p!=-1) {
            parent[i] = p;
            depth[i] = depth[p] + 1;
        }

        for(int child: adj[i]) {
            if(child != p) {
                dfs(child,i);
            }
        }
    }

    void build() {
        for(int j = 0; j < LOG; j++) {
            for(int v = 0; v < n; v++) {
                if(j == 0) {
                    up[v][0] = parent[v];
                }else {
                    up[v][j] = up[ up[v][j-1] ][j-1];
                }
            }
        }
    }

    int goUp(int node, int k) {
        if(depth[node] < k) return -1; 

        for(int j = LOG - 1; j >= 0; j--) {
            if(k >= (1 << j)) {
                node = up[node][j];
                k -= 1 << j;
            }
        }

        return node;
    }

    int lca(int a, int b) {
        if(depth[a] < depth[b]) swap(a, b);
        int k = depth[a] - depth[b];
        a = goUp(a,k);
        if(a == b) {
            return a;
        }
        for(int j = LOG - 1; j >= 0; j--) {
            if(up[a][j] != up[b][j]) {
                a = up[a][j];
                b = up[b][j];
            }
        }
        return up[a][0];
    }
    
    int distance(int a, int b) {
        return depth[a]+depth[b]-2*depth[lca(a,b)];
    }
};



