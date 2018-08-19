#pragma once

#include <vector>
#include "Triangle.h"
#include "Mesh.h"

namespace ricardo {

	enum graphics_apis { DirectX11, };

	struct InfoVertex {
		vec3 Pos;
		vec4 Color;
	};

	class Scene {
		public:
			Scene();
			void setResolution(int width, int height);
			void setGraphic_api(graphics_apis api);
			void addTriangle(Triangle* triangle);
			void addMesh(Mesh* mesh);
			graphics_apis& getGraphicsAPI();
			int& getResolution_width();
			int& getResolution_height();
			std::vector<Triangle *>& getTriangles();
			std::vector<Mesh *>& getMeshes();
			std::vector<WORD> getIndices();
			void addIndex(WORD index);
			void addVertex(vec3 vertex, vec4 color);
			std::vector<WORD> indices;
			std::vector<InfoVertex> vertices;
			void setCameraEye(vec3 eye);
			void setCameraLookAt(vec3 lookAt);
			void setCameraRotationScaler(float rotationScaler);
			void setCameraMoveScaler(float moveScaler);
			void setCameraVMin(vec3 vMin);
			void setCameraVMax(vec3 vMax);
			vec3& getCameraEye();
			vec3& getCameraLookAt();
			float& getCameraRotationScaler();
			float& getCameraMoveScaler();
			vec3& getCameraVMin();
			vec3& getCameraVMax();
		private:
			std::vector<Mesh *> meshes;
			std::vector<Triangle *> triangles;
			int resolution_width;
			int resolution_height;
			vec3 cameraEye;
			vec3 cameraLookAt;
			float cameraRotationScaler;
			float cameraMoveScaler;
			vec3 cameraVMin;
			vec3 cameraVMax;
			graphics_apis graphic_api;
	};
}