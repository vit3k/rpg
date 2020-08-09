#include "Component.h"

namespace EntitySystem
{
	TypeId ScriptComponentTypeId()
	{
		return ClassTypeId<Component>::GetScriptTypeId();
	}
}