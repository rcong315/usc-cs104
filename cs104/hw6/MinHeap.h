#include <vector>

template <class T>
  class MinHeap {
     public:
        /* Constructor that builds a d-ary Min Heap
          This should work for any d >= 2,
          but doesn't have to do anything for smaller d.*/
       MinHeap (int d) {
        //set d value for heap
        dary = d;
       }
       
       ~MinHeap () {
        //clear heap
        heap.clear();
       }

        /* adds the item to the heap, with the given priority. */
       void add (T item, int priority) {
         //first add item to end
         heap.push_back({item, priority});
         int child = heap.size() - 1;
         //calculate the index of the parent
         int parent = (child - 1) / dary;

         //compare the item added to its parent and bubble up when necessary
         while (parent >= 0 && heap[parent].second > heap[child].second) {
           std::swap(heap[parent], heap[child]);
           //calculate new parent
           child = parent;
           parent = (child - 1) / dary;
         }
       }
         
        /* returns the element with smallest priority.  
          Break ties however you wish.  
          Throws an exception if the heap is empty. */
       const T & peek () const {
         //throw exception when empty
         if (heap.empty()) {
           throw std::exception();
         }

         //return first element
         return heap[0].first;
       }
         
        /* removes the element with smallest priority.
          Break ties however you wish.
          Throws an exception if the heap is empty. */
       void remove () {
         //throw exception when empty
         if (heap.empty()) {
           throw std::exception();
         }

         //swap item to remove and last item
         //makes removing easier
         std::swap(heap[0], heap[heap.size() - 1]);
         //remove item
         heap.pop_back();
         int size = heap.size();
         int parent = 0;

         //loop while the parent node is in the heap
         while (dary * parent + 1 < size) {
          //calculate the indices of the children nodes and find the one with highest priority
          int minchild = dary * parent + 1;
          for (int d = 2; d <= dary; d++) {
            int child = dary * parent + d;
            if (child < size && heap[child].second < heap[minchild].second) {
              minchild = child;
            }
          }

          //bubble up the parent has lower priority than child node
          if (heap[parent].second > heap[minchild].second) {
            std::swap(heap[parent], heap[minchild]);
          }

          //otherwise all children have lower priority than parent, done swapping nodes
          else {
            return;
          }

          //set new parent and firstchild after swapping
          parent = minchild;
         }
       }
         
        /* returns true iff there are no elements on the heap. */
       bool isEmpty () {
         return heap.empty();
       }
    

   private:
      // whatever you need to naturally store things.
      // You may also add helper functions here.
      //using vector to act as heap
      std::vector<std::pair<T, int>> heap;
      //int to store d value of heap
      int dary;
  };
