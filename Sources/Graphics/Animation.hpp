#ifndef OE_ANIMATION_HPP
#define OE_ANIMATION_HPP

#include "../System/Time.hpp"
#include "../Application/ResourceManager.hpp"

#include "Rect.hpp"

namespace oe
{

class Animation
{
	public:
		struct Frame
		{
			Frame();
			Frame(ResourceId texture, const Rect& rect, Time duration);

			ResourceId texture;
			Rect rect;
			Time duration;
		};

	public:
		Animation();

		void addFrame(const Animation::Frame& frame = Animation::Frame());
		void addFrame(oe::ResourceId texture, const Rect& rect, Time duration);

		U32 getFrameCount() const;

		Animation::Frame& getFrame(U32 index);

		void removeFrame(U32 index);

		void removeAllFrames();

		Time getDuration() const;

	private:
		std::vector<Animation::Frame> mFrames;
};

} // namespace oe

#endif // OE_ANIMATION_HPP

