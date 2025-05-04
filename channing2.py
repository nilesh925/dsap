def create(table, bucket):
    global b
    b = int(input("Size of list: "))
    for i in range(b):
        table.append([None, -1])  # [key, link]
        bucket[i] = -1

def insert(table, bucket):
    key = int(input("Enter element: "))
    hashvalue = key % b

    if table[hashvalue][0] is None:
        table[hashvalue][0] = key
        bucket[hashvalue] = hashvalue
    else:
        for i in range(1, b):
            newhashvalue = (hashvalue + i) % b
            if table[newhashvalue][0] is None:
                table[newhashvalue][0] = key
                if bucket[hashvalue] != hashvalue:
                    # Traverse to the last node in chain
                    temp = hashvalue
                    while table[temp][1] != -1:
                        temp = table[temp][1]
                    table[temp][1] = newhashvalue
                else:
                    table[hashvalue][1] = newhashvalue
                bucket[hashvalue] = newhashvalue
                break

def search(table, key):
    global a
    hashvalue = key % b
    a = hashvalue

    if table[hashvalue][0] == key:
        return hashvalue
    else:
        while table[hashvalue][1] != -1:
            a = hashvalue
            hashvalue = table[hashvalue][1]
            if table[hashvalue][0] == key:
                return hashvalue
    return -1

def delete(table):
    key = int(input("Element to be deleted: "))
    hashvalue = search(table, key)
    if hashvalue != -1:
        if table[hashvalue][1] != -1:
            table[a][1] = table[hashvalue][1]
        else:
            table[a][1] = -1
        table[hashvalue][0] = None
        table[hashvalue][1] = -1
        print("Deleted")
    else:
        print("Element not found")

def display(table):
    print("Index\tKey\tLink")
    for i in range(b):
        print(f"{i}\t{table[i][0]}\t{table[i][1]}")
    print()

def main():
    global a, b
    table = []
    bucket = {}
    a = 0
    b = 0
    create(table, bucket)
    n = int(input("Enter the number of elements: "))
    for _ in range(n):
        insert(table, bucket)
    display(table)
    key = int(input("Enter element to be searched: "))
    s = search(table, key)
    if s != -1:
        print(f"Found at index {s}")
    else:
        print("Not found")
    delete(table)
    display(table)

main()

# Size of list: 5
# Enter the number of elements: 3
# Enter element: 7
# Enter element: 12
# Enter element: 17

# Index	Key	Link
# 0	    None	-1
# 1	    None	-1
# 2	    7	    3
# 3	    12	    4
# 4	    17	    -1

# Enter element to be searched: 12
# Found at index 3

# Element to be deleted: 12
# Deleted

# Index	Key	Link
# 0	    None	-1
# 1	    None	-1
# 2	    7	    4
# 3	    None	-1
# 4	    17	    -1
