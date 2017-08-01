#ifndef OE_LIST_HPP
#define OE_LIST_HPP

#include <functional>
#include <vector>
#include <algorithm>

#include "Prerequisites.hpp"

namespace oe
{

template <typename T>
class List
{
	public:
		using iterator = typename std::vector<T>::iterator;
		using const_iterator = typename std::vector<T>::const_iterator;
		using reverse_iterator = typename std::vector<T>::reverse_iterator;
		using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;

		List() : mList() {}

		void clear() { mList.clear(); }

		bool has(T item)
		{
			for (T i : mList)
			{
				if (i == item)
				{
					return true;
				}
			}
			return false;
		}

		bool insert(T item)
		{
			if (!has(item))
			{
				mList.push_back(item);
				return true;
			}
			return false;
		}

		bool remove(T item)
		{
			auto itr = std::find(mList.begin(), mList.end(), item);
			if (itr != mList.end())
			{
				mList.erase(itr);
				return true;
			}
			return false;
		}

		U32 size() const { return mList.size(); }
		bool empty() const { return mList.empty(); }

		iterator find(T item)
		{
			return std::find(mList.begin(), mList.end(), item);
		}

		void sort(std::function<bool(T a, T b)> sortingFunction)
		{
			std::sort(mList.begin(), mList.end(), sortingFunction);
		}

		iterator begin()
		{
			return mList.begin();
		}

		const_iterator begin() const
		{
			return mList.begin();
		}

		iterator end()
		{
			return mList.end();
		}

		const_iterator end() const
		{
			return mList.end();
		}

		const_iterator cbegin() const
		{
			return mList.cbegin();
		}

		const_iterator cend() const
		{
			return mList.cend();
		}

		const_reverse_iterator crbegin() const
		{
			return mList.crbegin();
		}

		const_reverse_iterator crend() const
		{
			return mList.crend();
		}

		reverse_iterator rbegin()
		{
			return mList.rbegin();
		}

		const_reverse_iterator rbegin() const
		{
			return mList.rbegin();
		}

		reverse_iterator rend()
		{
			return mList.rend();
		}

		const_reverse_iterator rend() const
		{
			return mList.rend();
		}

	protected:
		std::vector<T> mList;
};

} // namespace oe

#endif // OE_LIST_HPP
