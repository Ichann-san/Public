#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    int n, value, target = 100;
    unordered_map<int, int> seen;
    scanf("%d", &n);
    if(n == 1){
        scanf("%d", &value);
        printf("1");
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        int complement = target - value;
        if (seen.find(complement) != seen.end()) {
            printf("%d\n%d", seen[complement]+1, i+1);
            return 0;
        }
        seen[value] = i;
    }
    return 0;
}