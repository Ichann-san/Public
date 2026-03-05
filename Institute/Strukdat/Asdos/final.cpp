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
    int region_idx, pos, ring_size, found;
    Location() : region_idx(-1), pos(-1), ring_size(-1), found(0) {}
};

Location search(const list<Region>& network, const string& destination_name) {
    Location loc; int i = 0;
    
    for (const Region& r : network) {
        int j = 1;
        for (const string& vision_name : r.visions) {
            if (vision_name == destination_name) {
                loc.region_idx = i; 
                loc.pos = j;
                loc.ring_size = r.visions.size() + 1;
                loc.found = 1;
                return loc;
            }
            j++;
        }
        i++;
    }
    return loc;
}

int get_distance(int pos1, int pos2, int ring_size) {
    int diff = abs(pos1 - pos2);
    return min(diff, ring_size - diff);
}

string solve(const list<Region>& teyvat, int total_regions) {
    int maks, jarak = 0;
    string source, destination;
    cin >> source >> destination >> maks;

    Location src = search(teyvat, source);
    Location dst = search(teyvat, destination);
    if (!src.found || !dst.found) return "Signal lost";

    if (src.region_idx == dst.region_idx) jarak = get_distance(src.pos, dst.pos, src.ring_size - 1);
    else {
        int exit_dist  = get_distance(src.pos, 0, src.ring_size);
        int enter_dist = get_distance(dst.pos, 0, dst.ring_size);
        int super_dist = get_distance(src.region_idx, dst.region_idx, total_regions);
        jarak = exit_dist + super_dist + enter_dist;
    }

    if (jarak <= maks) return "Connected on " + to_string(jarak) + " second";
    else return "Signal lost";
}

int main() {
    list<Region> teyvat;
    int regions, t;
    cin >> regions;

    for (int i = 0; i < regions; i++) {
        string name, character;
        cin >> name; 
        Region current_region(name);
        
        while (cin >> character && character != "end") current_region.visions.push_back(character);
        teyvat.push_back(current_region);
    }
    
    cin >> t;
    while(t--) cout << solve(teyvat, regions) << endl;
    return 0;
}