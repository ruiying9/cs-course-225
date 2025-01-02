#include "dsets.h"
#include <cmath>
#include <iostream>
void DisjointSets::addelements(int num){
    for (int i = 0; i < num; i++) {
        sets.push_back(-1);
    }
}
int DisjointSets::find(int elem){
    if(sets[elem]<0){
        return elem;/*it self is the root*/
    }
    int root = find(sets[elem]);/*sets[elem]-the value will just be the parent's index*/
    sets[elem] = root;/*update the parent index to be the root*/
    return root;
}
void DisjointSets::setunion(int a, int b){
    int root1 = find(a);
    int root2 = find(b);
    if(root2==a || root1==b) return;
    if (sets[root1] > sets[root2]) {/*set1-2 set2-4 append set1 to 2*/
        sets[root2] += sets[root1];
        sets[root1] = root2;
    } else {
        sets[root1] += sets[root2];
        sets[root2] = root1;
    }
}
int DisjointSets::size(int elem){
    int size=abs(sets[find(elem)]);
    return size;
}
void DisjointSets::print(){
    for(int i:sets){
        std::cout<<i<<std::endl;
    }
}