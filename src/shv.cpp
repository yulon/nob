#include <nob/shv.hpp>

#include <rua/any_ptr.hpp>

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
				HMODULE dll = nullptr;

				for (size_t i = 0; i < _module_names.size(); ++i) {
					dll = GetModuleHandleW(_module_names[i]);
					if (dll) {
						break;
					}
				}
				if (!dll) {
					for (size_t i = 0; i < _module_names.size(); ++i) {
						dll = LoadLibraryW(_module_names[i]);
						if (dll) {
							break;
						}
					}
					if (!dll) {
						return false;
					}
				}

				#define GPA(_v, _n) _v = rua::any_ptr(GetProcAddress(dll, _n))

				GPA(createTexture, "?createTexture@@YAHPEBD@Z");

				GPA(drawTexture, "?drawTexture@@YAXHHHHMMMMMMMMMMMM@Z");

				GPA(presentCallbackRegister, "?presentCallbackRegister@@YAXP6AXPEAX@Z@Z");
				GPA(presentCallbackUnregister, "?presentCallbackUnregister@@YAXP6AXPEAX@Z@Z");

				GPA(keyboardHandlerRegister, "?keyboardHandlerRegister@@YAXP6AXKGEHHHH@Z@Z");
				GPA(keyboardHandlerUnregister, "?keyboardHandlerUnregister@@YAXP6AXKGEHHHH@Z@Z");

				GPA(scriptWait, "?scriptWait@@YAXK@Z");
				GPA(scriptRegister, "?scriptRegister@@YAXPEAUHINSTANCE__@@P6AXXZ@Z");
				GPA(scriptRegisterAdditionalThread, "?scriptRegisterAdditionalThread@@YAXPEAUHINSTANCE__@@P6AXXZ@Z");
				GPA(scriptUnregister, "?scriptUnregister@@YAXPEAUHINSTANCE__@@@Z");

				GPA(nativeInit, "?nativeInit@@YAX_K@Z");
				GPA(nativePush64, "?nativePush64@@YAX_K@Z");
				GPA(nativeCall, "?nativeCall@@YAPEA_KXZ");

				GPA(getGlobalPtr, "?getGlobalPtr@@YAPEA_KH@Z");

				GPA(worldGetAllVehicles, "?worldGetAllVehicles@@YAHPEAHH@Z");
				GPA(worldGetAllPeds, "?worldGetAllPeds@@YAHPEAHH@Z");
				GPA(worldGetAllObjects, "?worldGetAllObjects@@YAHPEAHH@Z");
				GPA(worldGetAllPickups, "?worldGetAllPickups@@YAHPEAHH@Z");

				GPA(getScriptHandleBaseAddress, "?getScriptHandleBaseAddress@@YAPEAEH@Z");

				GPA(getGameVersion, "?getGameVersion@@YA?AW4eGameVersion@@XZ");

				return true;
			})();
			return valid;
		}
	} /* shv */
} /* nob */
