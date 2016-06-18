typedef struct node {
    //left child, right child, pref. path parent, aux parent
    node *l = NULL, *r=NULL, *p = NULL, *pp=NULL;
    //indicates whether tree needs to be flipped (childs swaped)
    bool flip = false;
    //path aggr values: for whole aux. path [pav], for node [nav]
    ll pav = 0, nav = 1;
    ll val;
} node;

//update data (min/max/sum edge/node usw), called iff new childs
void update(node *v) {
    //set v->pav based on operation
    v->pav = v->nav + (v->l != NULL ? v->l->pav : 0) + (v->r != NULL ? v->r->pav: 0);
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
ll calcPav(node *v, node *u) {
    makeRoot(v);
    access(u);
    return u->pav;
}
