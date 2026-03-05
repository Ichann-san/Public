#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct VisionNode {
    char name[50];
    struct VisionNode* next;
};

struct RegionNode {
    char name[50];
    int vision_count;
    struct VisionNode* vision_head;
    struct RegionNode* next;
};

struct Location {
    int region_idx, pos, ring_size, found;
};

struct Location search(struct RegionNode* network, const char* target_name) {
    struct Location loc = {-1, -1, -1, 0};
    /*
    Implement ur code here
    */
    return loc;
}

int get_distance(int pos1, int pos2, int ring_size) {
    /*
    Implement ur code here
    */
    return 0;
}

void solve(struct RegionNode* teyvat, int total_regions) {
    int maks;
    char source[50], destination[50];
    scanf("%s %s %d", source, destination, &maks);
    /*
    Implement ur code here
    */
}

int main() {
    int regions, t;
    scanf("%d", &regions);
    struct RegionNode* head_region = NULL;
    struct RegionNode* tail_region = NULL;

    for (int i = 0; i < regions; i++) {
        char region_name[50], char_name[50];
        scanf("%s", region_name);
        /*
        Implement ur code here
        */
        
        while (scanf("%s", char_name) == 1 && strcmp(char_name, "end") != 0) {
            /*
            Implement ur code here
            */
        }
    }

    scanf("%d", &t);
    while(t--) solve(head_region, regions);
    return 0;
}