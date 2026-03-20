#include<bits/stdc++.h>

using namespace std;

void construct_BIT(vector<int> &a, vector<int> &tree, const int &n)
{
    for(int i = 1; i <= n; i++)
    {
        int j = i + (i & -i);
        if(j <= n)
        {
            tree[j] += tree[i];
        }
    }
}

int pref_sum(vector<int> &tree,int id)
{
    int sm = 0;

    while(id > 0)
    {
        sm += tree[id];
        int j = id & -id;
        id -= j;
    }

    return sm;
}

int query(vector<int> &tree, int l, int r)
{
    return pref_sum(tree, r) - pref_sum(tree, l - 1);
}

void update(int i, int x, int n, vector<int> &tree)
{
    while(i <= n)
    {
        tree[i] = tree[i] + x;
        i = i + (i & -i);
    }
}

int main()
{
    int n;
    cin >> n;

    vector<int> v(n + 1);
    for(int i = 1; i <= n; i++) cin >> v[i];

    vector<int> tree(n + 1);
    for(int i = 1; i <= n; i++) tree[i] = v[i];
    construct_BIT(v, tree, n);

    cout << "Status of Fenwick Tree (idx: value):" << endl;
    for(int i = 1; i <= n; i++)
    {
        cout << i << ":" << tree[i] << " ";
    }
    cout << endl;

    int t;
    cin >> t;

    while(t--)
    {
        int choice;
        cin >> choice;

        if(choice == 1)
        {
            int begin, end;
            cin >> begin >> end;

            cout << "Query: Sum=" << query(tree, begin, end) << endl;
        }
        else if(choice == 2)
        {
            int index, newValue;
            cin >> index >> newValue;

            update(index, newValue, n, tree);
            cout << "Updated tree:" << endl;

            for(int i = 1; i <= n; i++)
            {
                cout << i << ":" << tree[i] << " ";
            }
            cout << endl;
        }
    }
}