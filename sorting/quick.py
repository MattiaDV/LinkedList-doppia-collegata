def quick_sort(arr):
    if len(arr) <= 1:
        return arr

    mid = (len(arr) - 1) // 2
    left = []
    right = []
    middle = []
    i = 0
    pivot = arr[mid]
    while i < len(arr):
        if arr[i] < pivot:
            left.append(arr[i])
        elif arr[i] == pivot:
            middle.append(arr[i])
        else:
            right.append(arr[i])
        i += 1
    
    return quick_sort(left) + middle + quick_sort(right)

arr = [2,8,4,6,1,9]
print(quick_sort(arr))