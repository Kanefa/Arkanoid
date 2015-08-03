#ifndef COMPONENT_H
#define COMPONENT_H

using FrameTime = float;

class Entity;

struct Component
{
							Component() = default;
	virtual					~Component();
							Component(const Component &) = delete;
	Component &				operator=(const Component &) = delete;

	virtual void			init();
	virtual void			update(FrameTime ftStep);
	virtual void			draw();

	Entity					*mEntity{ nullptr };
};

#endif
