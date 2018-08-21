#pragma once

#include "DXUTcamera.h"
#include "stdafx.h"

using namespace DirectX;

namespace ricardo {

	class RicardoFPSCamera : public CFirstPersonCamera {
	public:
		DirectX::XMFLOAT3 GetVelocity() const { return m_vVelocity; }
		DirectX::XMFLOAT3 GetDir() const { return m_vKeyboardDirection; }
	};
}
