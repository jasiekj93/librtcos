#pragma once

/**
 * @file ArrayBuffer.hpp
 * @author Adrian Szczepanski
 * @date 2023-11-23
 */

#include <librtcos/Buffer.hpp>
#include <algorithm>
#include <memory>

namespace rtcos::utils
{
    template <class T>
	class ArrayBuffer : public Buffer<T>
	{
	public:
		ArrayBuffer(size_t, const T& nullValue = T());

        inline const T& operator[](int i) const override { return array[i]; }
        void clear() override;
        bool put(const T&) override;

        bool isFull() const override;
        bool isEmpty() const override;

        inline size_t getSize() const  override { return size; }
        inline size_t getCount() const  override { return count; }
        inline const T* getData() const  override { return array.get(); }

        inline auto begin() { return array.get(); }
        inline auto begin() const { return array.get(); }
        inline auto end() { return array.get() + count; }
        inline auto end() const { return array.get() + count; }

        bool dropTo(ArrayBuffer& to);
        ArrayBuffer clone() const;

    protected:
        void eraseTo(size_t to);

    private:
        std::unique_ptr<T[]> array;
        const size_t size;
        size_t count;
        const T nullValue;
	};
}

#include <librtcos/utils/ArrayBuffer.tpp>
