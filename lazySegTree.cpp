#include<bits/stdc++.h>

using namespace std;

template <typename T>
class LazySegTree
{
private:
    vector<T> arr;
    vector<T> tree;
    vector<T> lazy;
    vector<int> nodes;
    int n;
    T identity;

    T combine(const T &a,const T &b) const
    {
        return min(a, b);
    }

    void init(int node, int begin, int end)
    {
        nodes.emplace_back(node);
        if (begin == end)
        {
            tree[node] = arr[begin];
            return;
        }

        int left = 2 * node;
        int right = (2 * node) + 1;
        int mid = (begin + end) / 2;

        init(left, begin, mid);
        init(right, mid + 1, end);

        tree[node] = combine(tree[left], tree[right]);
    }

    T query(int node, int b, int e, int i, int j)
    {
        push(node, b, e);
        if ((i > e) || (j < b))
        {
            return identity;
        }

        if ((b >= i) && (e <= j))
        {
            return tree[node];
        }

        int left = 2 * node;
        int right = (2 * node) + 1;
        int mid = (b + e) / 2;

        T q1 = query(left, b, mid, i, j);
        T q2 = query(right, mid + 1, e, i, j);

        return combine(q1, q2);
    }

    void push(int node, int b, int e)
    {
        if(lazy[node] == T()) return;
        tree[node] += lazy[node];

        if (b != e)
        {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }

        lazy[node] = T();
    }

    void lazy_update(int node, int b, int e, int i, int j, T newValue)
    {
        push(node, b, e);
        if ((i > e) || (j < b))
        {
            return;
        }

        if ((b >= i) && (e <= j))
        {
            lazy[node] += newValue;
            push(node, b, e);
            return;
        }

        int left = 2 * node;
        int right = (2 * node) + 1;
        int mid = (b + e) / 2;

        lazy_update(left, b, mid, i, j, newValue);
        lazy_update(right, mid + 1, e, i, j, newValue);

        tree[node] = combine(tree[left], tree[right]);
    }

public:
    LazySegTree(const vector<T> &a, T id = 0) : arr(a), n(a.size() - 1)
    {
        identity = id;
        tree.resize(4 * n, identity);
        lazy.resize(4 * n, 0);
        init(1, 1, n);
        sort(nodes.begin(), nodes.end());
    }

    T query(int i, int j)
    {
        return query(1, 1, n, i, j);
    }

    void update(int i, int j, T newValue)
    {
        lazy_update(1, 1, n, i, j, newValue);
    }

    void printTree()
    {
        for(auto &x:nodes) cout << tree[x] << " ";
        cout << endl;
        for(auto &x:nodes) cout << lazy[x] << " ";
        cout << endl;
    }
};

int main()
{
    int n, q;
    cin >> n >> q;

    vector<int> v(n + 1);
    for(int i = 1; i <= n; i++)
    {
        cin >> v[i];
    }

    LazySegTree<int> seg(v, 1e9);

    seg.printTree();

    while(q--)
    {
        int choice;
        cin >> choice;

        if(choice == 1)
        {
            int i, j;
            cin >> i >> j;
            cout << seg.query(i, j) << endl;
            seg.printTree();
        }
        else 
        {
            int i, j, x;
            cin >> i >> j >> x;
            seg.update(i, j, x);
            seg.printTree();
        }
    }
}