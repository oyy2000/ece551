#include <iostream>
#include <vector>
#include <map>
using namespace std;

template <typename T>
// templated function addOne
void addOne(std::map<T, int> &my_map, const T &to_add) {
    typename std::map<T, int>::iterator it = my_map.find(to_add);
    if (it == my_map.end()) {
        // inserting to_add into it if there is not a key for it and set value to 1
        my_map.insert(std::make_pair(to_add, 1));
    } else {
        // else incrementing its value by 1
        it->second++;
    }
}
int main() {
}