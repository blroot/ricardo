#pragma once

#include "Scene.h"
#include <iostream>

namespace ricardo {

	template<typename handler>
	class Renderer {
	public:
		int render() {
			return static_cast<handler*>(this)->render();
		};
		void otro() {
			std::cout << "OTRO" << std::endl;
		};
	};

	class DX11Handler : public Renderer<DX11Handler> {
		friend class Renderer<DX11Handler>;
	private:
		int render() {
			std::cout << "DX11" << std::endl;
			return 0;
		};
	};
}