#ifndef OE_COMPONENT_HPP
#define OE_COMPONENT_HPP

namespace oe
{

class Entity;

class Component
{
	public:
		Component();

		Entity* getParent();
		bool hasParent() const;

	private:
		friend Entity;
		void setParent(Entity* parent);
		virtual void onAttach();
		virtual void onDetach();

	protected:
		Entity* mParent;
};

} // namespace oe

#endif // OE_COMPONENT_HPP
