#include "Node.hpp"

namespace oe
{

Node::Node()
	: mParent(nullptr)
	, mChilds()
	, mLocalPosition(0.0f, 0.0f, 0.0f)
	, mLocalScale(1.0f, 1.0f)
	, mLocalRotation(0.0f)
	, mLocalTransform()
	, mGlobalTransform()
	, mGlobalPosition(0.0f, 0.0f, 0.0f)
	, mLocalTransformUpdated(false)
	, mGlobalTransformUpdated(false)
	, mGlobalZUpdated(false)
{
}

void Node::setParent(Node* node)
{
	if (mParent == node)
	{
		return;
	}
	if (mParent != nullptr)
	{
		mParent->removeChild(this);
	}
	mParent = node;
	if (mParent != nullptr)
	{
		mParent->addChild(this);
	}
	invalidateNode();
	invalidateNodeZ();
}

bool Node::hasChilds() const
{
	return !mChilds.empty();
}

bool Node::hasParent() const
{
	return mParent != nullptr;
}

const Vector3& Node::getPosition() const
{
	return mLocalPosition;
}

const Vector2& Node::getScale() const
{
	return mLocalScale;
}

F32 Node::getRotation() const
{
	return mLocalRotation;
}

F32 Node::getPositionZ() const
{
	return mLocalPosition.z;
}

void Node::setPosition(F32 x, F32 y)
{
	setPosition(Vector2(x, y));
}

void Node::setPosition(const Vector2& position)
{
	if (mLocalPosition.x != position.x || mLocalPosition.y != position.y)
	{
		mLocalPosition.x = position.x;
		mLocalPosition.y = position.y;
		mLocalTransformUpdated = false;
		invalidateNode();
	}
}

void Node::setPosition(F32 x, F32 y, F32 z)
{
	setPosition(Vector3(x, y, z));
}

void Node::setPosition(const Vector3& position)
{
	if (mLocalPosition != position)
	{
		if (mLocalPosition.z != position.z)
		{
			invalidateNodeZ();
		}
		mLocalPosition = position;
		mLocalTransformUpdated = false;
		invalidateNode();
	}
}

void Node::setScale(F32 x, F32 y)
{
	setScale(Vector2(x, y));
}

void Node::setScale(const Vector2& scale)
{
	if (mLocalScale != scale)
	{
		mLocalScale = scale;
		mLocalTransformUpdated = false;
		invalidateNode();
	}
}

void Node::setRotation(F32 rotation)
{
	if (mLocalRotation != rotation)
	{
		mLocalRotation = rotation;
		mLocalTransformUpdated = false;
		invalidateNode();
	}
}

void Node::setPositionZ(F32 z)
{
	if (mLocalPosition.z != z)
	{
		mLocalPosition.z = z;
		invalidateNodeZ();
	}
}

void Node::move(F32 x, F32 y)
{
	move(Vector2(x, y));
}

void Node::move(const Vector2& movement)
{
	if (movement != Vector2::zero())
	{
		mLocalPosition.x += movement.x;
		mLocalPosition.y += movement.y;
		mLocalTransformUpdated = false;
		invalidateNode();
	}
}

void Node::move(F32 x, F32 y, F32 z)
{
	move(Vector3(x, y, z));
}

void Node::move(const Vector3& movement)
{
	if (movement != Vector3::zero())
	{
		if (movement.z != 0.0f)
		{
			invalidateNodeZ();
		}
		mLocalPosition += movement;
		mLocalTransformUpdated = false;
		invalidateNode();
	}
}

void Node::scale(F32 x, F32 y)
{
	scale(Vector2(x, y));
}

void Node::scale(const Vector2& scale)
{
	if (scale != Vector3(1.0f))
	{
		mLocalScale *= scale;
		mLocalTransformUpdated = false;
		invalidateNode();
	}
}

void Node::rotate(F32 rotation)
{
	if (rotation != 0.0f)
	{
		mLocalRotation += rotation;
		mLocalTransformUpdated = false;
		invalidateNode();
	}
}

void Node::moveZ(F32 z)
{
	if (z != 0.0f)
	{
		mLocalPosition.z += z;
		invalidateNodeZ();
	}
}

const Vector3& Node::getGlobalPosition() const
{
	ensureUpdateGlobalTransform();
	ensureUpdateGlobalZ();
	return mGlobalPosition;
}

const F32& Node::getGlobalZ() const
{
	ensureUpdateGlobalZ();
	return mGlobalPosition.z;
}

const sf::Transform& Node::getGlobalTransform() const
{
	ensureUpdateGlobalTransform();
	return mGlobalTransform;
}

void Node::ensureUpdateLocalTransform() const
{
	if (!mLocalTransformUpdated)
	{
		updateLocalTransform();
	}
}

void Node::ensureUpdateGlobalTransform() const
{
	if (!mLocalTransformUpdated || !mGlobalTransformUpdated)
	{
		updateGlobalTransform();
	}
}

void Node::ensureUpdateGlobalZ() const
{
	if (!mGlobalZUpdated)
	{
		updateGlobalZ();
	}
}

void Node::addChild(Node* node)
{
	#ifdef OE_SAFETY
	if (std::find(mChilds.begin(), mChilds.end(), node) != mChilds.end())
	{
		return;
	}
	#endif
	mChilds.push_back(node);
}

void Node::removeChild(Node* node)
{
	auto itr = std::find(mChilds.begin(), mChilds.end(), node);
	if (itr != mChilds.end())
	{
		mChilds.erase(itr);
	}
}

void Node::invalidateNode()
{
	mGlobalTransformUpdated = false;
	for (Node* node : mChilds)
	{
		node->invalidateNode();
	}
	onNodeInvalidation(this);
}

void Node::invalidateNodeZ()
{
	mGlobalZUpdated = false;
	for (Node* node : mChilds)
	{
		node->invalidateNodeZ();
	}
	onNodeInvalidationZ(this);
}

void Node::updateLocalTransform() const
{
	const F32 angle = -mLocalRotation;
	const F32 cos = Math::cos(angle);
	const F32 sin = Math::sin(angle);
	mLocalTransform = sf::Transform(mLocalScale.x * cos, mLocalScale.y * sin, mLocalPosition.x, -mLocalScale.x * sin, mLocalScale.y * cos, mLocalPosition.y, 0.0f, 0.0f, 1.0f);
	mLocalTransformUpdated = true;
}

void Node::updateGlobalTransform() const
{
	ensureUpdateLocalTransform();
	if (mParent)
	{
		mGlobalTransform = mParent->getGlobalTransform() * mLocalTransform;
		mGlobalPosition.set(toOE(mGlobalTransform.transformPoint(0.0f, 0.0f)), mGlobalPosition.z);
	}
	else
	{
		mGlobalTransform = mLocalTransform;
		mGlobalPosition = mLocalPosition;
	}
	mGlobalTransformUpdated = true;
}

void Node::updateGlobalZ() const
{
	if (mParent)
	{
		mGlobalPosition.z = mParent->getGlobalZ() + mLocalPosition.z;
	}
	else
	{
		mGlobalPosition.z = mLocalPosition.z;
	}
	mGlobalZUpdated = true;
}

} // namespace oe