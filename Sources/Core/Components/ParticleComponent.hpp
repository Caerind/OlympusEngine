#ifndef OE_PARTICLECOMPONENT_HPP
#define OE_PARTICLECOMPONENT_HPP

#include <array>
#include <functional>

#include <SFML/Graphics/VertexArray.hpp>

#include "../../System/Distribution.hpp"

#include "../RenderableComponent.hpp"

namespace oe
{

class ParticleComponent : public RenderableComponent
{
    public:
		using Quad = std::array<sf::Vertex, 6>;
		
		class Particle
		{
			public:
				Particle(Time lifetime) : position(), velocity(), rotation(), rotationSpeed(), scale(1.0f, 1.0f), color(255, 255, 255), textureIndex(0), passedLifetime(Time::Zero), totalLifetime(lifetime) {}

				Vector2 position;
				Vector2 velocity;
				F32 rotation;
				F32 rotationSpeed;
				Vector2 scale;
				Color color;
				U32 textureIndex;

				Time passedLifetime;
				Time totalLifetime;
		};

		using Affector = std::function<void(Particle&, Time)>;

	public:
		ParticleComponent(Entity& entity);

		void setTexture(ResourceId texture);
		void setTexture(sf::Texture& texture);
		U32 addTextureRect(U32 x, U32 y, U32 w, U32 h);

		void addAffector(const Affector& affector);
		void clearAffectors();

		void update(Time dt);

		U32 getParticleCount() const;
		void clearParticles();

		void enableEmission();
		void disableEmission();

		void setEmissionRate(F32 particlesPerSecond);
		void setParticleLifetime(Distribution<Time> lifetime);
		void setParticlePosition(Distribution<Vector2> position);
		void setParticleVelocity(Distribution<Vector2> velocity);
		void setParticleRotation(Distribution<F32> rotation);
		void setParticleRotationSpeed(Distribution<F32> rotationSpeed);
		void setParticleScale(Distribution<Vector2> scale);
		void setParticleColor(Distribution<Color> color);
		void setParticleTextureIndex(Distribution<U32> textureIndex);

		void emitParticle();
		void emitParticles(U32 particleAmount);

		void addGravity(F32 gravityFactor);

		virtual void onSpawn(); // override RenderableComponent::onSpawn to register as ParticleComponent
		virtual void onDestroy(); // override RenderableComponent::onDestrop to unregister as ParticleComponent

		virtual void render(sf::RenderTarget& target);

	private:
		U32 computeParticleCount(Time dt);
		void updateParticle(Particle& particle, Time dt);
		void computeVertices();
		void computeQuads();
		void computeQuad(Quad& quad, const sf::IntRect& rect);

	private:
		std::vector<Particle> mParticles;
		std::vector<Affector> mAffectors;

		sf::Texture* mTexture;
		std::vector<sf::IntRect> mTextureRects;

		sf::VertexArray mVertices;
		bool mNeedsVertexUpdate;
		std::vector<Quad> mQuads;
		bool mNeedsQuadUpdate;

		bool mEmitting;
		F32 mEmissionRate;
		F32 mEmissionDifference;

		Distribution<Time> mParticleLifetime;
		Distribution<Vector2> mParticlePosition;
		Distribution<Vector2> mParticleVelocity;
		Distribution<F32> mParticleRotation;
		Distribution<F32> mParticleRotationSpeed;
		Distribution<Vector2> mParticleScale;
		Distribution<Color> mParticleColor;
		Distribution<U32> mParticleTextureIndex;
};

} // namespace oe

#endif // OE_PARTICLECOMPONENT_HPP
