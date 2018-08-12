#pragma once

#include "Scene.h"
#include <iostream>
#include "BasicShaders.ps.h"
#include "BasicShaders.vs.h"

using namespace DirectX;

namespace ricardo {

#define IDC_TOGGLEFULLSCREEN    1
#define IDC_TOGGLEREF           3
#define IDC_CHANGEDEVICE 4

	CDXUTTextHelper* g_pTxtHelper = nullptr;
	CDXUTDialogResourceManager  g_DialogResourceManager;
	CD3DSettingsDlg             g_D3DSettingsDlg;
	CDXUTDialog                 g_HUD;
	CDXUTDialog                 g_SampleUI;
	CFirstPersonCamera          g_Camera;
	XMMATRIX                    g_mCenterMesh;

	struct ShaderTransforms {
		XMMATRIX World;
		XMMATRIX View;
		XMMATRIX Projection;
	};

	template<typename handler>
	class Renderer {
	public:
		Scene scene;

		void HandleFrameRender() {
			static_cast<handler*>(this)->HandleFrameRender();
		};
		HRESULT HandleDeviceCreated() {
			return static_cast<handler*>(this)->HandleDeviceCreated();
		};
		HRESULT initialize() {
			return static_cast<handler*>(this)->initialize();
		};
		void reset() {
			static_cast<handler*>(this)->reset();
		};
		void InitApp() {
			static_cast<handler*>(this)->InitApp();
		};
		void setScene(Scene& scene) {
			this->scene = scene;
		}
	};

	class DX11Handler : public Renderer<DX11Handler> {
		friend class Renderer<DX11Handler>;
	public:
		CComPtr<ID3D11Buffer> CBuffer;
		CComPtr<ID3D11Buffer> IndexBuffer;
		CComPtr<ID3D11Buffer> VertexBuffer;
		CComPtr<ID3D11InputLayout> InputLayout;
		CComPtr<ID3D11VertexShader> BasicVS;
		CComPtr<ID3D11PixelShader> BasicPS;
		ShaderTransforms transforms;
		float RotationY = 0.0f;
		ID3D11Device* pd3dDevice;
		HRESULT hr;

		static void CALLBACK HandleFrameMove(double fTime, float fElapsedTime, void* pUserContext)
		{
			// Update the camera's position based on user input 
			g_Camera.FrameMove(fElapsedTime);
		};

		static bool CALLBACK HandleDeviceAcceptable(const CD3D11EnumAdapterInfo *AdapterInfo, UINT Output, const CD3D11EnumDeviceInfo *DeviceInfo,
			DXGI_FORMAT BackBufferFormat, bool bWindowed, void* pUserContext) {
			return true;
		};

		static HRESULT CALLBACK HandleDeviceCreated(_In_ ID3D11Device* pd3dDevice, 
			_In_ const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, _In_opt_ void* pUserContext) {

			DX11Handler *pRender = static_cast<DX11Handler *>(pUserContext);
			HRESULT hr = S_OK;
			pRender->reset();
			V_RETURN(pRender->initialize(pd3dDevice));

			auto pd3dImmediateContext = DXUTGetD3D11DeviceContext();
			V_RETURN(g_DialogResourceManager.OnD3D11CreateDevice(pd3dDevice, pd3dImmediateContext));
			V_RETURN(g_D3DSettingsDlg.OnD3D11CreateDevice(pd3dDevice));
			g_pTxtHelper = new CDXUTTextHelper(pd3dDevice, pd3dImmediateContext, &g_DialogResourceManager, 15);

			// Setup the camera's view parameters
			static const XMVECTORF32 s_vecEye = { 0.0f, 0.0f, -100.0f, 0.0f };
			g_Camera.SetViewParams(s_vecEye, g_XMZero);
			g_Camera.SetRotateButtons(TRUE, FALSE, FALSE);
			g_Camera.SetScalers(0.01f, 10.0f);
			g_Camera.SetDrag(true);
			g_Camera.SetEnableYAxisMovement(false);

			// We'll use this to set indoor scene boundaries
			//g_ViewerCamera.SetClipToBoundary(TRUE, &vMin, &vMax);

			return hr;
		};

