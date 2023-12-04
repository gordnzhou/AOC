lines_count = 193

points = {}
adj = {}
for i in range(1, lines_count + 1):
    _, cards = input().split(":")
    winning, hand = cards.split("|")
    winning = winning.split(" ")
    hand = hand.split(" ")
    winning = [int(c) for c in filter(lambda x: x != '', winning)]
    hand = [int(c) for c in filter(lambda x: x != '', hand)]
    
    adj[i] = []
    cnt = 0
    for c in hand:
        if c in winning:
            cnt += 1
            adj[i].append(i + cnt)

ans = 0
for i in range(lines_count):
    cur = lines_count - i
    points[cur] = 1
    for a in adj[cur]:
        if (a <= lines_count):
            points[cur] += points[a]
    ans += points[cur]

print(ans)
