lines_count = 100

ans = 0
for i in range(lines_count):
    _ , post = input().split(":")
    ok = True
    max_r, max_g, max_b = 0, 0, 0
    for round in post.split(";"):
        r, g, b = 0, 0, 0
        for item in round.split(","):
            _, num, col = item.split(" ")
            num = int(num)
            if (col == "red"): r = num
            elif(col == "green"): g = num
            else: b = num
        
        max_r, max_g, max_b = max(max_r, r), max(max_g, g), max(max_b, b)
    
    ans += max_r * max_g * max_b
    

print(ans)
