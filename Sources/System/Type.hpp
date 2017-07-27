#ifndef OE_TYPE_HPP
#define OE_TYPE_HPP

#include "Hash.hpp"

#define TYPE(CLASS_NAME) static const std::string getStaticType() { return #CLASS_NAME; } \
						 static constexpr unsigned int getStaticTypeId() { return oe::hashCompile(#CLASS_NAME); } \
                         virtual const std::string getType() const { return getStaticType(); } \
					     virtual const unsigned int getTypeId() const { return getStaticTypeId(); }

#endif // OE_TYPE_HPP