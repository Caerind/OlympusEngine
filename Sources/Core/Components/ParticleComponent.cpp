#include "ParticleComponent.hpp"
#include "../World.hpp"

namespace oe
{

ParticleComponent::ParticleComponent(Entity& entity, bool attachedToEntity)
	: RenderableComponent(entity, attachedToEntity)
	, mParticles()
	, mAffectors()
	, mTexture(nullptr)
	, mTextureRects()
	, mVertices(sf::Triangles)
	, mNeedsVertexUpdate(true)
	, mQuads()
	, mNeedsQuadUpdate(true)
	, mEmitting(false)
	, mEmissionRate(0.0f)
	, mEmissionDifference(0.0f)
	, mParticleLifetime(seconds(1.0f))
	, mParticlePosition(Vector2(0.0f, 0.0f))
	, mParticleVelocity(Vector2(0.0f, 0.0f))
	, mParticleRotation(0.0f)
	, mParticleRotationSpeed(0.0f)
	, mParticleScale(Vector2(1.0f, 1.0f))
	, mParticleColor(Color::White)
	, mParticleTextureIndex(0)
{
}

void ParticleComponent::setTexture(ResourceId id)
{
	setTexture(getWorld().getTextures().get(id));
}

void ParticleComponent::setTexture(sf::Texture& texture)
{
	mTexture = &texture;
}

U32 ParticleComponent::addTextureRect(U32 x, U32 y, U32 w, U32 h)
{
	mTextureRects.emplace_back(x, y, w, h);
	mNeedsQuadUpdate = true;
	return mTextureRects.size() - 1;
}

void ParticleComponent::addAffector(const Affector& affector)
{
	mAffectors.push_back(affector);
}

void ParticleComponent::clearAffectors()
{
	mAffectors.clear();
}

void ParticleComponent::update(Time dt)
{
	if (mEmitting)
	{
		emitParticles(computeParticleCount(dt));
	}

	U32 psize = mParticles.size();
	if (psize > 0)
	{
		mNeedsVertexUpdate = true;

		oe::Vector2 min;
		oe::Vector2 max;

		for (U32 i = 0; i < psize; )
		{
			if (i == 0)
			{
				min = mParticles[i].position;
				max = mParticles[i].position;
			}
			else
			{
				min.minimize(mParticles[i].position);
				max.maximize(mParticles[i].position);
			}

			updateParticle(mParticles[i], dt); // lifetime, move, rotate
			if (mParticles[i].passedLifetime < mParticles[i].totalLifetime)
			{
				for (auto& affector : mAffectors)
				{
					affector(mParticles[i], dt);
				}
				i++;
			}
			else
			{
				mParticles.erase(mParticles.begin() + i);
				psize--;
			}
		}

		setLocalAABB(oe::Rect(min, max));
	}
}

U32 ParticleComponent::getParticleCount() const
{
	return mParticles.size();
}

void ParticleComponent::clearParticles()
{
	mParticles.clear();
}

void ParticleComponent::enableEmission()
{
	mEmitting = true;
}

void ParticleComponent::disableEmission()
{
	mEmitting = false;
}

void ParticleComponent::setEmissionRate(F32 particlesPerSecond)
{
	mEmissionRate = particlesPerSecond;
}

void ParticleComponent::setParticleLifetime(Distribution<Time> lifetime)
{
	mParticleLifetime = lifetime;
}

void ParticleComponent::setParticlePosition(Distribution<Vector2> position)
{
	mParticlePosition = position;
}

void ParticleComponent::setParticleVelocity(Distribution<Vector2> velocity)
{
	mParticleVelocity = velocity;
}

void ParticleComponent::setParticleRotation(Distribution<F32> rotation)
{
	mParticleRotation = rotation;
}

void ParticleComponent::setParticleRotationSpeed(Distribution<F32> rotationSpeed)
{
	mParticleRotationSpeed = rotationSpeed;
}

void ParticleComponent::setParticleScale(Distribution<Vector2> scale)
{
	mParticleScale = scale;
}

void ParticleComponent::setParticleColor(Distribution<Color> color)
{
	mParticleColor = color;
}

void ParticleComponent::setParticleTextureIndex(Distribution<U32> textureIndex)
{
	mParticleTextureIndex = textureIndex;
}

void ParticleComponent::emitParticle()
{
	Particle particle(mParticleLifetime());
	particle.position = mParticlePosition();
	particle.velocity = mParticleVelocity();
	particle.rotation = mParticleRotation();
	particle.rotationSpeed = mParticleRotationSpeed();
	particle.scale = mParticleScale();
	particle.color = mParticleColor();
	particle.textureIndex = mParticleTextureIndex();
	mParticles.push_back(particle);
}

void ParticleComponent::emitParticles(U32 particleAmount)
{
	for (U32 i = 0; i < particleAmount; i++)
	{
		emitParticle();
	}
}

void ParticleComponent::addGravity(F32 gravityFactor)
{
	mAffectors.push_back([=](Particle& particle, Time dt)
	{
		particle.velocity.y += dt.asSeconds() * gravityFactor;
	});
}

void ParticleComponent::render(sf::RenderTarget& target)
{
	if (mTexture != nullptr)
	{
		if (mNeedsQuadUpdate)
		{
			computeQuads();
			mNeedsQuadUpdate = false;
		}

		if (mNeedsVertexUpdate)
		{
			computeVertices();
			mNeedsVertexUpdate = false;
		}

		sf::RenderStates states;
		states.texture = mTexture;
		states.transform = getGlobalTransform();
		target.draw(mVertices, states);
	}
}

void ParticleComponent::onSpawn()
{
	getWorld().getParticleSystem().registerParticleComponent(this);
}

void ParticleComponent::onDestroy()
{
	getWorld().getParticleSystem().unregisterParticleComponent(this);
}

U32 ParticleComponent::computeParticleCount(Time dt)
{
	// We want to fulfill the desired particle rate as exact as possible. Since the amount of emitted particles per frame is
	// integral, we have to emit sometimes more and sometimes less. mParticleDifference takes care of the deviation each frame.
	F32 particleAmount = mEmissionRate * dt.asSeconds() + mEmissionDifference;
	U32 nbParticles = (U32)particleAmount;

	// Compute difference for next frame, return current amount
	mEmissionDifference = particleAmount - nbParticles;
	return nbParticles;
}

void ParticleComponent::updateParticle(Particle& particle, Time dt)
{
	particle.passedLifetime += dt;
	particle.position += dt.asSeconds() * particle.velocity;
	particle.rotation += dt.asSeconds() * particle.rotationSpeed;
}

void ParticleComponent::computeVertices()
{
	mVertices.clear();
	U32 size = mParticles.size();
	for (U32 i = 0; i < size; i++)
	{
		sf::Transform t;
		t.translate(toSF(mParticles[i].position));
		t.rotate(mParticles[i].rotation);
		t.scale(toSF(mParticles[i].scale));

		ASSERT(mParticles[i].textureIndex == 0 || mParticles[i].textureIndex < mTextureRects.size());

		const Quad& quad(mQuads[mParticles[i].textureIndex]);
		for (U32 j = 0; j < 6; j++)
		{
			sf::Vertex v;
			v.position = t.transformPoint(quad[j].position);
			v.texCoords = quad[j].texCoords;
			v.color = toSF(mParticles[i].color);
			mVertices.append(v);
		}
	}
}

void ParticleComponent::computeQuads()
{
	ASSERT(mTexture != nullptr);

	if (mTextureRects.empty())
	{
		mQuads.resize(1);
		computeQuad(mQuads[0], sf::IntRect(0, 0, mTexture->getSize().x, mTexture->getSize().y));
	}
	else
	{
		mQuads.resize(mTextureRects.size());
		for (U32 i = 0; i < mTextureRects.size(); i++)
		{
			computeQuad(mQuads[i], mTextureRects[i]);
		}
	}
}

void ParticleComponent::computeQuad(Quad& quad, const sf::IntRect& tRect)
{
	sf::FloatRect rect((sf::FloatRect)tRect);

	quad[0].texCoords = sf::Vector2f(rect.left, rect.top);
	quad[1].texCoords = sf::Vector2f(rect.left + rect.width, rect.top);
	quad[2].texCoords = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
	quad[4].texCoords = sf::Vector2f(rect.left, rect.top + rect.height);
	quad[3].texCoords = quad[2].texCoords;
	quad[5].texCoords = quad[0].texCoords;

	quad[0].position = sf::Vector2f(-rect.width, -rect.height) / 2.0f;
	quad[1].position = sf::Vector2f(rect.width, -rect.height) / 2.0f;
	quad[2].position = sf::Vector2f(rect.width, rect.height) / 2.0f;
	quad[4].position = sf::Vector2f(-rect.width, rect.height) / 2.0f;
	quad[3].position = quad[2].position;
	quad[5].position = quad[0].position;
}

} // namespace oe