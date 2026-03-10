def main():
    num_elements = int(input())
    positive_sum = 0
    positive_count = 0
    
    for _ in range(num_elements):
        current_number = int(input())
        if current_number > 0:
            positive_sum += current_number
            positive_count += 1
            
    if positive_count > 0:
        average = positive_sum / positive_count
        print(f"{average:.2f}")
    else:
        print("No positive numbers")

if __name__ == "__main__":
    main()