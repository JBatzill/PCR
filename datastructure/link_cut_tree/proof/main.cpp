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

typedef struct node {
    node *l = NULL, *r=NULL, *p = NULL, *pp=NULL;
    ll val;
} node;

//rotate pref path in aux tree such that v is root
void splay(node *v) {
    //if v is already root of aux tree, return
    if(v->p == NULL) return;

    node *u = v, *up = NULL, *upp = NULL;
    while(u->p != NULL) {
        up = u->p;
        upp = u->p->p;

        //CASE 1
        if(upp == NULL) {
            //CASE 1.1
            if(up->l == u) {
                node *B = u->r;
                u->r = up, u->p = up->p;
                up->p = u, up->l = B;
            }
            //CASE 2.1
            else {
                node *B = u->l;
                u->l = up, u->p = up->p;
                up->r = B, up->p = u;
            }
        } else {
            //CASE 2.1
            if(up->l == u && upp->l == up) {
                node *B = u->r, *C = up->r;
                u->r = up, u->p = upp->p;
                up->l = B, up->r = upp, up->p = u;
                upp->l = C, upp->p = up;
            }
            //CASE 2.2
            else if(up->r == u && upp->r == up) {
                node *B = up->l, *C = u->l;
                u->l = up, u->p = upp->p;
                up->l = upp, up->r = C, up->p = u;
                upp->r = B, upp->p = up;
            }
            //CASE 3.1
            else if(up->r == u && upp->l == up) {
                node *B = u->l, *C = u->r;
                u->l = up, u->r = upp, u->p = upp->p;
                up->r = B, up->p = u;
                upp->l = C, upp->p = u;
            }
            //CASE 3.2
            else {
                node *B = u->l, *C = u->r;
                u->l = upp, u->r = up, u->p = upp->p;
                up->l = C, up->p = u;
                upp->r = B, upp->p = u;
            }
        }
    }

    //set old root
    node *r = (upp == NULL ? up : upp);

    //update pointers (attach aux tree of w to v)
    v->p = NULL;
    v->pp = r->pp;
    r->pp = NULL;
}

//restructures the three containing v based on new pref. path
void access(node *v) {
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

//(v and w must be roots, link v to w)
void link(node *v, node *w) {
    //update aux trees
    access(v);
    access(w);

    //set  (both roots, so no subtrees on the left)
    v->l = w;
    w->p = v;
}

void solve() {
    node t1, t2, t3, t4;

    t1.val = 1, t2.val = 2, t3.val = 3, t4.val = 4;

    link(&t1, &t2);
    link(&t3, findRoot(&t2));

    cout << "root of t3 " << (*findRoot(&t3)).val << endl;
    cout << "root of t4 " << (*findRoot(&t4)).val << endl;

    link(findRoot(&t1), &t4);

    cout << "root of t1 " << (*findRoot(&t1)).val << endl;
}

int main() {
	//USE FOR FAST IO
	ios::sync_with_stdio(false);
	solve();
	return 0;
}
