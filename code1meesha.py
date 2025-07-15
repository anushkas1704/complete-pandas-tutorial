K, a, b = map(int, input().split())

Z = [[0]*4]
for _ in range(3):
    Z.append([0] + list(map(int, input().split())))

A = [[0]*4]
for _ in range(3):
    A.append([0] + list(map(int, input().split())))

def get_winner(x, y):
    if x == y:
        return 0
    if (x == 1 and y == 3) or (x == 2 and y == 1) or (x == 3 and y == 2):
        return 1
    return 2

seen = [[(-1, 0, 0) for _ in range(4)] for _ in range(4)]

round = 0
z_wins = 0
a_wins = 0
z = a
aa = b

while round < K:
    if seen[z][aa][0] != -1:
        prev_round, z_prev, a_prev = seen[z][aa]
        cycle_len = round - prev_round
        z_cycle = z_wins - z_prev
        a_cycle = a_wins - a_prev
        remaining = K - round
        cycles = remaining // cycle_len
        z_wins += z_cycle * cycles
        a_wins += a_cycle * cycles
        round += cycles * cycle_len
        if round >= K:
            break
    seen[z][aa] = (round, z_wins, a_wins)
    winner = get_winner(z, aa)
    if winner == 1:
        z_wins += 1
    elif winner == 2:
        a_wins += 1
    nz = Z[z][aa]
    na = A[z][aa]
    z, aa = nz, na
    round += 1

print(z_wins, a_wins)
