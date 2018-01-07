/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com
		 (C) Alexander Blade 2015-2016
*/

#pragma once

#include <windows.h>

namespace nob {
	namespace shv {
		/* textures */

		// Create texture
		//	texFileName	- texture file name, it's best to specify full texture path and use PNG textures
		//	returns	internal texture id
		//	Texture deletion is performed automatically when game reloads scripts
		//	Can be called only in the same thread as natives

		extern int (WINAPI *createTexture)(const char *texFileName);

		// Draw texture
		//	id		-	texture id recieved from createTexture()
		//	index	-	each texture can have up to 64 different instances on screen at one time
		//	level	-	draw level, being used in global draw order, texture instance with least level draws first
		//	time	-	how much time (ms) texture instance will stay on screen, the amount of time should be enough
		//				for it to stay on screen until the next corresponding drawTexture() call
		//	sizeX,Y	-	size in screen space, should be in the range from 0.0 to 1.0, e.g setting this to 0.2 means that
		//				texture instance will take 20% of the screen space
		//	centerX,Y -	center position in texture space, e.g. 0.5 means real texture center
		//	posX,Y	-	position in screen space, [0.0, 0.0] - top left corner, [1.0, 1.0] - bottom right,
		//				texture instance is positioned according to it's center
		//	rotation -	should be in the range from 0.0 to 1.0
		//	screenHeightScaleFactor - screen aspect ratio, used for texture size correction, you can get it using natives
		//	r,g,b,a	-	color, should be in the range from 0.0 to 1.0
		//
		//	Texture instance draw parameters are updated each time script performs corresponding call to drawTexture()
		//	You should always check your textures layout for 16:9, 16:10 and 4:3 screen aspects, for ex. in 1280x720,
		//	1440x900 and 1024x768 screen resolutions, use windowed mode for this
		//	Can be called only in the same thread as natives

		extern void (WINAPI *drawTexture)(int id, int index, int level, int time,
			float sizeX, float sizeY, float centerX, float centerY,
			float posX, float posY, float rotation, float screenHeightScaleFactor,
			float r, float g, float b, float a);

		// IDXGISwapChain::Present callback
		// Called right before the actual Present method call, render test calls don't trigger callbacks
		// When the game uses DX10 it actually uses DX11 with DX10 feature level
		// Remember that you can't call natives inside
		// void OnPresent(IDXGISwapChain *swapChain);
		typedef void(WINAPI *PresentCallback)(void *);

		// Register IDXGISwapChain::Present callback
		// must be called on dll attach
		extern void (WINAPI *presentCallbackRegister)(PresentCallback cb);

		// Unregister IDXGISwapChain::Present callback
		// must be called on dll detach
		extern void (WINAPI *presentCallbackUnregister)(PresentCallback cb);

		/* keyboard */

		// DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow
		typedef void(WINAPI *KeyboardHandler)(DWORD, WORD, BYTE, BOOL, BOOL, BOOL, BOOL);

		// Register keyboard handler
		// must be called on dll attach
		extern void (WINAPI *keyboardHandlerRegister)(KeyboardHandler handler);

		// Unregister keyboard handler
		// must be called on dll detach
		extern void (WINAPI *keyboardHandlerUnregister)(KeyboardHandler handler);

		/* scripts */

		extern void (WINAPI *scriptWait)(DWORD time);
		extern void (WINAPI *scriptRegister)(HMODULE module, void(WINAPI *LP_SCRIPT_MAIN)());
		extern void (WINAPI *scriptRegisterAdditionalThread)(HMODULE module, void(WINAPI *LP_SCRIPT_MAIN)());
		extern void (WINAPI *scriptUnregister)(HMODULE module);

		extern void (WINAPI *nativeInit)(UINT64 hash);
		extern void (WINAPI *nativePush64)(UINT64 val);
		extern PUINT64 (WINAPI *nativeCall)();

		inline void WAIT(DWORD time) { scriptWait(time); }
		inline void TERMINATE() { WAIT(MAXDWORD); }

		// Returns pointer to global variable
		// make sure that you check game version before accessing globals because
		// ids may differ between patches
		extern UINT64 *(WINAPI *getGlobalPtr)(int globalId);

		/* world */

		// Get entities from internal pools
		// return value represents filled array elements count
		// can be called only in the same thread as natives
		extern int (WINAPI *worldGetAllVehicles)(int *arr, int arrSize);
		extern int (WINAPI *worldGetAllPeds)(int *arr, int arrSize);
		extern int (WINAPI *worldGetAllObjects)(int *arr, int arrSize);
		extern int (WINAPI *worldGetAllPickups)(int *arr, int arrSize);

		/* misc */

		// Returns base object pointer using it's script handle
		// make sure that you check game version before accessing object fields because
		// offsets may differ between patches
		extern BYTE *(WINAPI *getScriptHandleBaseAddress)(int handle);

		enum eGameVersion : int
		{
			VER_1_0_335_2_STEAM,
			VER_1_0_335_2_NOSTEAM,

			VER_1_0_350_1_STEAM,
			VER_1_0_350_2_NOSTEAM,

			VER_1_0_372_2_STEAM,
			VER_1_0_372_2_NOSTEAM,

			VER_1_0_393_2_STEAM,
			VER_1_0_393_2_NOSTEAM,

			VER_1_0_393_4_STEAM,
			VER_1_0_393_4_NOSTEAM,

			VER_1_0_463_1_STEAM,
			VER_1_0_463_1_NOSTEAM,

			VER_1_0_505_2_STEAM,
			VER_1_0_505_2_NOSTEAM,

			VER_1_0_573_1_STEAM,
			VER_1_0_573_1_NOSTEAM,

			VER_1_0_617_1_STEAM,
			VER_1_0_617_1_NOSTEAM,

			VER_SIZE,
			VER_UNK = -1
		};

		extern eGameVersion (WINAPI *getGameVersion)();
	} /* shv */
} /* nob */
