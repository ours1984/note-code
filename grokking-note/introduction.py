#! /usr/bin/python

def binary_search(list,item):

    low = 0
    high = len(list)-1

    while low <= high:
        mid = (low + high) / 2
        guess = list[mid]
        if guess == item:
            return mid
        elif guess >item:
            high = mid -1
        else:
            low = mid + 1
    return None

def force_search(list,item):
    low = 0
    high = len(list)-1

    while low <= high:
        guess = list[low]
        if guess == item:
            return low
        ++low
    return None

