#include <vector>

template <class T, class Comparator> void mergeSortHelper(std::vector<T>& myArray, int k, Comparator comp, int begin, int end);
template <class T, class Comparator> void merge(std::vector<T>& myArray, int k, Comparator comp, std::vector<std::pair<int,int> > indices, int begin, int end);

//called with initial myArray, never called again
template <class T, class Comparator>
  void mergeSort (std::vector<T>& myArray, int k, Comparator comp) {
    //base case, sort with selection sort
    int size = myArray.size();
    if (size < k) {
      for (int i = 0; i < size; i++) {
        //set min as first element
        T minval = myArray[i];
        int minindex = i;
        //compare all elements with min
        for (int j = i + 1; j < size; j++) {
          if (comp(myArray[j], minval)) {
            minval = myArray[j];
            minindex = j;
          }
        }
        //set new min
        T temp = myArray[i];
        myArray[i] = minval;
        myArray[minindex] = temp;
      }
      //vector is sorted, done
      return;
    }

    //create vecotr of indices and size from one index to next
    std::vector<std::pair<int,int> > indices;
    //not every partition will have the same size
    //find how many partitions will have an extra element
    int remainder = size % k;
    int offset = 0;
    //add to indices
    for (int i = 0; i < k; i++) {
      int extra = 0;
      bool entered = false;
      if (remainder > 0) {
        //add 1 to pair second
        extra = 1;
        entered = true;
        remainder--;
      }
      //add pair to indices
      indices.push_back(std::make_pair(size / k * i + offset, size / k + extra));
      //an extra element in a pair offsets all the pairs after
      if (entered) {
        offset++;
      }
    }

    //call helper to mergesort partition of array
    for (int i = 0; i < k; i++) {
      //only call if there are more than one element
      if (indices[i].second > 1) {
        mergeSortHelper(myArray, k, comp, indices[i].first, indices[i].first + indices[i].second - 1);
      }
    } 
    //merge the diferent partitions together
    merge(myArray, k, comp, indices, 0, size - 1);
  }

//recursive helper function to split myArray further
template <class T, class Comparator>
  void mergeSortHelper(std::vector<T>& myArray, int k, Comparator comp, int begin, int end) {
    int size = end - begin + 1;
    //base case, selection sort
    if (size < k) {
      for (int i = begin; i <= end; i++) {
        //set min as first element
        T minval = myArray[i];
        int minindex = i;
        //compare all elements with min
        for (int j = i + 1; j <= end; j++) {
          if (comp(myArray[j], minval)) {
            minval = myArray[j];
            minindex = j;
          }
        }
        //set new min
        T temp = myArray[i];
        myArray[i] = minval;
        myArray[minindex] = temp;
      }
      //vector is sorted, done
      return;
    }

    //create vector of indices and sizes
    std::vector<std::pair<int,int> > indices;
    //not every partition will have the same size
    //find how many partitions will have an extra element
    int remainder = size % k;
    int offset = 0;
    //add to indices
    for (int i = 0; i < k; i++) {
      int extra = 0;
      bool entered = false;
      if (remainder > 0) {
        //add 1 to pair second
        extra = 1;
        entered = true;
        remainder--;
      }
      //add pair to indices
      indices.push_back(std::make_pair(size / k * i + begin + offset, size / k + extra));
      //an extra element in a pair offsets all the pairs after
      if (entered) {
        offset++;
      }
    }

    //call helper to mergesort partition of array
    for (int i = 0; i < k; i++) {
      //only call if there are more than one element
      if (indices[i].second > 1) {
        mergeSortHelper(myArray, k, comp, indices[i].first, indices[i].first + indices[i].second - 1);
      }
    }
    //merge the diferent partitions together
    merge(myArray, k, comp, indices, begin, end);
  }

//merge multiple partitions of myArray to one sorted partition
template <class T, class Comparator>
  void merge(std::vector<T>& myArray, int k, Comparator comp, std::vector<std::pair<int,int> > indices, int begin, int end) {
    //create temporary vector to hold sorted values from begin to end
    std::vector<T> temp;
    
    //loop while not done
    bool done = false;
    while (!done) {
      T minval;
      int minindex;
      //give min initial value
      for (int i = 0; i < k; i++) {
        if (indices[i].second > 0) {
          minval = myArray[indices[i].first];
          minindex = i;
          break;
        }
      }

      //find actual min
      for (int i = minindex + 1; i < k; i++) {
        if (indices[i].second > 0 && comp(myArray[indices[i].first], minval)) {
          minval = myArray[indices[i].first];
          minindex = i; 
        }
      }

      //increment index and decrement size of pair in indices with the min
      indices[minindex].first++;
      indices[minindex].second--;
      //add min to temp
      temp.push_back(minval);
      //loop to see if all elements added, done set true as default
      done = true;
      for (int i = 0; i < k; i++) {
        //if there is still elements to add, not done
        if (indices[i].second > 0) {
          done = false;
        }
      }
    }

    //copy temp to myArray
    for (unsigned int i = 0; i < temp.size(); i++) {
      myArray[begin + i] = temp[i];
    }
  }