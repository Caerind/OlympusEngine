#ifndef OE_APPLICATION_HPP
#define OE_APPLICATION_HPP

#include "../System/Singleton.hpp"

namespace oe
{

class Application : public Singleton<Application>
{
	public:
		Application();

		bool run() const;
		void stop();

		static Application& getSingleton();
		static Application* getSingletonPtr();

	private:
		bool mRunning;
};

} // namespace oe

#endif // OE_COLOR_HPP
