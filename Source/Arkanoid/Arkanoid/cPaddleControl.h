#ifndef CPADDLECONTROL_H
#define CPADDLECONTROL_H

#include "component.h"

using FrameTime = float;

struct CPhysics;

struct CPaddleControl : Component
{
							CPaddleControl() = default;
							CPaddleControl(const CPaddleControl &) = delete;
	CPaddleControl &		operator=(const CPaddleControl &) = delete;

	virtual void			init() override;
	virtual void			update(FrameTime ftStep) override;

	const float				mVelocity{0.6f};
	CPhysics				*mCPhysics{nullptr};
};

#endif
