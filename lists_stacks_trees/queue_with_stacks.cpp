// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <iostream>
#include <stack>

using namespace std;

/************** begin assignment **************/
// Queue insertion and deletion follows first-in, first-out semantics; stack
// insertion and deletion is last-in, first-out. How would you implement a queue
// with the help of two stacks?
//
// Of course, implementing a queue with stacks is not efficient, but it is a
// good exercise to get familiar with data structures and templates ;).
// When coding in real life use the C++ queue implementation:
// https://www.geeksforgeeks.org/queue-cpp-stl/
// Or if a problem requires it, use the priority queue implementation of std:
// https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/

// simple queue implementation with two stacks
template <typename T>
class Queue {
   private:
    // these are the only class variables you need to implement the queue.
    stack<T> enq, deq;

    // move all elements from the enqueue stack to the dequeue stack
    void shift_stacks() {
        while (!enq.empty()) {
            deq.push(enq.top());
            enq.pop();
        }
    }

   public:
    // TODO: implement enqueue
    void enqueue(T x) {
        enq.push(x);
    }

    // TODO: implement dequeue
    T dequeue() {
        // if there are no elements in the dequeue stack put all the enqueue elements in dequeue
        if (deq.empty()) {
            shift_stacks();
        }
        T x = deq.top();
        deq.pop();
        return x;
    }

    // convenience functions
    // TODO: implement size
    size_t size() { return enq.size() + deq.size(); }
    // TODO: implement empty
    bool empty() { return enq.empty() & deq.empty(); }
};
/*************** end assignment ***************/

int main() {
    {
        Queue<int> my_queue;
        assert(my_queue.size() == 0);
        assert(my_queue.empty());
        my_queue.enqueue(1);
        my_queue.enqueue(2);
        my_queue.enqueue(3);
        assert(my_queue.size() == 3);
        assert(!my_queue.empty());
        assert(my_queue.dequeue() == 1);
        assert(my_queue.dequeue() == 2);
        my_queue.enqueue(7);
        assert(my_queue.size() == 2);
        assert(my_queue.dequeue() == 3);
        assert(my_queue.dequeue() == 7);
        assert(my_queue.size() == 0);
        assert(my_queue.empty());
    }
    {
        int n = 1000000;
        Queue<int> my_queue;
        for (int i = 0; i < n; ++i) {
            my_queue.enqueue(i);
        }
        assert(my_queue.size() == size_t(n));
        assert(!my_queue.empty());
        for (int i = 0; i < n / 2; ++i) {
            my_queue.dequeue();
        }
        assert(my_queue.size() == size_t(n / 2));
        assert(my_queue.dequeue() == n / 2);
        for (int i = 0; i < 10; ++i) {
            my_queue.enqueue(i);
        }
        for (int i = 0; i < n / 2 - 1; ++i) {
            assert(my_queue.dequeue() == n / 2 + 1 + i);
        }
        for (int i = 0; i < 10; ++i) {
            assert(my_queue.dequeue() == i);
        }
        assert(my_queue.size() == 0);
        assert(my_queue.empty());
    }
    cout << "all tests passed" << endl;
}
