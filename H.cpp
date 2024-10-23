//
// Created by XXS on 2024/10/23.
//

#include<iostream>
#include <vector>
using namespace std;
const int maxn = 200233;

struct Splay {
    int ch[maxn][2], fa[maxn], tag[maxn];

    void clear(int x) { ch[x][0] = ch[x][1] = fa[x] = tag[x] = 0; }

    int getch(int x) { return ch[fa[x]][1] == x; }

    int isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }

    void pushdown(int x) {
        if (tag[x]) {
            if (ch[x][0])
                swap(ch[ch[x][0]][0], ch[ch[x][0]][1]), tag[ch[x][0]] ^= 1;
            if (ch[x][1])
                swap(ch[ch[x][1]][0], ch[ch[x][1]][1]), tag[ch[x][1]] ^= 1;
            tag[x] = 0;
        }
    }

    void update(int x) {
        if (!isroot(x))
            update(fa[x]);
        pushdown(x);
    }

    void rotate(int x) {
        int y = fa[x], z = fa[y], chx = getch(x), chy = getch(y);
        fa[x] = z;
        if (!isroot(y))
            ch[z][chy] = x;
        ch[y][chx] = ch[x][chx ^ 1];
        fa[ch[x][chx ^ 1]] = y;
        ch[x][chx ^ 1] = y;
        fa[y] = x;
    }

    void splay(int x) {
        update(x);
        for (int f = fa[x]; f = fa[x], !isroot(x); rotate(x))
            if (!isroot(f))
                rotate(getch(x) == getch(f) ? f : x);
    }

    void access(int x) {
        for (int f = 0; x; f = x, x = fa[x])
            splay(x), ch[x][1] = f;
    }

    void makeroot(int x) {
        access(x);
        splay(x);
        swap(ch[x][0], ch[x][1]);
        tag[x] ^= 1;
    }

    int find(int x) {
        access(x);
        splay(x);
        while (ch[x][0])
            x = ch[x][0];
        splay(x);
        return x;
    }
} st;

void solve() {
    int n = read(), q = read();
    vector<int> p(n + 1);
    pmr::vector<bool> vis(n + 1, false);
    for (int i = 1; i <= n; i++) {
        p[i] = read();
    }
    for (int qi = 0; qi < q; qi++) {
        int opi = read(), u = read(), v = read();
        if (opi == 1) {
            if (st.find(u) != st.find(v)) {
                st.makeroot(u), st.fa[u] = v;
            }
            vis[u] = vis[v] = 1;
        }
        if (opi == 2) {
            st.makeroot(u);
            st.access(v);
            st.splay(v);
            if (st.ch[v][0] == u && !st.ch[u][1])
                st.ch[v][0] = st.fa[u] = 0;
            vis[u] = vis[v] = 1;
        }
        if (opi == 3) {
            vector<int> s;
            for (int i = 1; i <= n; i++) {
                if (vis[i] && st.find(u) == st.find(i)) {
                    s.pb(p[i]);
                }
            }
            sort(s.begin(), s.end());
            if (s.size() < v) {
                write(0);
                putchar('\n');
            } else {
                write(s[v - 1]);
                putchar('\n');
            }
        }
    }
}