def main():
    num_elements = int(input())
    even_sum = 0
    
    for _ in range(num_elements):
        current_number = int(input())
        if current_number % 2 == 0:
            even_sum += current_number
            
    print(even_sum)

if __name__ == "__main__":
    main()