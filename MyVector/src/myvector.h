#pragma once

#include <iostream>
#include <algorithm>
#include <stdexcept>

template<typename T>
class MyVector
{
private:
	T* data_;
	size_t size_;
	size_t capacity_;
public:
	MyVector()
		: data_(nullptr), size_(0), capacity_(0)
	{
	}

	MyVector(const size_t& capacity_)
		: data_(new T[capacity_]), size_(0), capacity_(capacity_)
	{
	}

	MyVector(const size_t& count, const T& value)
	{
		assign(count, value);
	}

	MyVector(std::initializer_list<T> list)
	{
		insert(begin(), list);
	}

	MyVector(T* iteratorFirst, T* iteratorLast)
	{
		insert(begin(), iteratorFirst, iteratorLast);
	}

	MyVector(const MyVector& vector)
		: data_(new T[vector.capacity_]), size_(vector.size_), capacity_(vector.capacity_)
	{
		for (int i = 0; i < size_; i++)
		{
			data_[i] = vector[i];
		}
	}

	~MyVector()
	{
		delete[] data_;
	}

public:
	T* begin() noexcept
	{
		return data_;
	}

	const T* begin() const noexcept
	{
		return data_;
	}

	T* end() noexcept
	{
		return data_ + size_;
	}

	const T* end() const noexcept
	{
		return data_ + size_;
	}

	size_t size() const noexcept
	{
		return size_;
	}

	void resize(const size_t& newSize)
	{
		if (newSize < size_)
		{
			size_ = newSize;

			return;
		}

		if (newSize > size_)
		{
			T* newData = new T[newSize];

			for (int i = 0; i < size_; i++)
			{
				newData[i] = data_[i];
			}

			for (int i = size_; i < newSize; i++)
			{
				newData[i] = 0;
			}

			delete[] data_;
			size_ = newSize;
			capacity_ = newSize;
			data_ = newData;

			return;
		}
	}

	void resize(const size_t& count, const T& value)
	{
		if (count < size_)
		{
			size_ = count;

			for (int i = 0; i < count; i++)
			{
				data_[i] = value;
			}

			return;
		}

		if (count > size_)
		{
			assign(count, value);

			return;
		}
	}

	size_t capacity() const noexcept
	{
		return capacity_;
	}

	bool empty() const noexcept
	{
		return size_ == 0;
	}

	void reserve(const size_t& newCapacity)
	{
		T* newData = new T[newCapacity];

		for (int i = 0; i < size_; i++)
		{
			newData[i] = data_[i];
		}

		delete[] data_;
		data_ = newData;
		capacity_ = newCapacity;
	}

	void shrink_to_fit()
	{
		capacity_ = size_;
		T* newData = new T[capacity_];

		for (int i = 0; i < size_; i++)
		{
			newData[i] = data_[i];
		}

		delete[] data_;
		data_ = newData;
	}

	T& at(const size_t& index)
	{
		if (index >= size_)
		{
			throw std::out_of_range("Invalidate index");
		}

		return data_[index];
	}

	const T& at(const size_t& index) const
	{
		if (index >= size_)
		{
			throw std::out_of_range("Invalidate index");
		}

		return data_[index];
	}

	T& front()
	{
		return *data_;
	}

	const T& front() const
	{
		return *data_;
	}

	T& back()
	{
		return *(data_ + size_ - 1);
	}

	const T& back() const
	{
		return *(data_ + size_ - 1);
	}

	T* data() noexcept
	{
		return data_;
	}

	const T* data() const noexcept
	{
		return data_;
	}

	void assign(const size_t& count, const T& value)
	{
		size_ = count;
		capacity_ = count;

		delete[] data_;

		data_ = new T[capacity_];

		for (int i = 0; i < size_; i++)
		{
			data_[i] = value;
		}
	}

	void assign(T* iteratorFirst, T* iteratorLast)
	{
		int tempSize = iteratorLast - iteratorFirst;
		size_ = tempSize;
		capacity_ = tempSize;

		delete[] data_;

		data_ = new T[capacity_];

		for (int i = 0; i < size_; i++)
		{
			data_[i] = *(iteratorFirst + i);
		}
	}

	void assign(std::initializer_list<T> list)
	{
		size_ = list.size();
		capacity_ = list.size();

		delete[] data_;

		data_ = new T[capacity_];

		for (int i = 0; i < size_; i++)
		{
			data_[i] = list.begin()[i];
		}
	}

	void push_back(const T& value)
	{
		if (capacity_ == 0)
		{
			reserve(8);
		}

		if (size_ >= capacity_)
		{
			reserve(capacity_ * 2);
		}

		data_[size_++] = value;
	}

	void pop_back()
	{
		if (size_ == 0)
		{
			return;
		}

		size_--;
	}
	
	T* insert(const T* position, const T& value)
	{
		size_t posInVector = position - begin();

		if (posInVector >= size_ + 1)
		{
			throw std::out_of_range("Invalidate index");
		}

		if (capacity_ == 0)
		{
			reserve(8);
		}

		if (size_ >= capacity_)
		{
			reserve(capacity_ * 2);
		}

		size_++;

		for (int i = size_ - 1; i > posInVector; i--)
		{
			std::swap(data_[i], data_[i - 1]);
		}

		data_[posInVector] = value;
		position = &data_[posInVector];

		return &data_[posInVector];
	}

