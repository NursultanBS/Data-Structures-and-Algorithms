/* Your code here! */
#include "dsets.h"
#include <vector>

void DisjointSets::addelements(int num) {
    while(num > 0) {
        s.push_back(-1);
        num--;
    }
}

int DisjointSets::find(int elem) {
    if (s[elem] < 0) {
        return elem;
    } else {
        s[elem] = find(s[elem]);
        return s[elem];
    }
}

void DisjointSets::setunion(int a, int b) {
    int reprA = find(a);
    int reprB = find(b);
    if (reprA == reprB) {
        return;
    }
    //size of repr. el. of set a is larger than or equal to size of repr. el. of set b
    if (s[reprA] <= s[reprB]) {
        s[reprA] += s[reprB];
        s[reprB] = reprA;
    } else {
        s[reprB] += s[reprA];
        s[reprA] = reprB;
    }
}

int DisjointSets::size(int elem) {
    return -s[find(elem)];
}

