#include <nob/shv.hpp>

#include <rua/any_ptr.hpp>

#include <array>

namespace nob {
	namespace shv {
		int (WINAPI *createTexture)(const char *texFileName);

		void (WINAPI *drawTexture)(
			int id, int index, int level, int time,
			float sizeX, float sizeY, float centerX, float centerY,
			float posX, float posY, float rotation, float screenHeightScaleFactor,
			float r, float g, float b, float a
		);

		void (WINAPI *presentCallbackRegister)(PresentCallback cb);
		void (WINAPI *presentCallbackUnregister)(PresentCallback cb);

		void (WINAPI *keyboardHandlerRegister)(KeyboardHandler handler);
		void (WINAPI *keyboardHandlerUnregister)(KeyboardHandler handler);

		void (WINAPI *scriptWait)(DWORD time);
		void (WINAPI *scriptRegister)(HMODULE module, void(WINAPI *LP_SCRIPT_MAIN)());
		void (WINAPI *scriptRegisterAdditionalThread)(HMODULE module, void(WINAPI *LP_SCRIPT_MAIN)());
		void (WINAPI *scriptUnregister)(HMODULE module);

		void (WINAPI *nativeInit)(UINT64 hash);
		void (WINAPI *nativePush64)(UINT64 val);
		PUINT64 (WINAPI *nativeCall)();

		UINT64 *(WINAPI *getGlobalPtr)(int globalId);

		int (WINAPI *worldGetAllVehicles)(int *arr, int arrSize);
		int (WINAPI *worldGetAllPeds)(int *arr, int arrSize);
		int (WINAPI *worldGetAllObjects)(int *arr, int arrSize);
		int (WINAPI *worldGetAllPickups)(int *arr, int arrSize);

		BYTE *(WINAPI *getScriptHandleBaseAddress)(int handle);

		eGameVersion (WINAPI *getGameVersion)();

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
