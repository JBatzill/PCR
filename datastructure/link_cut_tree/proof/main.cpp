//https://www.codechef.com/problems/GERALD07
#include <bits/stdc++.h>

#define pb push_back

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef ll (*MY_FUNC)(ll x, ll y);

const ll MAX_LL = 1LL << 62; //(1 << 63) - 1
const int MAX_INT = (int)((1LL << 31) - 1);
const double PI = acos(-1);
const double EPS = 0.0000001L;
const ll MOD = 1000000007;


//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

typedef struct {
    int l,r,idx;
} query;

vector<int> weights;

typedef struct node {
    //left child, right child, pref. path parent, aux parent
    node *l = NULL, *r=NULL, *p = NULL, *pp=NULL;
    //indicates whether tree needs to be flipped (childs swaped)
    bool flip = false;
    //path aggr values: for whole aux. path [pav], for node [nav]
    int pav = 0, nav = 0;
    ll val;
} node;


node t1, t2, t3, t4, t5;

void print(node *u) {
    cout << "node " << u->val;
    cout << " l: " << (u->l == NULL ? -1 : u->l->val);
    cout << " r: " << (u->r == NULL ? -1 : u->r->val);
    cout << " p: " << (u->p == NULL ? -1 : u->p->val);
    cout << " pp: " << (u->pp == NULL ? -1 : u->pp->val);
    cout << " pav: " << weights[(u->pav)];
    cout << endl;
}

void printAllNodes() {
    print(&t1); print(&t2); print(&t3); print(&t4); print(&t5); cout << endl;
}

//update data (min/max/sum edge/node usw), called iff new childs
void update(node *v) {
    //set v->pav based on operation
    v->pav = v->nav;
    if(v->l != NULL && weights[v->pav] > weights[v->l->pav]) v->pav = v->l->pav;
    if(v->r != NULL && weights[v->pav] > weights[v->r->pav]) v->pav = v->r->pav;
}

//normalize a node if indicated
void normalize(node *u) {
    if(!u->flip) return;

    //swap childs
    node *t = u->l;
    u->l = u->r;
    u->r = t;

    //update revert indicator
    if(u->l != NULL) u->l->flip = !u->l->flip;
    if(u->r != NULL) u->r->flip = !u->r->flip;

    u->flip = false;
}

//rotate tree such that x moves one layer up (assumption: parent exists)
void rotate(node *u) {
    node *up = u->p, *upp = up->p;

    //Case 1.1
    if(up->l == u) {
        node *B = u->r;
        u->r = up, u->p = up->p;
        up->p = u, up->l = B;
        if(B != NULL) B->p = up;
    }
    //CASE 1.2
    else {
        node *B = u->l;
        u->l = up, u->p = up->p;
        up->r = B, up->p = u;
        if(B != NULL) B->p = up;
    }

    //update upp's pointers, if exists
    if(upp != NULL) {
        if(upp->l == up) upp->l = u;
        else upp->r = u;
    }

    //update path aggr. values
    update(up);
    update(u);
}

//rotate pref path in aux tree such that v is root
void splay(node *v) {
    //if v is already root of aux tree, normalize and return
    if(v->p == NULL) {
        normalize(v);
        return;
    };

    node *u = v, *up = NULL, *upp = NULL;
    while(u->p != NULL) {
        up = u->p, upp = up->p;

        //normalize all necessary components before rotating
        if(upp != NULL) normalize(upp);
        normalize(up);
        normalize(u);

        //if at least 2 layers above
        if(upp != NULL) {
            //zig-zig
            if((up->l == u) == (upp->l == up)) rotate(up);
            //zig-zag
            else rotate(u);
        }
        //last step of current rotation
        rotate(u);
    }

    //set old root
    node *r = (upp == NULL ? up : upp);

    //update pointers (attach aux tree of w to v)
    v->p = NULL;
    v->pp = r->pp;
    r->pp = NULL;
}

//restructures the three containing v based on new pref. path
node *access(node *v) {
    //make v the root of the aux. tree
    splay(v);

    //v is beginning of preffered path => remove preffered child
    if(v->r != NULL) {
        v->r->pp = v;
        v->r->p = NULL;
    }
    v->r = NULL;

    node *u = v;
    //while not at root of represented tree
    while(u->pp != NULL) {
        //get node curr. aux. tree is connected to
        node *w = u->pp;
        //make node to root of new aux. tree
        splay(w);
        //switch w's pref. chil
        if(w->r != NULL) {
            w->r->pp = w;
            w->r->p = NULL;
        }
        w->r = u;
        u->p = w;
        u->pp = NULL;
        u=w;
    }

    //one more splay of v to make v he root of the new aux. tree
    splay(v);
    //update v if there was no update process at all (i.e. v was last access call)
    update(v);

    //return first node of new pref. path in the old highest aux tree
    return u;
}

