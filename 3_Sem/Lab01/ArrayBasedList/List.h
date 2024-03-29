#ifndef LAB_LIST_H
#define LAB_LIST_H

#include <cstddef>
#include <ostream>
#include <string>
#include <sstream>
#include <initializer_list>

#include "Visitor.h"

const int DELTA_CAPACITY = 30;

template <class U>
class ListIterator;

template <class T>
class List {
private:
	size_t size_;
	size_t capacity_;
	T* array_;
public:
	List();
	List(const List<T>& source);
	List(List<T>&& source);
	List(std::initializer_list<T> args);
	~List();
	size_t size() const;
	bool isEmpty() const;
	T& front() const;
	T& back() const;
	ListIterator<T> iterator();
	void accept(Visitor &v);
	T& getElement(int index) const;
	size_t getCapacity() const;
	void clear();
	void pushBack(const T value);
	void pushFront(const T value);
	void popBack();
	void popFront();
	void setSize(size_t newSize);
	void setCapacity(size_t newCapacity);
	void setElement(int index, const T& value);
	void resize();

	List<T>& operator+=(const List<T>& list);
	List<T>& operator=(const List<T>& source);
	List<T>& operator=(List<T>&& source);

	template <class K>
	friend std::ostream& operator<<(std::ostream& stream, ListIterator<K>& iterator);
	template <class K>
	friend std::istream& operator>>(std::istream& stream, List<K>& list);
	template <class K>
	friend const List<K> operator+(const List<K>& left, const List<K>& right);
	template <class K>
	friend bool operator==(const List<K>& left, const List<K>& right);
	template <class K>
	friend bool operator!=(const List<K>& left, const List<K>& right);
	template <class K>
	friend void swap(List<K>& firstList, List<K>& secondList);

	template<class U> friend class ListIterator;
};


template <class T>
List<T>::List() {
	array_ = nullptr;
	size_ = 0;
	capacity_ = 0;
}

template <class T>
List<T>::List(const List<T>& source) : List() {
	size_ = source.size();
	capacity_ = source.getCapacity();
	if (capacity_ > 0) {
		array_ = new T[capacity_];

		for (int i = 0; i < source.size(); i++) {
			array_[i] = source[i];
		}
	}
}

template <class T>
List<T>::List(std::initializer_list<T> args) : List() {
	typename std::initializer_list<T>::iterator it = args.begin();
	while (it != args.end()) {
		this->pushBack(*it);
		it++;
	}
}

template <class T>
List<T>::List(List<T>&& source) : List() {
	swap(*this, source);
}

template <class T>
List<T>::~List() {
	this->clear();
}

template <class T>
size_t List<T>::size() const {
	return size_;
}

template <class T>
size_t List<T>::getCapacity() const {
	return capacity_;
}

template <class T>
bool List<T>::isEmpty() const {
	return size_ == 0;
}

template <class T>
T& List<T>::front() const {
	if (size_ > 0) {
		return array_[0];
	}
}

template <class T>
T& List<T>::back() const {
	if (size_ > 0) {
		return array_[size_ - 1];
	}
}

template <class T>
ListIterator<T> List<T>::iterator() {
	ListIterator<T> it = ListIterator<T>(this);
	return it;
}

template <class T>
void List<T>::accept(Visitor &v) {
	ListIterator<T> iterator(this);

	while (iterator.hasNext()) {
		v.visit(iterator.current());
		iterator.next();
	}
}

template <class T>
T& List<T>::getElement(int index) const {
	return array_[index];
}

template <class T>
void List<T>::clear() {
	if (array_ != nullptr) {
		delete [] array_;
	}
	array_ = nullptr;
	size_ = 0;
	capacity_ = 0;
}

template <class T>
void List<T>::pushBack(const T value) {
	if (size_+1 > capacity_) {
		capacity_ += DELTA_CAPACITY;
		this->resize();
	}
	array_[size_] = value;
	size_++;
}


template <class T>
void List<T>::pushFront(const T value) {
	if (size_+1 > capacity_) {
		capacity_ += DELTA_CAPACITY;
		this->resize();
	}
	for (int i = size_; i > 0; i--) {
		array_[i] = array_[i - 1];
	}
	array_[0] = value;
	size_++;
}

