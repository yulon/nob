#include <nob/dx.hpp>

#include <minhook.hpp>

#include <rua/gnc/any_ptr.hpp>

#include <d3d11.h>

namespace nob {
	namespace dx {
		static rua::any_ptr *_dxgi_swap_chain_vtab() {
			WNDCLASSEXW wc = { sizeof(WNDCLASSEXW), CS_CLASSDC, DefWindowProcW, 0, 0, GetModuleHandleA(nullptr), nullptr, nullptr, nullptr, nullptr, L"NobDxgiTmpWnd", nullptr };
			RegisterClassExW(&wc);
			HWND hWnd = CreateWindowW(L"NobDxgiTmpWnd", nullptr, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, nullptr, nullptr, wc.hInstance, NULL);

			D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };

			UINT flags = 0;
			#ifndef NDEBUG
				flags |= D3D11_CREATE_DEVICE_DEBUG;
			#endif

			DXGI_SWAP_CHAIN_DESC sc_dsc;
			memset(&sc_dsc, 0, sizeof(sc_dsc));
			sc_dsc.BufferCount = 1;
			sc_dsc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sc_dsc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sc_dsc.OutputWindow = hWnd;
			sc_dsc.SampleDesc.Count = 1;
			sc_dsc.Windowed = ((GetWindowLongPtr(hWnd, GWL_STYLE) & WS_POPUP) != 0) ? false : true;
			sc_dsc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			sc_dsc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			sc_dsc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

			ID3D11Device *dev = nullptr;
			IDXGISwapChain *sc = nullptr;

			if (FAILED(D3D11CreateDeviceAndSwapChain(
				nullptr,
				D3D_DRIVER_TYPE_HARDWARE,
				nullptr,
				flags,
				levels,
				sizeof(levels) / sizeof(D3D_FEATURE_LEVEL),
				D3D11_SDK_VERSION,
				&sc_dsc,
				&sc,
				&dev,
				nullptr,
				nullptr
			))) {
				return nullptr;
			}

			auto vtab = *(rua::any_ptr **)sc;

			sc->Release();
			dev->Release();
			DestroyWindow(hWnd);

			return vtab;
		}

		static minhook<HRESULT (*)(IDXGISwapChain *, UINT, UINT)> _IDXGISwapChainPresent_hk;

		void _hook() {
			if (_IDXGISwapChainPresent_hk) {
				return;
			}
			auto vtab = _dxgi_swap_chain_vtab();
			if (vtab) {
				_IDXGISwapChainPresent_hk.install(
					vtab[8],
					[](IDXGISwapChain *th1s, UINT SyncInterval, UINT Flags) -> HRESULT {
						for (auto &hdr : on_render::handler_list()) {
							hdr(th1s);
						}
						return _IDXGISwapChainPresent_hk.original(th1s, SyncInterval, Flags);
					}
				);
			}
		}

		void _handle(void *sc) {
			for (auto &hdr : on_render::handler_list()) {
				hdr(reinterpret_cast<IDXGISwapChain *>(sc));
			}
		}
	}
}
