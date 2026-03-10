def main():
    num_elements = int(input())
    if num_elements > 0:
        max_element = max(int(input()) for _ in range(num_elements))
        print(max_element)

if __name__ == "__main__":
    main()