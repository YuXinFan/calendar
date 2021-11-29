def bitCount(n):
    count = 0;
    while (n):
        count += n & 1;
        n >>= 1;
    return count;
l = []
for i in range(1,1014560):
    j = (i+bitCount(i))%8
    if (j == 0):
        k = (i-bitCount(i))%9+1
        l.append(k)
    else:
        l.append(-1)
print(l)
