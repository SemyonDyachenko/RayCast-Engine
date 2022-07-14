#include "GuiConsole.h"
#include "ObjectAdditor.h"


class EntityCreator
{
public:
	EntityCreator();
	virtual ~EntityCreator() = default;

	void Update(float deltaTime);

	void Render(ObjectAdditor & objectAdditor);
};

