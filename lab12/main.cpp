#include <iostream>
#include <list>
using namespace std;

template<typename T>
class RangeIter {
private:
    // typename нужно, так как итератор зависит от шаблона T - контейнера. компилятор не может проверять T (на данный момент у него нет определения), и поэтому он не знает, является ли T::iterator статическим полем или типом. в такой ситуации компилятор предполагает, что это поле, поэтому это приводит к синтаксической ошибке. чтобы решить проблему, просто сообщите компилятору, что это тип, указав имя типа перед объявлением
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
    
    // T::reference указывает на тип ссылки на элемент контейнера, которая будет возвращена оператором разыменования
    typename T::reference operator*() {
        return *current;
    }

    bool operator==(const RangeIter& other) {
        return current == other.current;
    }

    bool operator!=(const RangeIter& other) {
        return current != other.current;
    }
    void print() {
        for (typename T::iterator it = current; it != end; ++it) {
            cout << *it << " ";
        }
    }
};

template<typename T>
class Range {
private:
    T& container;
public:
    Range(T& container) : container(container) {}
    RangeIter<T> setRange(int n, long long k) {
        typename T::iterator temp1 = container.begin();
        while (n != 0) {
            ++temp1;
            n--;
        }
        typename T::iterator temp2 = container.end();
        long long h = size(container) - k - 1;
        while (h != 0) {
            --temp2;
            h--;
        }
        return RangeIter<T>(temp1, temp2);
    }
};

int main() {
    list<int> myList = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Range<list<int>> range(myList);
    RangeIter it = range.setRange(3, 7);
    cout << "Элементы списка из заданного диапазона: ";
    it.print();
    cout << endl;
    return 0;
}
