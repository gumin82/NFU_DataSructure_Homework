#include <iostream>
using namespace std;

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
};

template <class T>
class MinHeap : public MinPQ<T> {
private:
    T* heap;
    int heapSize;
    int capacity;

    void resize() {
        capacity *= 2;
        T* newHeap = new T[capacity + 1];
        for (int i = 1; i <= heapSize; i++)
            newHeap[i] = heap[i];
        delete[] heap;
        heap = newHeap;
    }

public:
    MinHeap(int cap = 10) {
        capacity = cap;
        heapSize = 0;
        heap = new T[capacity + 1];
    }

    ~MinHeap() {
        delete[] heap;
    }

    bool IsEmpty() const override {
        return heapSize == 0;
    }

    const T& Top() const override {
        if (IsEmpty()) throw "Heap is empty";
        return heap[1];
    }

    void Push(const T& e) override {
        if (heapSize == capacity)
            resize();

        int current = ++heapSize;

        while (current != 1 && heap[current / 2] > e) {
            heap[current] = heap[current / 2];
            current /= 2;
        }

        heap[current] = e;
    }

    void Pop() override {
        if (IsEmpty()) throw "Heap is empty";

        T last = heap[heapSize--];

        int current = 1;
        int child = 2;

        while (child <= heapSize) {
            if (child < heapSize && heap[child] > heap[child + 1])
                child++;
            if (last <= heap[child]) break;
            heap[current] = heap[child];
            current = child;
            child *= 2;
        }
        heap[current] = last;
    }

    void Print() const {
        for (int i = 1; i <= heapSize; i++)
            cout << heap[i] << " ";
        cout << endl;
    }
};
int main() {
    MinHeap<int> h;
    h.Push(1);
    h.Push(2);
    h.Push(4);
    h.Push(3);
    cout << "Top: " << h.Top() << endl;
    h.Pop();
    cout << "Pop: ";
    h.Print();
    return 0;
}