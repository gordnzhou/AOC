lines_count = 193

ans = 0
for i in range(lines_count):
    _, cards = input().split(":")
    winning, hand = cards.split("|")
    winning = winning.split(" ")
    hand = hand.split(" ")
    winning = [int(c) for c in filter(lambda x: x != '', winning)]
    hand = [int(c) for c in filter(lambda x: x != '', hand)]
    n = 0
    for c in hand:
        if c in winning:
            n += 1
    
    if (n > 0):
        ans += pow(2, n - 1)

print(ans)
