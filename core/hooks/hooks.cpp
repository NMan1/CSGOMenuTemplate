#include "../features/features.hpp"
#include "../../dependencies/utilities/settings.h"
#include <algorithm>
#include "../menu/menu.h"

hooks::present::fn			present_original		    = nullptr;
hooks::reset::fn			reset_original				= nullptr;
hooks::lock_cursor::fn		lock_cursor_original		= nullptr;

using fn_org = void(__fastcall*)(void*, void*);

uint8_t*					present_address				= nullptr;
uint8_t*					reset_address				= nullptr;

HWND						hooks::hCSGOWindow			= nullptr; 
WNDPROC						hooks::pOriginalWNDProc		= nullptr;
bool						hooks::initialized_drawManager = false;
color						watermark					= (255, 59, 59);

unsigned int get_virtual(void* class_, unsigned int index) { return (unsigned int)(*(int**)class_)[index]; }
extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

bool hooks::initialize() 
{
	// Get window handle
	while (!(hooks::hCSGOWindow = FindWindowA("Valve001", nullptr)))
	{
		using namespace std::literals::chrono_literals;
		std::this_thread::sleep_for(50ms);
	}

	if (hooks::hCSGOWindow)        // Hook WNDProc to capture mouse / keyboard input
		hooks::pOriginalWNDProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hooks::hCSGOWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(hooks::WndProc)));
	else
	{
		throw std::runtime_error("failed to hook wndproc.");
		return false;
	}
	
	auto lock_cursor_target = reinterpret_cast<void*>(get_virtual(interfaces::surface, 67));
	auto in_key_event_target = reinterpret_cast<void*>(get_virtual(interfaces::client, 21));
	auto present_address = utilities::pattern_scan(GetModuleHandleW(L"gameoverlayrenderer.dll"), "FF 15 ? ? ? ? 8B F8 85 DB") + 0x2;
	auto reset_address = utilities::pattern_scan(GetModuleHandleW(L"gameoverlayrenderer.dll"), "FF 15 ? ? ? ? 8B F8 85 FF 78 18") + 0x2;

	if (!present_address || !reset_address)
	{
		throw std::runtime_error("failed to aquire present address");
		return false;
	}

	if (MH_Initialize() != MH_OK) {
		throw std::runtime_error("failed to initialize MH_Initialize.");
		return false;
	}

	if (MH_CreateHook(**reinterpret_cast<void***>(present_address), &present::hook, reinterpret_cast<void**>(&present_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize present_address. (outdated index?)");
		return false;
	}		
	
	if (MH_CreateHook(**reinterpret_cast<void***>(reset_address), &reset::hook, reinterpret_cast<void**>(&reset_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize reset_address. (outdated index?)");
		return false;
	}	

	if (MH_CreateHook(lock_cursor_target, &lock_cursor::hook, reinterpret_cast<void**>(&lock_cursor_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize lock_cursor. (outdated index?)");
		return false;
	}			

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
		throw std::runtime_error("failed to enable hooks.");
		return false;
	}

	interfaces::engine->get_screen_size(menu.screen_x, menu.screen_y);

	console::log("[setup] hooks initialized!\n");
	return true;
}

void hooks::release() 
{
	menu.menu_opened = false;
	interfaces::input->m_fCameraInThirdPerson = false;
	Sleep(100);

	MH_Uninitialize();
	MH_DisableHook(MH_ALL_HOOKS);

	SetWindowLongPtr(hooks::hCSGOWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(hooks::pOriginalWNDProc));
}

long __stdcall hooks::present::hook(IDirect3DDevice9* device, RECT* source_rect, RECT* dest_rect, HWND dest_window_override, RGNDATA* dirty_region) 
{
	if (!hooks::initialized_drawManager) 
	{
		menu.apply_fonts();
		menu.setup_resent(device);
		hooks::initialized_drawManager = true;
	}

	if (hooks::initialized_drawManager)
	{
		menu.pre_render(device);
		menu.post_render();
		if (menu.config.spectator_list)
			menu.spectator_list();
		if (menu.menu_opened)
			menu.render();
		menu.end_present(device);
	}

	return present_original(device, source_rect, dest_rect, dest_window_override, dirty_region);
}

long __stdcall hooks::reset::hook(IDirect3DDevice9 * device, D3DPRESENT_PARAMETERS * present_parameters) 
{
	if (!hooks::initialized_drawManager)
		reset_original(device, present_parameters);

	menu.invalidate_objects();
	long hr = reset_original(device, present_parameters);
	menu.create_objects(device);

	return hr;
}

void __stdcall hooks::lock_cursor::hook()
{
	if (menu.menu_opened)
	{
		interfaces::surface->unlock_cursor();
		return;
	}
	return lock_cursor_original(interfaces::surface);
}      

LRESULT __stdcall hooks::WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	if (GetAsyncKeyState(menu.config.menu_key) & 1)
		menu.menu_opened = !menu.menu_opened;

	if (GetAsyncKeyState(menu.config.legit_pair.first))
		menu.config.legit_pair.second = true;
	else
		menu.config.legit_pair.second = false;

	if (GetAsyncKeyState(menu.config.trigger_bot_pair.first))
		menu.config.trigger_bot_pair.second = true;
	else
		menu.config.trigger_bot_pair.second = false;

	if (GetAsyncKeyState(menu.config.thirdperson_pair.first) & 1)
		menu.config.thirdperson_pair.second = !menu.config.thirdperson_pair.second;	

	if (GetAsyncKeyState(menu.config.movement_blocker.first) & 1)
		menu.config.movement_blocker.second = !menu.config.movement_blocker.second;	

	if (GetAsyncKeyState(menu.config.crouch_blocker.first) & 1)
		menu.config.crouch_blocker.second = !menu.config.crouch_blocker.second;

	if (GetAsyncKeyState(menu.config.fake_duck.first) & 1)
		menu.config.fake_duck.second = !menu.config.fake_duck.second;

	if (GetAsyncKeyState(menu.config.shoot_thrown_guns.first) & 1)
		menu.config.shoot_thrown_guns.second = !menu.config.shoot_thrown_guns.second;

	if (GetAsyncKeyState(menu.config.quick_peak_pair.first) & 1)
		menu.config.do_quick_peek = !menu.config.do_quick_peek;

	if (menu.menu_opened) 
		interfaces::inputsystem->enable_input(false);
	else if (!menu.menu_opened) 
		interfaces::inputsystem->enable_input(true);

	if (menu.menu_opened && ImGui_ImplDX9_WndProcHandler(hwnd, message, wparam, lparam))
		return true;

	return CallWindowProcA(hooks::pOriginalWNDProc, hwnd, message, wparam, lparam);
}
