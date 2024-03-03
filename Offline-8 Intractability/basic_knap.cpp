#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vi vector<int>
#define vl vector<ll>
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define fi first
#define se second

#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define REPN(i, n) for (int i = 1; i <= (n); ++i)
#define REPR(i, n) for (int i = (n)-1; i >= 0; --i)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define SORT(v) sort(v.begin(), v.end())

#define py cout << "YES" << endl;
#define pn cout << "NO" << endl;
#define ps cout << " " << endl;
#define r return;

const int MOD = 1e9 + 7;
const int INF = 1e9;

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "{ ";
    for (const T &x : v)
        os << x << " ";
    os << "}";
    return os;
}

int dp[10000][10000];

int knapsack(vi &value, vi &weigth, int index, int maxWeigth)
{
    if (maxWeigth == 0)
        return 0;
    if (index < 0)
        return 0;
    if (dp[index][maxWeigth] != -1)
        return dp[index][maxWeigth];
    int ans = knapsack(value, weigth, index - 1, maxWeigth);
    if (maxWeigth - weigth[index] >= 0)
        ans = max(ans, knapsack(value, weigth, index - 1, maxWeigth - weigth[index]) + value[index]);

    return dp[index][maxWeigth] = ans;
}

ll dp2[10000][10000];

void solve()
{
    memset(dp, -1, sizeof(dp));
    memset(dp2, INF, sizeof(dp2));
    freopen("in.txt", "r", stdin);

    int capacity;
    int n;
    cin >> n;
    cin >> capacity;
    vi value(n);
    vi weigth(n);
    REP(i, n)
    {
        cin >> value[i] >> weigth[i];
    }

    auto it = max_element(value.begin(), value.end());
    ll max_val = *it;

    cout << max_val << endl;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<=max_val*n;j++)
        {
            if(j<value[i])
            {
                dp2[i+1][j] = dp2[i][j];
            }
            else
            {
                if(dp2[i][j]<dp2[i][j-value[i]]+weigth[i])
                {
                    dp2[i+1][j] = dp2[i][j];
                }
                else
                {
                    dp2[i+1][j] = dp2[i][j-value[i]]+weigth[i];
                }
            }
        }
    }

    cout << "answer: " << knapsack(value, weigth, n, capacity) << endl;

    vi take2;
    int j = capacity;
    for (int i = n; i > 0; i--)
    {
        if (i == 1 && dp[i][j] != -1)
        {
            take2.push_back(1);
        }

        if (dp[i][j] != dp[i - 1][j])
        {
            take2.push_back(i + 1);
            j -= weigth[i];
        }
        if (j < 1)
            break;
    }
    // reverse(take2.begin(), take2.end());
    sort(take2.begin(), take2.end());

    ll used_wt = 0;
    for (auto i : take2)
    {
        used_wt += weigth[i - 1];
    }

    cout << "Used Weigth: " << used_wt << endl;
    cout << "Indices: " << take2;
    cout << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;

    while (t--)
    {
        solve();
    }
    return 0;
}