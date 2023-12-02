lines_count = 100

ans = 0
for i in range(lines_count):
    _ , post = input().split(":")
    ok = True
    for round in post.split(";"):
        r, g, b = 0, 0, 0
        for item in round.split(","):
            _, num, col = item.split(" ")
            num = int(num)
            if (col == "red"): r = num
            elif(col == "green"): g = num
            else: b = num
        
        ok &= (r <= 12 and g <= 13 and b <= 14)
    
    if (ok):
        ans += i + 1

print(ans)
