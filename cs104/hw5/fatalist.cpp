#include <vector>
#include <algorithm>

bool PairFirstCompare(std::pair<int,int> l, std::pair<int,int> r);
bool PairSecondCompare(std::pair<int,int> l, std::pair<int,int> r);

bool FatalistHypothesis(std::vector<std::pair<int,int> > grades) {
    //satisfies hypothesis even if there are no grades
    if (grades.empty()) {
        return true;
    }

    //sort vector by 104 grades
    std::sort(grades.begin(), grades.end(), PairFirstCompare);
    //compare 170 grades pair by pair
    for (unsigned int i = 0; i < grades.size() - 1; i++) {
        //return false if two pairs do not satisfy hypothesis
        if (grades[i].first != grades[i + 1].first && !PairSecondCompare(grades[i], grades[i + 1])) {
            return false;
        }
    }

    //sort vector by 170 grades
    std::sort(grades.begin(), grades.end(), PairSecondCompare);
    //compare 104 grades pair by pair
    for (unsigned int i = 0; i < grades.size() - 1; i++) {
        //return false if two pairs do not satisfy hypothesis
        if (grades[i].second != grades[i + 1].second && !PairFirstCompare(grades[i], grades[i + 1])) {
            return false;
        }
    }

    //return true at the end, no problems encountered
    return true;
}

bool PairFirstCompare(std::pair<int,int> l, std::pair<int,int> r) {
    return l.first <= r.first;
}

bool PairSecondCompare(std::pair<int,int> l, std::pair<int,int> r) {
    return l.second <= r.second;
}