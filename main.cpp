#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
const int N = 1e6 + 10;
int n, q, a[N];
struct node
{
    int l, r, sum;
    int lazy;
};
struct segment_tree
{
    node t[N << 2];
    void build(int k, int l, int r)
    {
        t[k].l = l;
        t[k].r = r;
        if(l == r)
        {
            t[k].sum = a[l];
            return;
        }
        int ch = k << 1;
        int mid = (l + r) >> 1;
        build(ch, l, mid);
        build(ch + 1, mid + 1, r);
        t[k].sum = t[ch].sum + t[ch + 1].sum ;
    }
    void push_down(int k, int l, int r)
    {
        if(t[k].lazy != 0)
        {
            int mid = l + r >> 1;
            t[k << 1].lazy += t[k].lazy ;
            t[k << 1 | 1].lazy += t[k].lazy ;
            t[k << 1].sum += t[k].lazy * (mid - l + 1);
            t[k << 1 | 1].sum += t[k].lazy * (r - mid);
            t[k].lazy = 0;
        }
    }
    void change(int k, int l, int r, int x)
    {
        if(l <= t[k].l && t[k].r <= r)
        {
            t[k].sum += (t[k].r - t[k].l + 1) * x;
            t[k].lazy += x;
            return ;
        }
        push_down(k, t[k].l, t[k].r );
        int mid = (t[k].l + t[k].r ) >> 1;
        if(l <= mid)
            change(k << 1, l, r, x);
        if(r > mid)
            change(k << 1 | 1, l, r, x);
        t[k].sum = t[k * 2].sum + t[k * 2 + 1].sum;
    }
    int query(int k, int l, int r)
    {
        if (t[k].l >= l && t[k].r <= r)
            return t[k].sum;
        push_down(k, l, r);
        int res = 0;
        int mid = (t[k].l + t[k].r) >> 1;
        if(l <= mid)
            res += query(k << 1, l, r);
        if(r > mid)
            res += query(k << 1 | 1, l, r);
        return res;
    }
} st;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> q;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    st.build(1, 1, n);
    int op, x, l, r;
    while(q-- && cin >> op)
    {
        if(op == 1)
        {
            cin >> l >> r >> x;
            st.change(1, l, r, x);
        }
        else
        {
            cin >> l >> r;
            cout << st.query(1, l, r) << "\n";
        }
    }
    return 0;
}