		static void RenderText()
		{
			UINT nBackBufferHeight = DXUTGetDXGIBackBufferSurfaceDesc()->Height;

			g_pTxtHelper->Begin();
			g_pTxtHelper->SetInsertionPos(2, 0);
			g_pTxtHelper->SetForegroundColor(Colors::Yellow);
			g_pTxtHelper->DrawTextLine(DXUTGetFrameStats(DXUTIsVsyncEnabled()));
			g_pTxtHelper->DrawTextLine(DXUTGetDeviceStats());
			g_pTxtHelper->End();
		};

		static HRESULT CALLBACK HandleResizedSwapChain(_In_ ID3D11Device* pd3dDevice, _In_ IDXGISwapChain* pSwapChain,
			_In_ const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, _In_opt_ void* pUserContext) {

			DX11Handler *pRender = static_cast<DX11Handler *>(pUserContext);
			HRESULT hr;

			V_RETURN(g_DialogResourceManager.OnD3D11ResizedSwapChain(pd3dDevice, pBackBufferSurfaceDesc));
			V_RETURN(g_D3DSettingsDlg.OnD3D11ResizedSwapChain(pd3dDevice, pBackBufferSurfaceDesc));

			// Setup the camera's projection parameters
			float fAspectRatio = pBackBufferSurfaceDesc->Width / (FLOAT)pBackBufferSurfaceDesc->Height;
			g_Camera.SetProjParams(XM_PI / 4, fAspectRatio, 2.0f, 4000.0f);

			g_HUD.SetLocation(pBackBufferSurfaceDesc->Width - 170, 0);
			g_HUD.SetSize(170, 170);
			g_SampleUI.SetLocation(pBackBufferSurfaceDesc->Width - 170, pBackBufferSurfaceDesc->Height - 300);
			g_SampleUI.SetSize(170, 300);

			return S_OK;
		};

		static void CALLBACK HandleFrameRender(_In_ ID3D11Device* pd3dDevice, _In_ ID3D11DeviceContext* pd3dImmediateContext, 
			_In_ double fTime, _In_ float fElapsedTime, _In_opt_ void* pUserContext) {

			DX11Handler *pRender = static_cast<DX11Handler *>(pUserContext);
			ID3D11RenderTargetView *rtv = DXUTGetD3D11RenderTargetView();

			pd3dImmediateContext->ClearRenderTargetView(rtv, DirectX::Colors::DarkSlateBlue);

			// Get the projection & view matrix from the camera class
			pRender->transforms.Projection = g_Camera.GetProjMatrix();
			pRender->transforms.View = g_Camera.GetViewMatrix();

			// Set the per object constant data
			// We don't need World transform - set to identity for now
			pRender->transforms.World = XMMatrixIdentity();

			RECT r = DXUTGetWindowClientRect();

			// Las matrices en constant buffers vienen column-major, por convencion.
			pRender->transforms.World = XMMatrixTranspose(pRender->transforms.World);
			pRender->transforms.View = XMMatrixTranspose(pRender->transforms.View);
			pRender->transforms.Projection = XMMatrixTranspose(pRender->transforms.Projection);
			pd3dImmediateContext->UpdateSubresource(pRender->CBuffer, 0, nullptr, &pRender->transforms, 0, 0);

			D3D11_VIEWPORT viewports[1] = { 0, 0, (FLOAT)r.right, (FLOAT)r.bottom, 0.0f, 1.0f };
			ID3D11RenderTargetView *rtvViews[1] = { rtv };
			ID3D11Buffer *vertexBuffers[1] = { pRender->VertexBuffer };
			UINT strides[1] = { sizeof(InfoVertex) };
			UINT offsets[1] = { 0 };
			pd3dImmediateContext->IASetVertexBuffers(0, 1, vertexBuffers, strides, offsets);
			pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			pd3dImmediateContext->IASetIndexBuffer(pRender->IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
			pd3dImmediateContext->IASetInputLayout(pRender->InputLayout);
			pd3dImmediateContext->VSSetShader(pRender->BasicVS, nullptr, 0);
			pd3dImmediateContext->VSSetConstantBuffers(0, 1, &pRender->CBuffer.p);
			pd3dImmediateContext->RSSetViewports(1, viewports);
			pd3dImmediateContext->PSSetShader(pRender->BasicPS, nullptr, 0);
			pd3dImmediateContext->OMSetRenderTargets(1, rtvViews, nullptr);
			pd3dImmediateContext->DrawIndexed(pRender->scene.indices.size(), 0, 0);

			DXUT_BeginPerfEvent(DXUT_PERFEVENTCOLOR, L"HUD / Stats");
			g_HUD.OnRender(fElapsedTime);
			g_SampleUI.OnRender(fElapsedTime);
			RenderText();
			DXUT_EndPerfEvent();
		};

		static void CALLBACK HandleGUIEvent(UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext) {
			switch (nControlID) {
			case IDC_TOGGLEFULLSCREEN:
				DXUTToggleFullScreen(); break;
			}

		};

		static LRESULT CALLBACK HandleMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing,
			void* pUserContext) {

			// Pass all windows messages to camera so it can respond to user input
			g_Camera.HandleMessages(hWnd, uMsg, wParam, lParam);

			return 0;
		};

