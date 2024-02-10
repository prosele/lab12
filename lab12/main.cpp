#include <iostream>
#include <list>
#include <vector>
#include <deque>
using namespace std;
template<typename T>
class RangeIter {
private:
    typename T::iterator current;
    typename T::iterator end;
public:
    RangeIter(typename T::iterator begin, typename T::iterator end) : current(begin), end(end) {}

    RangeIter& operator++() {
        ++current;
        return *this;
    }

    RangeIter& operator--() {
        --current;
        return *this;
    }

    typename T::reference operator*() {
        return *current;
    }

    bool operator==(const RangeIter& other) {
        return current == other.current;
    }

    bool operator!=(const RangeIter& other) {
        return current != other.current;
    }
};

template<typename T>
class Range {
private:
    T& container;
public:
    Range(T& container) : container(container) {}

    RangeIter<T> begin(int n) {
        typename T::iterator temp = container.begin();
        while (n != 0) {
            ++temp;
            n--;
        }
        return RangeIter<T>(temp, container.end());
    }

    RangeIter<T> end(long long n) {
        typename T::iterator temp = container.end();
        long long k = size(container) - n - 1;
        while (k != 0) {
            --temp;
            k--;
        }
        return RangeIter<T>(temp, temp);
    }
};

int main() {
    list<int> l = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Range<list<int>> range(l);

    cout << "Iterating over list: ";
    for (RangeIter it = range.begin(3); it != range.end(7); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}
