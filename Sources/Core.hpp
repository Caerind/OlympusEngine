#ifndef OE_CORE_HPP
#define OE_CORE_HPP

#include "Core/Color.hpp"
#include "Core/Compression.hpp"
#include "Core/Connection.hpp"
#include "Core/Date.hpp"
#include "Core/File.hpp"
#include "Core/Localization.hpp"
#include "Core/Log.hpp"
#include "Core/Math.hpp"
#include "Core/Matrix.hpp"
#include "Core/NonCopyable.hpp"
#include "Core/ParserCsv.hpp"
#include "Core/ParserIni.hpp"
#include "Core/ParserIni.hpp"
#include "Core/ParserPure.hpp"
#include "Core/ParserXml.hpp"
#include "Core/PoolAllocator.hpp"
#include "Core/Profiler.hpp"
#include "Core/Quaternion.hpp"
#include "Core/Random.hpp"
#include "Core/ResourceHolder.hpp"
#include "Core/Serialization.hpp"
#include "Core/Singleton.hpp"
#include "Core/StackAllocator.hpp"
#include "Core/String.hpp"
#include "Core/Thread.hpp"
#include "Core/Time.hpp"
#include "Core/UniqueId.hpp"
#include "Core/UnitTest.hpp"
#include "Core/Updatable.hpp"
#include "Core/Vector.hpp"

namespace oe
{

/// Just a class to initialize all singleton
class OE_API Core : public Singleton<Core>
{
	public:
		Core();
		~Core();

		static Core& getSingleton();
		static Core* getSingletonPtr();

	private:
		OConsole* mOutputConsole;
		IConsole* mInputConsole;
		Log* mLog;
		Profiler* mProfiler;
		Localization* mLocalization;
		UniqueIdManager* mUniqueIdManager;
};

} // namespace oe

#endif // OE_CORE_HPP