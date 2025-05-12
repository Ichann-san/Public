while True:
    item = input("Please input the item description: ")
    if not item:
        continue

    for i in range(len(item)):
        if not ((ord(item[i]) > 64 and ord(item[i]) < 91) or (ord(item[i]) >96 and ord(item[i]) < 123)):
            break
    else:
        print("Item description:", item)
        break