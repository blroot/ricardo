// ricardo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SceneReader.h"
#include "Scene.h"
#include <iostream>
#include "Renderer.h"

using namespace ricardo;

void printHelp()
{
	std::cout << "Usage: ./ricardo <scene file>" << std::endl;
}

inline HRESULT AtlCheck(HRESULT hr) {
	if (SUCCEEDED(hr)) return hr;
	AtlThrow(hr);
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		printHelp();
		return 1;
	}

	SceneReader scene_reader = SceneReader(argv[1]);
	Scene scene = scene_reader.read();

	// Building the renderer instance
	Renderer<DX11Handler> *renderer = new DX11Handler();
	renderer->setScene(scene);

	try {
		renderer->InitApp();
		AtlCheck(DXUTInit());
		AtlCheck(DXUTCreateWindow(L"Ricardo"));
		DXUTDeviceSettings deviceSettings;
		DXUTApplyDefaultDeviceSettings(&deviceSettings);
	#if _DEBUG
		deviceSettings.d3d11.CreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
		deviceSettings.d3d11.DriverType = D3D_DRIVER_TYPE_WARP;
	#endif
		DXUTSetCallbackD3D11DeviceCreated(DX11Handler::HandleDeviceCreated, renderer);
		DXUTSetCallbackD3D11SwapChainResized(DX11Handler::HandleResizedSwapChain, renderer);
		DXUTSetCallbackD3D11FrameRender(DX11Handler::HandleFrameRender, renderer);
		AtlCheck(DXUTCreateDeviceFromSettings(&deviceSettings));
		AtlCheck(DXUTMainLoop());
		renderer->reset();
	}
	catch (const CAtlException &e) {
		wprintf(L"failed with hr=0x%08x", (HRESULT)e);
	}

    return 0;
}