template <class T>
void List<T>::popBack() {
	if (size_ != 0) {
		size_--;
	}
}

template <class T>
void List<T>::popFront() {
	if (size_ != 0) {
		for (int i = 0; i < size_ - 1; i++) {
			array_[i] = array_[i + 1];
		}
		size_--;
	}
}

template  <class T>
void List<T>::setSize(size_t newSize) {
	size_ = newSize;
}

template  <class T>
void List<T>::setCapacity(size_t newCapacity) {
	capacity_ = newCapacity;
}

template  <class T>
void List<T>::setElement(int index, const T& value) {
	array_[index] = value;
}

template  <class T>
void List<T>::resize() {
	int* oldArray = array_;
	if (capacity_ > 0) {
		array_ = new T[capacity_];
		for (int i = 0; i < size_; i++) {
			array_[i] = oldArray[i];
		}
	}
	else {
		array_ = nullptr;
	}
	if (oldArray != nullptr) {
		delete [] oldArray;
		oldArray = nullptr;
	}
}

template  <class T>
List<T>& List<T>::operator+=(const List<T>& list) {
	for (int i = 0; i < list.size(); i++) {
		this->pushBack(list.getElement(i));
	}
	return *this;
}

template  <class T>
List<T>& List<T>::operator=(const List<T>& source) {
	if (this == &source) {
		return *this;
	}
	this->clear();
	size_ = source.size();
	capacity_ = source.getCapacity();
	if (capacity_ > 0) {
		array_ = new T[capacity_];

		for (int i = 0; i < source.size(); i++) {
			array_[i] = source.getElement(i);
		}
	}
	else {
		array_ = nullptr;
	}
	return *this;
}

template  <class T>
List<T>& List<T>::operator=(List<T>&& source) {
	if (this == &source) {
		return *this;
	}
	this->clear();
	swap(*this, source);
	return *this;
}

template  <class T>
std::ostream& operator<<(std::ostream& stream, ListIterator<T>& iterator) {
	while(iterator.hasNext()) {
		stream << iterator.current()<< " ";
		iterator.next();
	}
	return stream;
}

template  <class T>
std::istream& operator>>(std::istream& stream, List<T>& list) {
	list.clear();
	std::string s;
	std::getline(stream, s);
	std::istringstream ss(s);
	T value;
	while (ss >> value) {
		list.pushBack(value);
	}
	return stream;
}

template <class T>
const List<T> operator+(const List<T>& left, const List<T>& right) {
	List<T> result;
	if (left.getCapacity() + right.getCapacity() > 0) {
		for (int i = 0; i < left.size(); i++) {
			result.pushBack(left.getElement(i));
		}

		for (int i = 0; i < right.size(); i++) {
			result.pushBack(right.getElement(i));
		}
	}
	else {
		result.array_ = nullptr;
	}

	return result;
}

template <class T>
bool operator==(const List<T>& left, const List<T>& right) {
	if (left.size_ != right.size_) {
		return false;
	}

	for (int i = 0; i < left.size(); i++) {
		if (left.getElement(i) != right.getElement(i)) {
			return false;
		}
	}
	return true;
}

template <class T>
bool operator!=(const List<T>& left, const List<T>& right) {
	if (left.size_ != right.size_) {
		return true;
	}

	for (int i = 0; i < left.size(); i++) {
		if (left.getElement(i) != right.getElement(i)) {
			return true;
		}
	}
	return false;
}

template <class T>
void swap(List<T>& firstList, List<T>& secondList) {
	size_t temp;
	T* tempArray;

	temp = firstList.size_;
	firstList.size_ = secondList.size_;
	secondList.size_ = temp;

	temp = firstList.capacity_;
	firstList.capacity_ = secondList.capacity_;
	secondList.capacity_ = temp;

	tempArray = firstList.array_;
	firstList.array_ = secondList.array_;
	secondList.array_ = tempArray;

}

#endif //LAB_LIST_H
