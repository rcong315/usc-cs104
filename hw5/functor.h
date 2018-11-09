#include <string>

struct AlphaStrComp {
  bool operator() (const std::string& lhs, const std::string& rhs)
  { // Uses string's built in operator<
    // to do lexicographic (alphabetical) comparison
    return (lhs < rhs);
  }
};

struct LengthStrComp {
  bool operator()(const std::string& lhs, const std::string& rhs)
  { // Compares strings by size;
    // Breaks ties by lexicographic comparison
    return (   (lhs.size() < rhs.size())
            || (lhs.size() == rhs.size() && lhs < rhs));
  }
};

struct NumStrComp {
  bool operator()(const std::string& lhs, const std::string& rhs)
  { 
    //create variables to keep track of sums
    int lsum = 0;
    int rsum = 0;
    
    //loop through left string
    for (unsigned int i = 0; i < lhs.size(); i++) {
      char c = lhs.at(i);
      //if char is a digit
      if (isdigit(c)) {
        lsum += c - 48;
      }
      //if char is a letter
      else if (isalpha(c)){
        lsum += toupper(c) - 55;
      }
    }

    //loop through right string
    for (unsigned int i = 0; i < rhs.size(); i++) {
      char c = rhs.at(i);
      //if char is a digit
      if (isdigit(c)) {
        rsum += c - 48;
      }
      //if char is a letter
      else if (isalpha(c)){
        rsum += toupper(c) - 55;
      }
    }
    //if sums are equal compare lexicographically
    if (lsum == rsum) {
      return lhs < rhs;
    }
    //return whether left sum is less than right sum
    return lsum < rsum;
  }
};
