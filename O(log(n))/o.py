el = list(range(1, 1000001))

left = 0
right = len(el) - 1
mid = (len(el) - 1) // 2
target = 7980

# O(n)
#for idx, e in enumerate(el):
#    if e == target:
#        print(f"Trovato! indice: {idx}")
#        break
# [Done] exited with code=0 in 0.532 seconds


# O(log(n))
while left <= right:
    mid = (left + right) // 2
    if el[mid] == target:
        print(f"Trovato!, indice: {mid}")
        break
    elif el[mid] < target:
        left = mid + 1
    elif el[mid] > target:
        right = mid - 1
# [Done] exited with code=0 in 0.292 seconds