#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    long long K;
    int a, b;
    cin >> K >> a >> b;

    int Z[4][4], A[4][4];
    for(int i=1;i<=3;++i)
        for(int j=1;j<=3;++j)
            cin >> Z[i][j];

    for(int i=1;i<=3;++i)
        for(int j=1;j<=3;++j)
            cin >> A[i][j];

    auto get_winner = [](int x, int y) {
        if(x == y) return 0;
        if((x==1 && y==3) || (x==2 && y==1) || (x==3 && y==2))
            return 1;
        return 2;
    };

    pair<long long, pair<long long,long long>> seen[4][4];
    for(int i=1;i<=3;++i)
        for(int j=1;j<=3;++j)
            seen[i][j] = {-1, {0,0}};

    long long round = 0;
    long long z_wins = 0, a_wins = 0;
    int z = a, aa = b;

    while(round < K) {
        if(seen[z][aa].first != -1) {
            long long prev_round = seen[z][aa].first;
            long long cycle_len = round - prev_round;
            long long z_prev = seen[z][aa].second.first;
            long long a_prev = seen[z][aa].second.second;

            long long z_cycle = z_wins - z_prev;
            long long a_cycle = a_wins - a_prev;

            long long remaining = K - round;
            long long cycles = remaining / cycle_len;

            z_wins += z_cycle * cycles;
            a_wins += a_cycle * cycles;
            round += cycles * cycle_len;

            if(round >= K) break;
        }

        seen[z][aa] = {round, {z_wins, a_wins}};

        int winner = get_winner(z, aa);
        if(winner==1) z_wins++;
        else if(winner==2) a_wins++;

        int next_z = Z[z][aa];
        int next_a = A[z][aa];
        z = next_z;
        aa = next_a;
        round++;
    }

    cout << z_wins << " " << a_wins << endl;
    return 0;
}