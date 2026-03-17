def counting(arr):
    max_v = max(arr)
    
    count = [0] * (max_v + 1)
    for x in arr:
        count[x] += 1
    
    sorted_arr = []
    for i in range(len(count)):
        for _ in range(count[i]):
            sorted_arr.append(i)
    
    return sorted_arr

arr = [2, 5, 3, 0, 2, 3, 0, 3]
print(counting(arr))