def main():
    num_elements = int(input())
    positive_sum = 0
    
    for _ in range(num_elements):
        current_number = int(input())
        if current_number > 0:
            positive_sum += current_number
            
    print(positive_sum)

if __name__ == "__main__":
    main()