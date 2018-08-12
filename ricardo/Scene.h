#pragma once

#include <vector>
#include "Object.h"

namespace ricardo {

	enum graphics_apis { DirectX11, };

	struct InfoVertex {
		vec4 Pos;
		vec4 Color;
	};

	class Scene {
		public:
			Scene();
			void setResolution(int width, int height);
			void setGraphic_api(graphics_apis api);
			void addObject(Object* object);
			graphics_apis& getGraphicsAPI();
			int& getResolution_width();
			int& getResolution_height();
			std::vector<Object *>& getObjects();
			std::vector<WORD> getIndices();
			std::vector<InfoVertex> getVertices();
			void addIndex(WORD index);
			void addVertex(vec4 vertex, vec4 color);
			std::vector<WORD> indices;
			std::vector<InfoVertex> vertices;
		private:
			std::vector<Object *> objects;
			int resolution_width;
			int resolution_height;
			graphics_apis graphic_api;
	};
}