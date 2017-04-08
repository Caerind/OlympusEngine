#ifndef OE_NODE_HPP
#define OE_NODE_HPP

#include "Prerequisites.hpp"
#include "Signal.hpp"
#include "../Math/Vector2.hpp"
#include "SFML.hpp"

namespace oe
{

class Node
{
	public:
		Node();

		void setParent(Node* node);
		bool hasChilds() const;
		bool hasParent() const;

		const Vector3& getPosition() const;
		const Vector2& getScale() const;
		F32 getRotation() const;
		F32 getPositionZ() const;

		void setPosition(F32 x, F32 y);
		void setPosition(const Vector2& position);
		void setPosition(F32 x, F32 y, F32 z);
		void setPosition(const Vector3& position);
		void setScale(F32 x, F32 y);
		void setScale(const Vector2& scale);
		void setRotation(F32 rotation);
		void setPositionZ(F32 z);

		void move(F32 x, F32 y);
		void move(const Vector2& movement);
		void move(F32 x, F32 y, F32 z);
		void move(const Vector3& movement);
		void scale(F32 x, F32 y);
		void scale(const Vector2& scale);
		void rotate(F32 rotation);
		void moveZ(F32 z);

		const sf::Transform& getGlobalTransform() const;
		const Vector3& getGlobalPosition() const;
		const F32& getGlobalZ() const;

		void ensureUpdateLocalTransform() const;
		void ensureUpdateGlobalTransform() const;
		void ensureUpdateGlobalZ() const;

		// TODO : Convert position in Local/Global space

		OeSignal(onNodeInvalidation, const Node*);
		OeSignal(onNodeInvalidationZ, const Node*);

	protected:
		void addChild(Node* node);
		void removeChild(Node* node);

		virtual void invalidateNode();
		virtual void invalidateNodeZ();
		virtual void updateLocalTransform() const;
		virtual void updateGlobalTransform() const;
		virtual void updateGlobalZ() const;

	private:
		Node* mParent;
		std::vector<Node*> mChilds;

		Vector3 mLocalPosition;
		Vector2 mLocalScale;
		F32 mLocalRotation;
		mutable sf::Transform mLocalTransform;

		mutable sf::Transform mGlobalTransform;
		mutable Vector3 mGlobalPosition;

		mutable bool mLocalTransformUpdated;
		mutable bool mGlobalTransformUpdated;
		mutable bool mGlobalZUpdated;
};

} // namespace oe

#endif // OE_NODE_HPP
