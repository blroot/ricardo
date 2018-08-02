#pragma once

#include <vector>
#include "Object.h"

namespace ricardo {

	enum graphics_apis { DirectX11, };

	class Scene {
		public:
			Scene();
			void setResolution(int width, int height);
			void setGraphic_api(graphics_apis api);
			void addObject(Object* object);
			graphics_apis& getGraphicsAPI();
		private:
			std::vector<Object *> objects;
			int resolution_width;
			int resolution_height;
			graphics_apis graphic_api;
	};
}