#include "DataManager.hpp"

namespace oe
{

template <> DataManager* Singleton<DataManager>::mSingleton = nullptr;

Data::Data(const std::string& key, const std::string& value)
	: key(key)
	, value(value)
{
}

DataViewer::DataViewer()
{
	connect();
}

DataViewer::~DataViewer()
{
	if (isConnected())
	{
		disconnect();
	}
}

void DataViewer::connect()
{
	if (DataManager::getSingletonPtr() != nullptr)
	{
		DataManager::getSingleton().connectViewer(this);
		mConnected = true;
	}
}

void DataViewer::disconnect()
{
	if (DataManager::getSingletonPtr() != nullptr)
	{
		DataManager::getSingleton().disconnectViewer(this);
		mConnected = false;
	}
}

bool DataViewer::isConnected() const
{
	return mConnected;
}

void DataViewer::setData(const std::string& key, const std::string& value)
{

}

void DataViewer::eraseData(const std::string& key)
{
}

void DataViewer::clear()
{
}

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}

DataManager& DataManager::getSingleton()
{
	ASSERT(mSingleton != nullptr);
	return *mSingleton;
}

DataManager* DataManager::getSingletonPtr()
{
	return mSingleton;
}

void DataManager::setData(const std::string& key, const std::string& value)
{
	bool found = false;
	for (Data& d : mData)
	{
		if (d.key == key)
		{
			d.value = value;
			found = true;
		}
	}
	if (!found)
	{
		mData.emplace_back(key, value);
	}

	for (DataViewer* v : mViewers)
	{
		v->setData(key, value);
	}
}

std::string DataManager::getData(const std::string& key) const
{
	for (const Data& d : mData)
	{
		if (d.key == key)
		{
			return d.value;
		}
	}
	return "";
}

void DataManager::eraseData(const std::string& key)
{
	for (auto itr = mData.begin(); itr != mData.end();)
	{
		if ((*itr).key == key)
		{
			itr = mData.erase(itr);
		}
		else
		{
			++itr;
		}
	}

	for (DataViewer* v : mViewers)
	{
		v->eraseData(key);
	}
}

void DataManager::clear()
{
	mData.clear();

	for (DataViewer* v : mViewers)
	{
		v->clear();
	}
}

void DataManager::connectViewer(DataViewer* viewer)
{
	mViewers.insert(viewer);
}

void DataManager::disconnectViewer(DataViewer* viewer)
{
	mViewers.remove(viewer);
}

} // namespace oe
