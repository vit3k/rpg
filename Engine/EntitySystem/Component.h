#ifndef COMPONENT_H
#define COMPONENT_H

#include "ClassTypeId.h"
#include <bitset>
#include <memory>
#include <string>

namespace EntitySystem {
	class Component {
	
	};

	template <class T>
	TypeId ComponentTypeId()
	{
		return ClassTypeId<Component>::GetTypeId<T>();
	}

	TypeId ScriptComponentTypeId();

	using ComponentList = std::bitset<32>;

	typedef std::shared_ptr<Component> ComponentSp;
}

#endif