		static void CALLBACK HandleDestroyDevice(void* pUserContext)
		{
			g_DialogResourceManager.OnD3D11DestroyDevice();
			g_D3DSettingsDlg.OnD3D11DestroyDevice();
			DXUTGetGlobalResourceCache().OnDestroyDevice();
			SAFE_DELETE(g_pTxtHelper);
		};

		static void CALLBACK HandleReleasingSwapChain(void* pUserContext)
		{
			g_DialogResourceManager.OnD3D11ReleasingSwapChain();
		}

	private:
		void InitApp() {
			g_D3DSettingsDlg.Init(&g_DialogResourceManager);
			g_HUD.Init(&g_DialogResourceManager);
			g_SampleUI.Init(&g_DialogResourceManager);

			g_HUD.SetCallback(HandleGUIEvent);
			int iY = 30;
			int iYo = 26;
			g_HUD.AddButton(IDC_TOGGLEFULLSCREEN, L"Toggle full screen", 0, iY, 170, 23);
			g_SampleUI.SetCallback(HandleGUIEvent); iY = 10;
		};

		void reset() {
			RotationY = 0.0f;
			CBuffer = nullptr;
			IndexBuffer = nullptr;
			VertexBuffer = nullptr;
			InputLayout = nullptr;
			BasicVS = nullptr;
			BasicPS = nullptr;
		};

		HRESULT initialize(_In_ ID3D11Device* pd3dDevice) {
			HRESULT hr = S_OK;

			// Create vertex buffer
			CD3D11_BUFFER_DESC vbDesc(scene.vertices.size() * sizeof(scene.vertices[0]), D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_IMMUTABLE);
			D3D11_SUBRESOURCE_DATA vbData = { scene.vertices.data(), 0, 0 };
			V_RETURN(pd3dDevice->CreateBuffer(&vbDesc, &vbData, &VertexBuffer));

			// Create constant buffer
			CD3D11_BUFFER_DESC cbDesc(sizeof(transforms), D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DEFAULT);
			V_RETURN(pd3dDevice->CreateBuffer(&cbDesc, nullptr, &CBuffer));

			CD3D11_BUFFER_DESC ibDesc(scene.indices.size() * sizeof(scene.indices[0]), D3D11_BIND_INDEX_BUFFER, D3D11_USAGE_DEFAULT);
			D3D11_SUBRESOURCE_DATA ibData = { scene.indices.data(), 0, 0 };
			V_RETURN(pd3dDevice->CreateBuffer(&ibDesc, &ibData, &IndexBuffer));

			// LPCSTR SemanticName; UINT SemanticIndex; DXGI_FORMAT Format; UINT InputSlot;
			// UINT AlignedByteOffset; D3D11_INPUT_CLASSIFICATION InputSlotClass; UINT InstanceDataStepRate;
			D3D11_INPUT_ELEMENT_DESC inputElementDescs[2] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			};
			V_RETURN(pd3dDevice->CreateInputLayout(inputElementDescs, _countof(inputElementDescs), g_vs_main, sizeof(g_vs_main), &InputLayout));
			V_RETURN(pd3dDevice->CreateVertexShader(g_vs_main, sizeof(g_vs_main), nullptr, &BasicVS));
			V_RETURN(pd3dDevice->CreatePixelShader(g_ps_main, sizeof(g_ps_main), nullptr, &BasicPS));

			return hr;
		};
	};
}