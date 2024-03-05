#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vi vector<ll>
#define vl vector<ll>
#define pii pair<ll, ll>
#define pll pair<ll, ll>
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define fi first
#define se second

#define FOR(i, a, b) for (ll i = (a); i <= (b); ++i)
#define REP(i, n) for (ll i = 0; i < (n); ++i)
#define REPN(i, n) for (ll i = 1; i <= (n); ++i)
#define REPR(i, n) for (ll i = (n)-1; i >= 0; --i)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define SORT(v) sort(v.begin(), v.end())

#define py cout << "YES" << endl;
#define pn cout << "NO" << endl;
#define ps cout << " " << endl;
#define r return;

const ll MOD = 1e9 + 7;
const ll INF = 1e9;

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "{ ";
    for (const T &x : v)
        os << x << " ";
    os << "}";
    return os;
}

// ll dp[10000][10000];

// ll knapsack(vi &value, vi &weight, ll index, ll maxweight)
// {
//     if (maxweight == 0)
//         return 0;
//     if (index < 0)
//         return 0;
//     if (dp[index][maxweight] != -1)
//         return dp[index][maxweight];
//     ll ans = knapsack(value, weight, index - 1, maxweight);
//     if (maxweight - weight[index] >= 0)
//         ans = max(ans, knapsack(value, weight, index - 1, maxweight - weight[index]) + value[index]);

//     return dp[index][maxweight] = ans;
// }

// ll dp2[10000][10000];

// ll knapsack2(vi &value, vi &weight, ll index, ll val_left, ll capacity)
// {
//     if (index < 0)
//         return INF;
//     if (val_left <= 0)
//         return 0;
//     if (dp[index][val_left] != -1)
//         return dp[index][val_left];

//     ll ans = knapsack3(value, weight, index - 1, val_left, capacity); // NOT CHOOSE

//     if (val_left - value[index] >= 0)
//     {
//         ans = min(ans, knapsack3(value, weight, index - 1, val_left - value[index], capacity));
//     }

//     if (ans == INF)
//     {
//         return INF;
//     }

//     if (ans <= capacity)
//     {
//         if (og_wt == -1)
//         {
//             og_wt = weight[index];
//             og_ans = value[index];
//         }
//         else
//         {
//             og_wt += weight[index];
//             og_ans += value[index];
//         }
//     }

//     return dp[index][val_left] = ans;
// }

bool solved = false;
ll og_wt = -1;
ll og_ans = -1;

void og_solve(vi &value, vi &weight, ll n, ll capacity)
{
    if (solved)
    {
        // cout << og_ans << endl;
        // cout << og_wt << endl;
        return;
    }
    cout << "Original Instance: " << endl;
    ll max_v = *max_element(value.begin(), value.end());

    vector<vector<ll>> dp(n + 1, vector<ll>(max_v * n + 1, INF));
    vector<vector<bool>> isSelected(n + 1, vector<bool>(max_v * n + 1, false));
    dp[0][0] = 0;
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j <= max_v * n; j++)
        {
            if (j < value[i])
            {
                dp[i + 1][j] = dp[i][j];
                isSelected[i + 1][j] = false;
                // cout << "1" << endl;
            }
            else
            {
                if (dp[i][j] < dp[i][j - value[i]] + weight[i])
                {
                    dp[i + 1][j] = dp[i][j];
                    isSelected[i + 1][j] = false;
                    // cout << "2 " << i << " " << j << endl;
                }
                else
                {
                    // cout << "3 " << i << " " << j << endl;
                    // cout << dp[i][j] << " " << dp[i][j - value_r[i]] + weight[i] << endl;
                    dp[i + 1][j] = dp[i][j - value[i]] + weight[i];
                    isSelected[i + 1][j] = true;
                }
            }
        }
    }

    // for (ll i = 0; i <= n; i++)
    // {
    //     for (ll j = 0; j <= max_v * n; j++)
    //     {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    og_ans = 0;
    for (ll i = 0; i <= max_v * n; i++)
    {
        if (dp[n][i] <= capacity)
        {
            og_ans = i;
        }
    }
    ll ans = og_ans;
    cout << "Answer: " << og_ans << endl;
    og_wt = 0;
    vi indices;
    for (ll i = n; i > 0; i--)
    {
        if (isSelected[i][og_ans])
        {
            // cout << i << " ";
            indices.pb(i);
            og_wt += weight[i - 1];
            og_ans -= value[i - 1];
        }
    }
    // cout << endl;
    cout << "Indices: ";
    for (auto i : indices)
        cout << i << " ";
    cout << endl;
    cout << "Used Weight: " << og_wt << endl
         << endl
         << endl;
    cout << "----------------------------------------------------------------------------"
         << endl
         << endl
         << endl;
    og_ans = ans;
    solved = true;
}

