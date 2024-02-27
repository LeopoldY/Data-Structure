#include "Stack&Queue/LinkedQueue.hpp"
using namespace std;

int main() {
    LinkedQueue<int> s;
    s.enqueue(3);
    s.enqueue(4);
    s.enqueue(5);
    cout << s.dequeue() << endl;
    cout << s.dequeue() << endl;
    cout << s.dequeue() << endl;
    return 0;
}
