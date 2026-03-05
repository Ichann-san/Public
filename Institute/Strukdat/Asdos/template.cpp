#include <iostream>
#include <string>
#include <list>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct Region {
    string name;
    list<string> visions;
    Region(string val) : name(val) {}
};

struct Location {
    int region_idx, pos, ring_size;
    bool found;
    Location() : region_idx(-1), pos(-1), ring_size(-1), found(false) {}
};

Location search(const list<Region>& network, const string& target_name) {
    Location loc;
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

string solve(const list<Region>& teyvat, int total_regions) {
    int maks, jarak = 0;
    string source, destination, res;
    cin >> source >> destination >> maks;
    /*
    Implement ur code here
    */
    return res;
}

int main() {
    list<Region> teyvat;
    int regions, t;
    cin >> regions;

    for (int i = 0; i < regions; i++) {
        /*
        Implement ur code here
        */
    }
    
    cin >> t;
    while(t--) cout << solve(teyvat, regions) << "\n";
    return 0;
}