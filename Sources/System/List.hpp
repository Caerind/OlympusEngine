#ifndef OE_LIST_HPP
#define OE_LIST_HPP

#include "../System/Prerequisites.hpp"

#include <vector>

namespace oe
{

template <typename T>
class List
{
	public:
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
			for (auto itr = mList.begin(); itr != mList.end(); ++itr)
			{
				if (item == *itr)
				{
					mList.erase(itr);
					return true;
				}
			}
			return false;
		}

		U32 size() const { return mList.size(); }
		bool empty() const { return mList.empty(); }

		typename std::vector<T>::iterator begin()
		{
			return mList.begin();
		}

		typename std::vector<T>::const_iterator begin() const
		{
			return mList.begin();
		}

		typename std::vector<T>::iterator end()
		{
			return mList.end();
		}

		typename std::vector<T>::const_iterator end() const
		{
			return mList.end();
		}

		typename std::vector<T>::const_iterator cbegin() const
		{
			return mList.cbegin();
		}

		typename std::vector<T>::const_iterator cend() const
		{
			return mList.cend();
		}

		typename std::vector<T>::const_reverse_iterator crbegin() const
		{
			return mList.crbegin();
		}

		typename std::vector<T>::const_reverse_iterator crend() const
		{
			return mList.crend();
		}

		typename std::vector<T>::reverse_iterator rbegin()
		{
			return mList.rbegin();
		}

		typename std::vector<T>::const_reverse_iterator rbegin() const
		{
			return mList.rbegin();
		}

		typename std::vector<T>::reverse_iterator rend()
		{
			return mList.rend();
		}

		typename std::vector<T>::const_reverse_iterator rend() const
		{
			return mList.rend();
		}

	protected:
		std::vector<T> mList;
};

} // namespace oe

#endif // OE_LIST_HPP
