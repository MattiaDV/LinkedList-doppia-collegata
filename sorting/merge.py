def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    
    mind = len(arr) // 2

    right = merge_sort(arr[mind:])
    left = merge_sort(arr[:mind])

    return merge(left, right)
    
def merge(left, right):
    result = []
    i = j = 0

    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    
    result.extend(left[i:])
    result.extend(right[j:])
    return result

arr = [2,8,4,6,1,9]
print(merge_sort(arr))