void solve_knapsack(vi value, vi weight, ll n, ll capacity, double epsilon)
{
    vi value_r(n);
    ll max_v = *max_element(value.begin(), value.end());

    cout << "Rounded Instance with Eps: " << epsilon << endl;
    double theta = (epsilon * (double)max_v) / (double)(2 * n);

    cout << "Theta: " << setprecision(16) << theta << endl;

    for (ll i = 0; i < n; i++)
    {
        value_r[i] = (ceil)((double)value[i] / (double)theta);
        // value[i] = (ceil)((double)value_r[i] * theta);
        if (value[i] == max_v)
        {
            value_r[i] += 1;
        }
    }

    ll max_vr = *max_element(value.begin(), value.end());

    ll t = *max_element(value_r.begin(), value_r.end());
    max_vr = t;

    vector<vector<ll>> dp(n + 1, vector<ll>(max_vr * n + 1, INF));
    vector<vector<bool>> isSelected(n + 1, vector<bool>(max_vr * n + 1, false));
    dp[0][0] = 0;
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j <= max_vr * n; j++)
        {
            if (j < value_r[i])
            {
                dp[i + 1][j] = dp[i][j];
                isSelected[i + 1][j] = false;
                // cout << "1" << endl;
            }
            else
            {
                if (dp[i][j] < dp[i][j - value_r[i]] + weight[i])
                {
                    dp[i + 1][j] = dp[i][j];
                    isSelected[i + 1][j] = false;
                    // cout << "2 " << i << " " << j << endl;
                }
                else
                {
                    // cout << "3 " << i << " " << j << endl;
                    // cout << dp[i][j] << " " << dp[i][j - value_r[i]] + weight[i] << endl;
                    dp[i + 1][j] = dp[i][j - value_r[i]] + weight[i];
                    isSelected[i + 1][j] = true;
                }
            }
        }
    }

    ll ans = 0;
    for (ll i = 0; i <= max_vr * n; i++)
    {
        if (dp[n][i] <= capacity)
        {
            ans = i;
        }
    }

    cout << "Answer of reduced instance: " << ans << endl;
    double x = ans;
    double ans_og = x * theta;
    cout << "Answer of reduced instance multiplied by theta: " << ans_og << endl;

    ll takewt = 0;
    ll og_val = 0;
    cout << "Indices: ";
    for (ll i = n; i > 0; i--)
    {
        if (isSelected[i][ans])
        {
            cout << i << " ";
            takewt += weight[i - 1];
            ans -= value_r[i - 1];
            og_val += value[i - 1];
        }
    }
    cout << endl;
    cout << "Answer of original instance (rounded up): " << og_val << endl;
    cout << "Used Weight: " << takewt << endl;
    // cout << og_ans << endl;
    cout << "Ratio: ";
    if (og_val == og_ans)
    {
        cout << "1.0" << endl;
    }
    else
    {
        double ratio = (double)og_ans / (double)og_val;
        cout << ratio << endl;
    }
    cout << endl
         << endl;
}

void solve(double epsilon)
{
    // memset(dp, -1, sizeof(dp));
    // memset(dp2, INF, sizeof(dp2));
    freopen("in2.txt", "r", stdin);
    // epsilon = 0.5;

    ll capacity;
    ll n;
    cin >> n;
    cin >> capacity;
    vi value(n);
    vi value_r(n);
    vi weight(n);
    REP(i, n)
    {
        cin >> value[i] >> weight[i];
    }

    og_solve(value, weight, n, capacity);
    solve_knapsack(value, weight, n, capacity, epsilon);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // ll t = 1;
    freopen("out_in2.txt", "w", stdout);
    vector<double> eps = {0.5, 0.2, 0.1, 0.05};

    for (auto i : eps)
    {
        solve(i);
        cout << "----------------------------------------------------------------------------" << endl
             << endl
             << endl;
    }

    // while (t--)
    // {
    //     solve(0.5);
    // }
    return 0;
}