//makes v the root of its repr. tree
void makeRoot(node *v) {
    //update aux trees
    access(v);
    //rotate childs (make v highest element in repr. tree)
    v->flip = !v->flip;
}

node *findRoot(node *v) {
    //update aux trees
    access(v);
    //find root(by constraints most left node (highest node))
    while(v->l != NULL) v = v->l;
    //make r root of aux tree s.t. will be found faster next time
    access(v);

    return v;
}

//cut subtree with node v
void cut(node *v) {
    //update aux trees
    access(v);

    //to cut everything above v just remove its left child, update path-pointer
    if(v->l != NULL) {
        v->l->p = NULL;
        v->l->pp = v->pp;
        v->pp = NULL;
        v->l = NULL;
    }
}

//cut edge between u and v (if exists) [makes u root as well as v]
void cut(node *u, node *v) {
    //make u root and access v
    makeRoot(u);
    access(v);

    //if there was no edge between u and v, return
    if(v->l != u) return;
    //else cut nodes
    v->l = NULL;
    u->p = NULL;
}

//(links u to v (makes u root)
void link(node *u, node *v) {
    //make u root, access v
    makeRoot(u);
    access(v);
    //set pointer
    u->pp = v;
    //update aux trees
    access(u);
}

node *lca(node *u, node *v) {
    //make u root of aux trees
    access(u);
    //lca is the first node of the path (v to root of tree) which was in the old root aux. tree
    return access(v);
}

//calculates the path aggr. value between node v and u (makes v root or repr. tree)
int calcPav(node *v, node *u) {
    makeRoot(v);
    access(u);
    return u->pav;
}


//fenwick tree
int lsbs(int x) {
    return (x & (-x));
}

const int MAX_FT_SIZE = 200042;
ll ft[MAX_FT_SIZE];

ll getV(int i) {
	ll res = ft[i];
	while((i -= lsbs(i)) > 0) {
		res += ft[i];
	}
	return res;
}

void setV(int i, ll value) {
	while(i < MAX_FT_SIZE) {
		ft[i] += value;
		i += lsbs(i);
	}
}

ll getRange(int l, int r) {
	return getV(r) - getV(l - 1);
}

vector<pii> edges;
vector<query> queries;
vector<node> graph;
vector<int> result;
void solve() {
    int n,m,q; cin >> n >> m >> q;

    graph = vector<node>(n+m);
    queries = vector<query>();
    edges = vector<pii>();
    result = vector<int>(q);
    weights = vector<int>(n+m, MAX_INT);
    memset(ft, 0, sizeof(ft));

    for(int i = 0; i < n; i++) {
        graph[i].val = i;
        graph[i].nav = i;
    }

    for(int i = 0; i < m; i++) {
        int u,v; cin >> u >> v;
        edges.pb({u-1, v-1});
        weights[n+i] = i;
        graph[n+i].nav = n+i;
    }

    for(int i = 0; i < q; i++) {
        int l,r; cin >> l >> r;
        queries.pb((query){l-1, r-1, i});
    }
    sort(queries.begin(), queries.end(), [](const query &p1, const query &p2) {
        return p1.r < p2.r;
    });

    int end = 0;
    for(query &qq: queries) {
        for(int i = end; i <= qq.r; i++) {
            int u = edges[i].first, v = edges[i].second;
            if(edges[i].first != edges[i].second) {
                    // cout << "edge: (" << (edges[i].first+1) << "," << (edges[i].second+1) << ")" << endl;
                if(findRoot(&graph[u]) == findRoot(&graph[v])) {
                        // cout << "m" << endl;
                    int ei = calcPav(&graph[u], &graph[v]);
                    // cout << "edge: " << edges[ei-n].first << "," << edges[ei-n].second << endl;
                    int eil1 = edges[ei-n].first, eil2 = edges[ei-n].second;
                    cut(&graph[eil1], &graph[ei]), cut(&graph[eil2], &graph[ei]);
                            // cout << "n" << endl;
                    setV(ei-n+1, -1);
                            // cout << "o" << endl;
                }

                        // cout << "p" << endl;
                        // cout << (n+i) << " < " << (n+m) << endl;
                link(&graph[u], &graph[n+i]), link(&graph[v], &graph[n+i]);
                        // cout << "q" << endl;
                setV(i+1, 1);
                        // cout << "r" << endl;
            }
        }
        end = qq.r + 1;

        // cout << "y" << endl;
        int ce = getRange(qq.l+1, qq.r+1);
        // cout << "z" << endl;
        result[qq.idx] = (n - ce);
    }

    for(int i = 0; i < q; i++) cout << result[i] << endl;
}

int main() {
	//USE FOR FAST IO
	ios::sync_with_stdio(false);
    int T; cin >> T;
    while(T--) {
	       solve();
    }
    return 0;
}
