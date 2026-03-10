def main():
    input_string = input()
    character_counts = {}
    
    for char in input_string:
        character_counts[char] = character_counts.get(char, 0) + 1
        
    for char, count in character_counts.items():
        print(f"{char}={count}")

if __name__ == "__main__":
    main()