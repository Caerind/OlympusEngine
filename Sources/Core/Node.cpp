#include "Node.hpp"
#include "../System/Logger.hpp"

namespace oe
{

Node::Node()
	: mParent(nullptr)
	, mChildren()
	, mLocalPosition(0.0f, 0.0f)
	, mLocalOrigin(0.0f, 0.0f)
	, mLocalScale(1.0f, 1.0f)
	, mLocalRotation(0.0f)
	, mLocalZ(0.0f)
	, mLocalTransform()
	, mGlobalTransform()
	, mGlobalPosition(0.0f, 0.0f)
	, mLocalTransformUpdated(false)
	, mGlobalTransformUpdated(false)
{
}

void Node::attach(Node* child)
{
	if (child == nullptr || child->mParent == this)
	{
		return;
	}

	if (child->mParent != nullptr)
	{
		child->mParent->detach(child);
	}

	#ifdef OE_SAFETY
	if (std::find(mChildren.begin(), mChildren.end(), child) != mChildren.end())
	{
		return;
	}
	#endif

	mChildren.push_back(child);

	child->mParent = this;
	child->invalidateNode();
	child->invalidateNodeZ();
}

void Node::detach(Node* child)
{
	auto itr = std::find(mChildren.begin(), mChildren.end(), child);
	if (itr != mChildren.end())
	{
		mChildren.erase(itr);
	}

	if (child != nullptr)
	{
		child->mParent = nullptr;
		child->invalidateNode();
		child->invalidateNodeZ();
	}
}

bool Node::hasChildren() const
{
	return !mChildren.empty();
}

bool Node::hasParent() const
{
	return mParent != nullptr;
}

const Vector2& Node::getPosition() const
{
	return mLocalPosition;
}

const Vector2& Node::getOrigin() const
{
	return mLocalOrigin;
}

const Vector2& Node::getScale() const
{
	return mLocalScale;
}

const F32& Node::getRotation() const
{
	return mLocalRotation;
}

const F32& Node::getPositionZ() const
{
	return mLocalZ;
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
	setPosition(Vector2(x, y));
	setPositionZ(z);
}

void Node::setPosition(const Vector2& position, F32 z)
{
	setPosition(position);
	setPositionZ(z);
}

void Node::setOrigin(F32 x, F32 y)
{
	setOrigin(Vector2(x, y));
}

void Node::setOrigin(const Vector2& origin)
{
	if (mLocalOrigin != origin)
	{
		mLocalOrigin = origin;
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
	if (mLocalZ != z)
	{
		mLocalZ = z;
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

const sf::Transform& Node::getLocalTransform() const
{
	ensureUpdateLocalTransform();
	return mLocalTransform;
}

const sf::Transform& Node::getGlobalTransform() const
{
	ensureUpdateGlobalTransform();
	return mGlobalTransform;
}

const Vector2& Node::getGlobalPosition() const
{
	ensureUpdateGlobalTransform();
	return mGlobalPosition;
}

const F32& Node::getGlobalZ() const
{
	ensureUpdateGlobalZ();
	return mGlobalZ;
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

void Node::invalidateNode()
{
	mGlobalTransformUpdated = false;
	for (Node* child : mChildren)
	{
		child->invalidateNode();
	}
	onNodeInvalidation(this);
}

void Node::invalidateNodeZ()
{
	mGlobalZUpdated = false;
	for (Node* child : mChildren)
	{
		child->invalidateNodeZ();
	}
	onNodeInvalidationZ(this);
}

void Node::updateLocalTransform() const
{
	const F32 angle = -mLocalRotation;
	const F32 cos = Math::cos(angle);
	const F32 sin = Math::sin(angle);

	const F32 sxc = mLocalScale.x * cos;
	const F32 syc = mLocalScale.y * cos;
	const F32 sxs = mLocalScale.x * sin;
	const F32 sys = mLocalScale.y * sin;

	const F32 tx = -mLocalOrigin.x * sxc - mLocalOrigin.y * sys + mLocalPosition.x;
	const F32 ty = mLocalOrigin.x * sxs - mLocalOrigin.y * syc + mLocalPosition.y;

	mLocalTransform = sf::Transform(sxc, sys, tx, -sxs, syc, ty, 0.0f, 0.0f, 1.0f);

	mLocalTransformUpdated = true;
}

void Node::updateGlobalTransform() const
{
	ensureUpdateLocalTransform();
	if (hasParent())
	{
		mGlobalTransform = mParent->getGlobalTransform() * mLocalTransform;
		mGlobalPosition.set(toOE(mGlobalTransform.transformPoint(0.0f, 0.0f)));
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
	if (hasParent())
	{
		mGlobalZ = mParent->getGlobalZ() + mLocalZ;
	}
	else
	{
		mGlobalZ = mLocalZ;
	}
	mGlobalZUpdated = true;
}

} // namespace oe