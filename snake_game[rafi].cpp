#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

#define sync() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ll long long
#define pb push_back
#define ff first
#define ss second
#define dd double
#define mkp make_pair
#define nl endl
#define imx pow(2,62) - 1
#define mod 1000000007
#define all(v) v.begin(),v.end()
#define pf printf
#define sf(x) scanf("%lld", &x)
#define db(x) cout << #x << ": " << x << nl
#define run(i, n) for(i = 1; i <= n; i++)

#define mem(a,v) memset(a,v,sizeof(a))
#define gcd(a,b) __gcd(a,b)
#define lcm(a,b) (a*(b/gcd(a,b)))

typedef vector < ll > VI;
typedef pair < ll, ll> PLL;
typedef vector < PLL > VP;
typedef stack < ll > STK;
typedef map < ll, ll > MLL;
typedef map < ll, bool > MLB;
typedef set < ll > ST;
typedef queue < ll > QU;
typedef priority_queue < ll > GPQ;
typedef priority_queue < ll, VI, greater < ll > > LPQ;

const double PI = acos(-1);
const double eps = 1e-9;

ll grid_height, grid_width, fruit_x, fruit_y, head_x, head_y, score;
bool gameover;

ll tail_x[110], tail_y[110], tail_len;

enum direction {
    Left = 1, Right, Up, Down, Pause
};
direction dir, before_pause;

/// Visualized the grid like a 2D array(1 based indexing)...
/// x = height, y = width

void validate(ll &row, ll &col)
{
    if(row == 1) row++;
    if(col == 1) col++;

    if(row == grid_height) row--;
    if(col == grid_width) col--;
}

void initialize()
{
    grid_height = 25;
    grid_width = 70;

    fruit_x = rand() % grid_height;
    fruit_y = rand() % grid_width;
    validate(fruit_x, fruit_y);

    head_x = grid_height >> 1;
    head_y = grid_width >> 1;
    validate(head_x, head_y);

    gameover = 0;
    score = 0;
    tail_len = 0;
}

void draw()
{
    system("cls");
    ll i, j, k;
    cout << "Score: " << score << nl;
    for(i = 1; i <= grid_width; i++) cout << "#";
    cout << nl;

    for(j = 1; j <= grid_height - 2; j++) /// -> x
    {
        cout << "#";

        for(k = 2; k <= grid_width - 1; k++) /// -> y
        {
            bool tail_matched = 0;
            for(i = 1; i <= tail_len; i++)
            {
                if(j == tail_x[i] && k == tail_y[i]){
                    cout << "o"; tail_matched = 1;
                    break;
                }
            }

            if(tail_matched) continue;
            if(j == head_x && k == head_y)
                cout << "O";
            else if(j == fruit_x && k == fruit_y)
                cout << "F";
            else cout << " ";
        }

        cout << "#\n";
    }

    for(i = 1; i <= grid_width; i++) cout << "#";
    cout << nl;
}

void movement()
{
    if(_kbhit())
    {
        char c;
        c = getch();

        if(c == 'w') dir = Up;
        else if(c == 'a') dir = Left;
        else if(c == 'd') dir = Right;
        else if(c == 's') dir = Down;
        else if(c == 'p') {
            before_pause = dir;
            dir = Pause;
        }
        else if(c == 'r') dir = before_pause;

    }
}

void backend()
{
    if(dir == Pause) return;
    /// tail growing
    ll prev_x = head_x;
    ll prev_y = head_y;

    for(ll i = 1; i <= tail_len; i++)
    {
        ll curr_x = tail_x[i];
        ll curr_y = tail_y[i];

        tail_x[i] = prev_x;
        tail_y[i] = prev_y;

        prev_x = curr_x;
        prev_y = curr_y;

    }

    if(dir == Up) head_x--;
    else if(dir == Down) head_x++;
    else if(dir == Left) head_y--;
    else if(dir == Right) head_y++;

    for(ll i = 1; i <= tail_len; i++)
    {
        if(head_x == tail_x[i] && head_y == tail_y[i])
        {
            gameover = 1;
            return;
        }
    }
    if(head_x <= 1 || head_x >= grid_height || head_y <= 1 || head_y >= grid_width) gameover = 1;
    else if(head_x == fruit_x && head_y == fruit_y)
    {
        score += 10;
        fruit_x = rand() % grid_height;
        fruit_y = rand() % grid_width;
        validate(fruit_x, fruit_y);
        tail_len++;
    }

}

int main()
{
//    sync();
    ll i, j, k, l, p, q, r, x, y(0), z = 0, n, m, c(0), t, h, mn = imx, mx = 0;
    string s, ss;


    initialize();

    while(!gameover)
    {
        draw();
        movement();
        backend();

    }

}
