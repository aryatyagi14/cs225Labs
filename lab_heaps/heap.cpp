
/**
	 * @file heap.cpp
	 * Implementation of a heap class.
	 */
	 #include <iostream>
	 #include <cmath>
	 using namespace std;
	
	
	template <class T, class Compare>
	size_t heap<T, Compare>::root() const
	{
	 // @TODO Update to return the index you are choosing to be your root.
	 return 1;
	}
	
	template <class T, class Compare>
	size_t heap<T, Compare>::leftChild(size_t currentIdx) const
	{
	 return currentIdx * 2;
	 // @TODO Update to return the index of the left child.
	}
	
	template <class T, class Compare>
	size_t heap<T, Compare>::rightChild(size_t currentIdx) const
	{
	 return 1 + (currentIdx * 2);
	 // @TODO Update to return the index of the right child.
	}
	
	template <class T, class Compare>
	size_t heap<T, Compare>::parent(size_t currentIdx) const
	{
	 // @TODO Update to return the index of the parent.
	 return currentIdx / 2;
	}
	
	template <class T, class Compare>
	bool heap<T, Compare>::hasAChild(size_t currentIdx) const
	{
	 return (_elems.size() > 2 * currentIdx);
	 // @TODO Update to return whether the given node has a child
	}
	
	template <class T, class Compare>
	size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
	{
	 bool first_check = _elems.size() <= rightChild(currentIdx);
	 if(first_check || higherPriority(_elems[leftChild(currentIdx)], _elems[rightChild(currentIdx)]) == true)
	 {
	 return leftChild(currentIdx);
	 }
	 else
	 {
	 return rightChild(currentIdx);
	 }
	 // @TODO Update to return the index of the child with highest priority
	 /// as defined by higherPriority()
	 //return 0;
	}
	
	template <class T, class Compare>
	void heap<T, Compare>::heapifyDown(size_t currentIdx)
	{
	
	
	 if ( hasAChild(currentIdx) == true )
	 {
	 size_t temp_Child = maxPriorityChild(currentIdx);
	 if (higherPriority(_elems[temp_Child], _elems[currentIdx]) == true)
	 {
	 swap(_elems[currentIdx], _elems[temp_Child]);
	 heapifyDown(temp_Child);
	 }
	 
	 }
	 else
	 {
	 return;
	 }
	 // @TODO Implement the heapifyDown algorithm.
	}
	
	template <class T, class Compare>
	void heap<T, Compare>::heapifyUp(size_t currentIdx)
	{
	 if (currentIdx == root())
	 return;
	 size_t parentIdx = parent(currentIdx);
	 if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
	 std::swap(_elems[currentIdx], _elems[parentIdx]);
	 heapifyUp(parentIdx);
	 }
	}
	
	template <class T, class Compare>
	heap<T, Compare>::heap()
	{
	 _elems.push_back(T());
	 // @TODO Depending on your implementation, this function may or may
	 /// not need modifying
	}
	
	template <class T, class Compare>
	heap<T, Compare>::heap(const std::vector<T>& elems) 
	{
	 _elems.push_back(T());
	
	 size_t i = 0;
	 while(i < elems.size())
	 {
	 _elems.push_back(elems[i]);
	 i++;
	 }
	
	 int temp;
	 temp = _elems.size() - 1;
	 while(temp >= 0)
	 {
	 heapifyDown(temp);
	 temp--;
	 }
	 // @TODO Construct a heap using the buildHeap algorithm
	}
	
	template <class T, class Compare>
	T heap<T, Compare>::pop()
	{
	 int start_ind = 1;
	 if(_elems.empty() == true || _elems.size() == 1)
	 {
	 return T();
	 }
	 T temp_result = _elems[start_ind];
	 swap(_elems[start_ind], _elems[_elems.size() -1]);
	 _elems.pop_back();
	 heapifyDown(start_ind);
	 return temp_result;
	 // @TODO Remove, and return, the element with highest priority
	 //return T();
	}
	
	template <class T, class Compare>
	T heap<T, Compare>::peek() const
	{
	 int start_ind = 1;
	 return _elems[start_ind];
	 // @TODO Return, but do not remove, the element with highest priority
	 //return T();
	}
	
	template <class T, class Compare>
	void heap<T, Compare>::push(const T& elem)
	{
	 _elems.push_back(elem);
	 heapifyUp(_elems.size() - 1);
	 // @TODO Add elem to the heap
	}
	
	template <class T, class Compare>
	void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
	{
	 T curr = _elems[idx];
	 _elems[idx] = elem;
	 
	 if(higherPriority(curr, elem))
	 {
	 heapifyDown(idx);
	 }
	 else 
	 {
	 heapifyUp(idx);
	 }
	 // @TODO In-place updates the value stored in the heap array at idx
	 // Corrects the heap to remain as a valid heap even after update
	}
	
	
	template <class T, class Compare>
	bool heap<T, Compare>::empty() const
	{ 
	 return _elems.size() == 0;
	 // @TODO Determine if the heap is empty
	 //return true;
	}
	
	template <class T, class Compare>
	void heap<T, Compare>::getElems(std::vector<T> & heaped) const
	{
	 for (size_t i = root(); i < _elems.size(); i++) {
	 heaped.push_back(_elems[i]);
	 }
	}