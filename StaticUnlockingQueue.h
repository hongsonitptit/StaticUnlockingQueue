/* 
 * This class is a non-blocking queue that supports access (pop/push method) 
 * from multi threads without using blocking technique.
 * The static queue has default size is 100000, but we can change it in order to 
 * make more suitable for hardware memory before compiles it.
 */
#ifndef STATIC_UNLOCKING_QUEUE_H_
#define STATIC_UNLOCKING_QUEUE_H_
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define SIZE_OF_QUEUE 100000 //the maximum item that contains in the queue, redefine if need

template <typename T>
class StaticUnlockingQueue
{
public:
    StaticUnlockingQueue(): m_reader(0), m_writer(0)  {}
	~StaticUnlockingQueue() {}
	
	bool isEmpty() {
		return m_reader == m_writer; 
	}
	
	bool isFull() {
		int next_element = (m_writer + 1) % SIZE_OF_QUEUE;
		return next_element == m_reader;
	}

	bool push(T &element)
	{
		if(isFull())
		{
			//can not push element more because the queue is full
			return false;	
		}
		//add new element to queue
		m_queue[m_writer] = element;
		m_writer = next_element;
		return true;
	}

	bool pop(T &element)
	{
		if(isEmpty()) {
			//can not pop element because the queue is empty
			return false;
		}
		//pop an element out of queue
		int next_element = (m_reader + 1) % SIZE_OF_QUEUE;
		element = m_queue[m_reader];
		m_reader = next_element;
		return true;
	}
private:
	int m_reader; //reading pointer
	int m_writer; // writing pointer
	T m_queue [SIZE_OF_QUEUE];
};

#endif /* STATIC_UNLOCKING_QUEUE_H_ */
