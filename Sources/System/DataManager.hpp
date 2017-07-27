#ifndef OE_DATAMANAGER_HPP
#define OE_DATAMANAGER_HPP

#include "Prerequisites.hpp"
#include "Singleton.hpp"
#include "List.hpp"

namespace oe
{

struct Data
{
	Data(const std::string& key, const std::string& value);

	std::string key;
	std::string value;
};

class DataViewer
{
	public:
		DataViewer();
		virtual ~DataViewer();

		void connect();
		void disconnect();
		bool isConnected() const;

		virtual void setData(const std::string& key, const std::string& value);
		virtual void eraseData(const std::string& key);
		virtual void clear();

	private:
		bool mConnected;	
};

class DataManager : public Singleton<DataManager>
{
	public:
		DataManager();
		~DataManager();

		static DataManager& getSingleton();
		static DataManager* getSingletonPtr();

		void setData(const std::string& key, const std::string& value);
		std::string getData(const std::string& key) const;
		void eraseData(const std::string& key);
		void clear();

		void connectViewer(DataViewer* viewer);
		void disconnectViewer(DataViewer* viewer);

	private:
		std::vector<Data> mData;

		List<DataViewer*> mViewers;
};

} // namespace oe

#endif // OE_DATAMANAGER_HPP