	T* insert(const T* position, const size_t& count, const T& value)
	{
		size_t posInVector = position - begin();

		if (posInVector >= size_ + 1)
		{
			throw std::out_of_range("Invalidate index");
		}

		if (size_ + count > capacity_)
		{
			reserve(size_ + count);
		}

		size_ += count;

		for (int i = size_ - 1; i >= posInVector + count; i--)
		{
			std::swap(data_[i], data_[i - count]);
		}

		for (int i = posInVector; i < posInVector + count; i++)
		{
			data_[i] = value;
		}

		position = &data_[posInVector];

		return &data_[posInVector];
	}

	T* insert(const T* position, T* iteratorFirst, T* iteratorLast)
	{
		size_t posInVector = position - begin();

		if (posInVector >= size_ + 1)
		{
			throw std::out_of_range("Invalidate index");
		}

		size_t count = iteratorLast - iteratorFirst;

		if (size_ + count > capacity_)
		{
			reserve(size_ + count);
		}

		size_ += count;

		for (int i = size_ - 1; i >= posInVector + count; i--)
		{
			std::swap(data_[i], data_[i - count]);
		}

		for (int i = posInVector; i < posInVector + count; i++)
		{
			data_[i] = *iteratorFirst++;
		}

		position = &data_[posInVector];

		return &data_[posInVector];
	}

	T* insert(const T* position, std::initializer_list<T> list)
	{
		size_t posInVector = position - begin();

		if (posInVector >= size_ + 1)
		{
			throw std::out_of_range("Invalidate index");
		}

		size_t count = list.size();

		if (size_ + count > capacity_)
		{
			reserve(size_ + count);
		}

		size_ += count;

		for (int i = size_ - 1; i >= posInVector + count; i--)
		{
			std::swap(data_[i], data_[i - count]);
		}

		for (int i = 0, pos = posInVector; i < count; i++)
		{
			data_[pos++] = list.begin()[i];
		}

		position = &data_[posInVector];

		return &data_[posInVector];
	}

	T* erase(const T* position)
	{
		size_t posInVector = position - begin();

		if (posInVector >= size_)
		{
			throw std::out_of_range("Invalidate index");
		}

		for (int i = posInVector + 1; i < size_; i++)
		{
			data_[i - 1] = data_[i];
		}

		size_--;

		return &data_[posInVector];
	}

	T* erase(const T* iteratorFirst, const T* iteratorLast)
	{
		if (iteratorFirst < begin())
		{
			throw std::out_of_range("Cannot seek vector iterator before begin");
		}

		if (iteratorLast > end())
		{
			throw std::out_of_range("Cannot seek vector iterator after end");
		}

		size_t index = iteratorFirst - begin();
		size_t count = iteratorLast - iteratorFirst;

		for (int i = index + count; i < size_; i++)
		{
			data_[i - count] = data_[i];
		}

		size_ -= count;

		return &data_[index];
	}

	void swap(MyVector<T>& vector)
	{
		if (this != &vector)
		{
			T* tempVector = new T[capacity_];

			for (int i = 0; i < size_; i++)
			{
				tempVector[i] = data_[i];
			}

			delete[] data_;

			data_ = vector.data_;
			vector.data_ = tempVector;

			std::swap(capacity_, vector.capacity_);
			std::swap(size_, vector.size_);
		}
	}

	void clear() noexcept
	{
		size_ = 0;
	}

	template<typename... Args>
	T* emplace(const T* position, Args&&... values)
	{
		return insert(position, T(values...));
	}

	template<typename... Args>
	void emplace_back(Args&&... values)
	{
		push_back(T(values...));
	}

	// Operators

	T& operator[](const size_t& index)
	{
		if (index >= size_)
		{
			throw std::out_of_range("Vector subscript out of range");
		}

		return data_[index];
	}

	const T& operator[](const size_t& index) const
	{
		if (index >= size_)
		{
			throw std::out_of_range("Vector subscript out of range");
		}

		return data_[index];
	}

	MyVector& operator=(const MyVector& vector)
	{
		size_ = vector.size();
		capacity_ = vector.capacity();

		delete[] data_;

		data_ = new T[capacity_];

		for (int i = 0; i < size_; i++)
		{
			data_[i] = vector[i];
		}

		return *this;
	}

	MyVector& operator=(std::initializer_list<T> list)
	{
		size_ = list.size();
		capacity_ = list.size();

		delete[] data_;

		data_ = new T[capacity_];

		for (int i = 0; i < size_; i++)
		{
			data_[i] = list.begin()[i];
		}

		return *this;
	}

	friend bool operator==(const MyVector<T>& lhs, const MyVector<T>& rhs)
	{
		if (lhs.size() != rhs.size())
		{
			return false;
		}

		for (int i = 0; i < lhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
			{
				return false;
			}
		}
		
		return true;
	}

	friend bool operator!=(const MyVector<T>& lhs, const MyVector<T>& rhs)
	{
		return !(lhs == rhs);
	}

	friend bool operator<(const MyVector<T>& lhs, const MyVector<T>& rhs)
	{
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	friend bool operator<=(const MyVector<T>& lhs, const MyVector<T>& rhs)
	{
		return !(rhs < lhs);
	}

	friend bool operator>(const MyVector<T>& lhs, const MyVector<T>& rhs)
	{
		return rhs < lhs;
	}

	friend bool operator>=(const MyVector<T>& lhs, const MyVector<T>& rhs)
	{
		return !(lhs < rhs);
	}

	friend std::ostream& operator<<(std::ostream& os, const MyVector& vector)
	{
		for (int i = 0; i < vector.size(); i++)
		{
			os << vector[i] << " ";
		}

		return os;
	}
};