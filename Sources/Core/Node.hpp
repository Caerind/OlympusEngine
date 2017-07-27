#ifndef OE_NODE_HPP
#define OE_NODE_HPP

#include "../System/Prerequisites.hpp"
#include "../System/Signal.hpp"
#include "../Math/Vector2.hpp"
#include "../Graphics/SFMLWrapper.hpp"

namespace oe
{

class Node
{
	public:
		Node();

		void attach(Node* child);
		void detach(Node* child);
		bool hasChildren() const;
		bool hasParent() const;

		const Vector2& getPosition() const;
		const Vector2& getOrigin() const;
		const Vector2& getScale() const;
		const F32& getRotation() const;
		const F32& getPositionZ() const;

		void setPosition(F32 x, F32 y);
		void setPosition(const Vector2& position);
		void setPosition(F32 x, F32 y, F32 z);
		void setPosition(const Vector2& position, F32 z);
		void setOrigin(F32 x, F32 y);
		void setOrigin(const Vector2& origin);
		void setScale(F32 x, F32 y);
		void setScale(const Vector2& scale);
		void setRotation(F32 rotation);
		void setPositionZ(F32 z);

		void move(F32 x, F32 y);
		void move(const Vector2& movement);
		void scale(F32 x, F32 y);
		void scale(const Vector2& scale);
		void rotate(F32 rotation);

		const sf::Transform& getLocalTransform() const;
		const sf::Transform& getGlobalTransform() const;
		const Vector2& getGlobalPosition() const;
		const F32& getGlobalZ() const;

		void ensureUpdateLocalTransform() const;
		void ensureUpdateGlobalTransform() const;
		void ensureUpdateGlobalZ() const;

		// TODO : Convert position in Local/Global space

		OeSignal(onNodeInvalidation, const Node*);
		OeSignal(onNodeInvalidationZ, const Node*);

	protected:
		virtual void invalidateNode();
		virtual void invalidateNodeZ();
		virtual void updateLocalTransform() const;
		virtual void updateGlobalTransform() const;
		virtual void updateGlobalZ() const;

	private:
		Node* mParent;
		std::vector<Node*> mChildren;

		Vector2 mLocalPosition;
		Vector2 mLocalOrigin;
		Vector2 mLocalScale;
		F32 mLocalRotation;
		F32 mLocalZ;
		mutable sf::Transform mLocalTransform;

		mutable sf::Transform mGlobalTransform;
		mutable Vector2 mGlobalPosition;
		mutable F32 mGlobalZ;

		mutable bool mLocalTransformUpdated;
		mutable bool mGlobalTransformUpdated;
		mutable bool mGlobalZUpdated;
};

} // namespace oe

#endif // OE_NODE_HPP
