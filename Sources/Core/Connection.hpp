#ifndef OE_CONNECTION_HPP
#define OE_CONNECTION_HPP

#include "NonCopyable.hpp"

#include <algorithm>
#include <functional>
#include <memory>
#include <map>
#include <vector>

namespace oe
{

namespace priv
{
	class OE_API AbstractConnectionImpl
	{
		public:
			virtual void disconnect() = 0;
			virtual ~AbstractConnectionImpl()
			{
			}
	};

	template <typename List>
	class OE_API IteratorConnectionImpl : public AbstractConnectionImpl
	{
		private:
			using Iterator = typename List::Iterator;

		public:
			IteratorConnectionImpl(List& container, Iterator iterator)
				: mContainer(&container)
				, mIterator(iterator)
			{
			}

			virtual void disconnect()
			{
				mContainer->remove(mIterator);
			}

		private:
			List* mContainer;
			Iterator mIterator;
	};

	template <typename Container>
	class OE_API IdConnectionImpl : public AbstractConnectionImpl
	{
		private:
			using ValueType = typename Container::value_type;

		public:
			IdConnectionImpl(Container& container, U32 id)
				: mContainer(&container)
				, mId(id)
			{
			}

			virtual void disconnect()
			{
				// TODO : Use binary search
				auto found = std::find_if(mContainer->begin(), mContainer->end(), [this](ValueType& v) { return v.id == mId; });
				if (found != mContainer->end())
					mContainer->erase(found);
			}

		private:
			Container* mContainer;
			U32 mId;
	};

	template <typename List>
	std::shared_ptr<IteratorConnectionImpl<List>> makeIteratorConnectionImpl(List& container, typename List::Iterator iterator)
	{
		return std::make_shared<IteratorConnectionImpl<List>>(container, iterator);
	}

	template <typename Container>
	std::shared_ptr<IdConnectionImpl<Container>> makeIdConnectionImpl(Container& container, U32 id)
	{
		return std::make_shared<IdConnectionImpl<Container>>(container, id);
	}

} // namespace priv

class OE_API Connection
{
	public:
		Connection() : mWeakRef()
		{
		}

		bool isConnected() const
		{
			return !mWeakRef.expired();
		}

		void invalidate()
		{
			mWeakRef.reset();
		}

		void disconnect()
		{
			if (auto shared = mWeakRef.lock())
			{
				shared->disconnect();
				invalidate();
			}
		}

	public:
		explicit Connection(std::weak_ptr<priv::AbstractConnectionImpl> tracker)
			: mWeakRef(std::move(tracker))
		{
		}

	private:
		std::weak_ptr<priv::AbstractConnectionImpl> mWeakRef;
};


class OE_API ScopedConnection : private NonCopyable
{
	public:
		ScopedConnection()
			: mConnection()
		{
		}

		explicit ScopedConnection(const Connection& connection)
			: mConnection(connection)
		{
		}

		ScopedConnection(ScopedConnection&& source)
			: mConnection(source.mConnection)
		{
			source.mConnection.invalidate();
		}

		ScopedConnection& operator= (ScopedConnection&& source)
		{
			mConnection = source.mConnection;
			source.mConnection.invalidate();
			return *this;
		}

		~ScopedConnection()
		{
			mConnection.disconnect();
		}

		bool isConnected() const
		{
			return mConnection.isConnected();
		}

	private:
		Connection mConnection;
};

namespace priv
{
	template <typename Parameter>
	class OE_API Listener
	{
		private:
			using Function = std::function<void(Parameter)>;

		public:
			Listener(const Function& fn)
				: mFunction(fn)
				, mStrongRef()
			{
			}

			void call(Parameter arg) const
			{
				mFunction(arg);
			}

			void swap(Listener& other)
			{
				std::swap(mFunction, other.mFunction);
				std::swap(mStrongRef, other.mStrongRef);
			}

			template <class ListenerContainer>
			void setEnvironment(ListenerContainer& container, typename ListenerContainer::Iterator iterator)
			{
				mStrongRef = makeIteratorConnectionImpl(container, iterator);
			}

			Connection shareConnection() const
			{
				return Connection(mStrongRef);
			}

		private:
			Function mFunction;
			std::shared_ptr<AbstractConnectionImpl>	mStrongRef;
	};

	template <typename Parameter>
	class OE_API ListenerSequence
	{
		public:
			using ValueType = Listener<Parameter>;

		private:
			using Container = std::vector<ValueType>;

		public:
			using Iterator = typename Container::iterator;

		public:
			Connection add(const ValueType& listener)
			{
				mListeners.push_back(listener);
				Iterator added = mListeners.end() - 1;
				added->setEnvironment(*this, added);
				return added->shareConnection();
			}

			void remove(Iterator iterator)
			{
				iterator->swap(mListeners.back());
				mListeners.pop_back();
			}

			void clear()
			{
				mListeners.clear();
			}

			void call(Parameter arg) const
			{
				for (const ValueType& listener : mListeners)
				{
					listener.call(arg);
				}
			}

		private:
			Container mListeners;
	};

	template <typename Trigger, typename Parameter>
	class OE_API ListenerMap
	{
		public:
			using ValueType = Listener<Parameter>;
			using KeyType = Trigger;

		private:
			using Container = std::multimap<KeyType, ValueType>;
			using ConstIterator = typename Container::const_iterator;

		public:
			using Iterator = typename Container::iterator;

		public:
			Connection add(const KeyType& trigger, const ValueType& listener)
			{
				Iterator added = mListeners.insert(std::make_pair(trigger, listener));
				added->second.setEnvironment(*this, added);
				return added->second.shareConnection();
			}

			void remove(Iterator iterator)
			{
				mListeners.erase(iterator);
			}

			void clear(KeyType key)
			{
				mListeners.erase(key);
			}

			void clearAll()
			{
				mListeners.clear();
			}

			void call(Trigger event, Parameter arg) const
			{
				std::pair<ConstIterator, ConstIterator> range = mListeners.equal_range(event);
				for (ConstIterator itr = range.first; itr != range.second; ++itr)
				{
					itr->second.call(arg);
				}
			}

		private:
			Container mListeners;
	};

} // namespace priv

} // namespace oe

#endif // OE_CONNECTION_HPP
