#include<bits/stdc++.h>

using namespace std;


// Indexing Starts from 1
template <typename T>
class SegTree
{
private:
    vector<T> arr;
    vector<T> tree;
    int n;
    T identity;

    T combine(T a, T b)
    {
        return a + b;
    }

    void init(int node, int begin, int end)
    {
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

    void update(int node, int b, int e, int i, T newValue)
    {
        if ((i > e) || (i < b))
        {
            return;
        }

        if ((b == i) && (e == i))
        {
            tree[node] = newValue;
            return;
        }

        int left = 2 * node;
        int right = (2 * node) + 1;
        int mid = (b + e) / 2;

        update(left, b, mid, i, newValue);
        update(right, mid + 1, e, i, newValue);

        tree[node] = combine(tree[left], tree[right]);
    }

public:
    SegTree(const vector<T> &a, T id = 0) : arr(a), n(a.size() - 1)
    {
        identity = id;
        tree.resize(4 * n, identity);
        init(1, 1, n);
    }

    T query(int i, int j)
    {
        return query(1, 1, n, i, j);
    }

    void update(int i, T newValue)
    {
        update(1, 1, n, i, newValue);
    }
};

int main()
{
    int n;
    cin >> n;

    vector<int> v(n + 1);
    for(int i = 1; i <= n; i++) cin >> v[i];
}