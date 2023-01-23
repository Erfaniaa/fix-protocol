#ifndef FIXED_VECTOR_H
#define FIXED_VECTOR_H

#include <cstddef>

template <typename T>
class FixedVector {
public:
    FixedVector();

    void push_back(const T& value);

    void pop_back();

    std::size_t size() const;

    T& operator[](std::size_t index);

    const T& operator[](std::size_t index) const;

	bool operator==(const FixedVector<T>& other) const;

	FixedVector<T>& operator=(const FixedVector<T>& other) const;

private:
    static constexpr std::size_t MaxSize = 1024;
    std::size_t size_;
    T data_[MaxSize];
};

#endif
