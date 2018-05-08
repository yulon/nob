#include <nob/shv.hpp>

#include <array>

namespace nob {
	namespace shv {
		int (*createTexture)(const char *texFileName);

		void (*drawTexture)(
			int id, int index, int level, int time,
			float sizeX, float sizeY, float centerX, float centerY,
			float posX, float posY, float rotation, float screenHeightScaleFactor,
			float r, float g, float b, float a
		);

		void (*presentCallbackRegister)(PresentCallback cb);
		void (*presentCallbackUnregister)(PresentCallback cb);

		void (*keyboardHandlerRegister)(KeyboardHandler handler);
		void (*keyboardHandlerUnregister)(KeyboardHandler handler);

		void (*scriptWait)(DWORD time);
		void (*scriptRegister)(HMODULE module, void(*LP_SCRIPT_MAIN)());
		void (*scriptRegisterAdditionalThread)(HMODULE module, void(*LP_SCRIPT_MAIN)());
		void (*scriptUnregister)(HMODULE module);

		void (*nativeInit)(UINT64 hash);
		void (*nativePush64)(UINT64 val);
		PUINT64 (*nativeCall)();

		UINT64 *(*getGlobalPtr)(int globalId);

		int (*worldGetAllVehicles)(int *arr, int arrSize);
		int (*worldGetAllPeds)(int *arr, int arrSize);
		int (*worldGetAllObjects)(int *arr, int arrSize);
		int (*worldGetAllPickups)(int *arr, int arrSize);

		BYTE *(*getScriptHandleBaseAddress)(int handle);

		eGameVersion (*getGameVersion)();

		constexpr const std::array<LPCWSTR, 2> _module_names {{
			L"ScriptHookV.dll",
			L"OpenVHook.dll"
		}};

		bool _init() {
			static bool valid = ([]()->bool {
				HMODULE dll;
				for (size_t i = 0; i < _module_names.size(); ++i) {
					dll = GetModuleHandleW(_module_names[i]);
					if (dll) {
						goto get_func;
					}
				}
				for (size_t i = 0; i < _module_names.size(); ++i) {
					dll = LoadLibraryW(_module_names[i]);
					if (dll) {
						goto get_func;
					}
				}
				return false;

				get_func:

				createTexture = (int (*)(const char *texFileName))GetProcAddress(dll, "?createTexture@@YAHPEBD@Z");

				drawTexture = (void (*)(
					int id, int index, int level, int time,
					float sizeX, float sizeY, float centerX, float centerY,
					float posX, float posY, float rotation, float screenHeightScaleFactor,
					float r, float g, float b, float a
				))GetProcAddress(dll, "?drawTexture@@YAXHHHHMMMMMMMMMMMM@Z");

				presentCallbackRegister = (void (*)(PresentCallback cb))GetProcAddress(dll, "?presentCallbackRegister@@YAXP6AXPEAX@Z@Z");
				presentCallbackUnregister = (void (*)(PresentCallback cb))GetProcAddress(dll, "?presentCallbackUnregister@@YAXP6AXPEAX@Z@Z");

				keyboardHandlerRegister = (void (*)(KeyboardHandler handler))GetProcAddress(dll, "?keyboardHandlerRegister@@YAXP6AXKGEHHHH@Z@Z");
				keyboardHandlerUnregister = (void (*)(KeyboardHandler handler))GetProcAddress(dll, "?keyboardHandlerUnregister@@YAXP6AXKGEHHHH@Z@Z");

				scriptWait = (void (*)(DWORD time))GetProcAddress(dll, "?scriptWait@@YAXK@Z");
				scriptRegister = (void (*)(HMODULE module, void(*LP_SCRIPT_MAIN)()))GetProcAddress(dll, "?scriptRegister@@YAXPEAUHINSTANCE__@@P6AXXZ@Z");
				scriptRegisterAdditionalThread = (void (*)(HMODULE module, void(*LP_SCRIPT_MAIN)()))GetProcAddress(dll, "?scriptRegisterAdditionalThread@@YAXPEAUHINSTANCE__@@P6AXXZ@Z");
				scriptUnregister = (void (*)(HMODULE module))GetProcAddress(dll, "?scriptUnregister@@YAXPEAUHINSTANCE__@@@Z");

				nativeInit = (void (*)(UINT64 hash))GetProcAddress(dll, "?nativeInit@@YAX_K@Z");
				nativePush64 = (void (*)(UINT64 val))GetProcAddress(dll, "?nativePush64@@YAX_K@Z");
				nativeCall = (PUINT64 (*)())GetProcAddress(dll, "?nativeCall@@YAPEA_KXZ");

				getGlobalPtr = (UINT64 *(*)(int globalId))GetProcAddress(dll, "?getGlobalPtr@@YAPEA_KH@Z");

				worldGetAllVehicles = (int (*)(int *arr, int arrSize))GetProcAddress(dll, "?worldGetAllVehicles@@YAHPEAHH@Z");
				worldGetAllPeds = (int (*)(int *arr, int arrSize))GetProcAddress(dll, "?worldGetAllPeds@@YAHPEAHH@Z");
				worldGetAllObjects = (int (*)(int *arr, int arrSize))GetProcAddress(dll, "?worldGetAllObjects@@YAHPEAHH@Z");
				worldGetAllPickups = (int (*)(int *arr, int arrSize))GetProcAddress(dll, "?worldGetAllPickups@@YAHPEAHH@Z");

				getScriptHandleBaseAddress = (BYTE *(*)(int handle))GetProcAddress(dll, "?getScriptHandleBaseAddress@@YAPEAEH@Z");

				getGameVersion = (eGameVersion (*)())GetProcAddress(dll, "?getGameVersion@@YA?AW4eGameVersion@@XZ");

				return true;
			})();
			return valid;
		}
	} /* shv */
} /* nob */
