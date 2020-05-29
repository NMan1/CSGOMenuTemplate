#include "Menu.h"
#include "../../source-sdk/misc/color.hpp"
#include "imgui/imgui_internal.h"
#include "menu_helpers.h"

Menu menu;
IDirect3DStateBlock9* state_block;

void __stdcall Menu::setup_resent(IDirect3DDevice9* device)
{
	ImGui_ImplDX9_Init(hooks::hCSGOWindow, device);

	ImGuiStyle& style = ImGui::GetStyle();
	style.Alpha = 1.f;
	style.WindowPadding = ImVec2(0, 0); // 8 or 9 x
	style.WindowMinSize = ImVec2(32, 32);
	style.WindowRounding = 10.0f;
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.ChildWindowRounding = 0.0f;
	style.FramePadding = ImVec2(4, 3);
	style.FrameRounding = 0.0f;
	style.ItemSpacing = ImVec2(8, 8);
	style.ItemInnerSpacing = ImVec2(8, 8);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 0.0f;
	style.ScrollbarSize = 6.0f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 0.0f;
	style.ButtonTextAlign = ImVec2(0.0f, 0.5f);
	style.DisplayWindowPadding = ImVec2(22, 22);
	style.DisplaySafeAreaPadding = ImVec2(4, 4);
	style.AntiAliasedLines = true;
	style.AntiAliasedShapes = false;
	style.CurveTessellationTol = 1.f;

	ImVec4* colors = ImGui::GetStyle().Colors;
	//colors[ImGuiCol_Text] = ImVec4(0.929, 0.290, 0.290, 1.00f); red
	colors[ImGuiCol_Text] = ImVec4(.6f, .6f, .6f, 1.00f); // grey
	colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
	colors[ImGuiCol_WindowBg] = helpers::main_grey;
	//colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ChildWindowBg] = helpers::main_light_grey;
	colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
	colors[ImGuiCol_Border] = ImVec4(1, 1, 1, .8f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.f, 0, 0, .0f);
	colors[ImGuiCol_FrameBg] = helpers::main_light_grey;
	colors[ImGuiCol_FrameBgHovered] = ImVec4(.6f, .6f, .6f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.25f, 0.30f, 1.0f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.40f, 0.40f, 0.55f, 0.80f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);
	colors[ImGuiCol_ScrollbarGrab] = helpers::main_red;
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(helpers::main_red.x, helpers::main_red.y, helpers::main_red.z, .70f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(helpers::main_red.x, helpers::main_red.y, helpers::main_red.z, .70f);
	colors[ImGuiCol_ComboBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.99f);
	colors[ImGuiCol_Separator] = ImVec4(0.654, 0.094, 0.278, 1.f);
	colors[ImGuiCol_CheckMark] = helpers::main_red;
	colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	//colors[ImGuiCol_Header] = ImVec4(237 / 255.f, 74 / 255.f, 74 / 255.f, .5f); //multicombo, combo selected item color.
	//colors[ImGuiCol_HeaderHovered] = ImVec4(35 / 255.f, 35 / 255.f, 35 / 255.f, 1.0f);
	//colors[ImGuiCol_HeaderActive] = ImVec4(35 / 255.f, 35 / 255.f, 35 / 255.f, 1.0f);	
	colors[ImGuiCol_Header] = ImVec4(0.1f, 0.1f, 0.1f, 1.); //multicombo, combo selected item color.
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.26f, 0.26f, 1.f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
	colors[ImGuiCol_CloseButton] = ImVec4(0.10f, 0.10f, 0.10f, 0.50f);
	colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_CloseButtonActive] = ImVec4(0.70f, 0.20f, 0.00f, 0.83f);
	colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

	create_objects(device);
}

void update_colors()
{
}

void Menu::render()
{
	ImGui::SetNextWindowSize(ImVec2(menu.screen_x, menu.screen_y));
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::Begin("Background", &menu.menu_opened, ImVec2(menu.screen_x, menu.screen_y), .45, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMove);
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.568, 0.533, 0.533, .2f));
		ImGui::PopStyleColor();
	}
	ImGui::End();

	ImGui::SetNextWindowSize(ImVec2(menu_size.x, 40));
	ImGui::SetNextWindowPos(ImVec2((menu.screen_x - 515) * .5, (menu.screen_y - 587) * .5), ImGuiCond_Once);
	ImGui::Begin("Overflow Tabs", &menu.menu_opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders);
	{
		ImGui::SetScrollY(0);
		auto window = ImGui::GetCurrentWindow();
		helpers::tab_window_pos = window->Pos;

		static color clr = helpers::to_color(helpers::main_red); //rainbow(clr);
		helpers::push_text(Menu::font_title, "OVERFLOW", clr, ImVec2(12, 6));

		window->DrawList->AddRectFilled(ImVec2(helpers::tab_window_pos.x + 10 + ImGui::CalcTextSize("OVERFLOW").x + 26, helpers::tab_window_pos.y + 13), ImVec2(helpers::tab_window_pos.x + 10 + ImGui::CalcTextSize("OVERFLOW").x + 26 + 1, helpers::tab_window_pos.y + 2 + ImGui::CalcTextSize("OVERFLOW").y), ImGui::ColorConvertFloat4ToU32(helpers::main_red));
		auto start_pos = ImVec2(helpers::tab_window_pos.x + 10 + ImGui::CalcTextSize("OVERFLOW").x + 30, helpers::tab_window_pos.y + 6);

		for (int i = 0; i < IM_ARRAYSIZE(helpers::tab_names); i++)
		{
			auto start_pos = ImVec2(10 + ImGui::CalcTextSize("OVERFLOW").x + 26 + 21, 7);
			auto pos = ImVec2(start_pos.x + (((515 - start_pos.x) / IM_ARRAYSIZE(helpers::tab_names)) * i), start_pos.y+1);

			switch (i)
			{
			case 0:
				pos.x -= 3; break;				
			case 1:
				pos.x += 4; break;			
			case 2:
				pos.x += 10; break;
			case 3:
				pos.x -= 5; break;
			case 4:
				pos.x -= 14; break;
			}

			auto size = ImGui::CalcTextSize(helpers::tab_names[i]);
			helpers::push_button_tab(Menu::font_large_menu, helpers::tab_names[i], true, pos, ImVec2(size.x + 8, size.y), helpers::to_color(helpers::main_red), color(255, 255, 255), i);
		}
	}
	ImGui::End();	

	ImGui::SetNextWindowSize(menu_size);
	ImGui::SetNextWindowPos(ImVec2(helpers::tab_window_pos.x, helpers::tab_window_pos.y + 47));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));
	ImGui::Begin("Overflow Main", &menu.menu_opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders, ImGuiCorner_TopLeft | ImGuiCorner_TopRight);
	{
		ImGui::SetScrollY(0);
		auto window = ImGui::GetCurrentWindow();
		helpers::main_window_pos = window->Pos;

		ImGui::PushFont(font_menu);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
		switch (helpers::page_number)
		{
		case 0:
			legit_tab(); break;
		case 1:
			visuals_tab(); break;
		case 2:
			misc_tab(); break;
		case 3:
			skins_tab(); break;
		case 4:
			settings_tab(); break;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor();
	}
	ImGui::End();
	ImGui::PopStyleVar();

	ImGui::SetNextWindowSize(ImVec2(menu_size.x, 10));
	ImGui::SetNextWindowPos(ImVec2(helpers::main_window_pos.x, helpers::main_window_pos.y + 500 + 4));
	ImGui::Begin("Overflow Bottom", &menu.menu_opened, ImVec2(0.f, 0.f), .0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs, ImGuiCorner_BottomLeft | ImGuiCorner_BottomRight);
	{
		auto window = ImGui::GetCurrentWindow();
		auto bottom_window_pos = window->Pos;
		window->DrawList->AddRect(ImVec2(bottom_window_pos.x, bottom_window_pos.y), ImVec2(bottom_window_pos.x + window->Size.x, bottom_window_pos.y + 19.5), ImGui::ColorConvertFloat4ToU32(ImVec4(1, 1, 1, .8)), 8, ImGuiCorner_BottomLeft | ImGuiCorner_BottomRight);
		
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 12);
		helpers::push_text(Menu::font_bottom_info, helpers::version, color(255, 255, 255));

		auto get_fps = []() -> int
		{
			static float frame_rate = 0;
			static auto old_fps = 0;
			auto fps = 0;
			frame_rate = 0.9 * frame_rate + (1.0 - 0.9) * interfaces::globals->absolute_frametime;
			fps = int(1.f / frame_rate);
			old_fps == 0 ? old_fps = fps : true;

			// if change is greater than 4 update
			if (abs(fps - old_fps) >= 4)
			{
				old_fps = fps = int(1.f / frame_rate);
				return fps;
			}
			else
				return old_fps;
		};

		helpers::push_text(Menu::font_bottom_info, std::string("Fps: " + std::to_string(get_fps())), color(255, 255, 255), ImVec2(window->Size.x - ImGui::CalcTextSize(std::string("Fps: " + std::to_string(get_fps())).c_str()).x + 19, ImGui::GetCursorPosY() - 22.9));
		//auto ping = "Ping: " + (interfaces::engine->is_connected() && interfaces::engine->is_in_game()) ? std::to_string(reinterpret_cast<i_net_channel_info*>(interfaces::engine->get_net_channel_info())->get_average_latency(1) * 1000) + "ms" : "0ms";
		std::string ping = "Ping: 0ms";
		helpers::push_text(Menu::font_bottom_info, ping, color(255, 255, 255), ImVec2(window->Size.x - (ImGui::CalcTextSize(ping.c_str()).x + ImGui::CalcTextSize(std::string("Fps: " + std::to_string(get_fps())).c_str()).x) + 45, ImGui::GetCursorPosY() - 22.9));
	}
	ImGui::End();
}

void Menu::change_log()
{

}

void Menu::spectator_list()
{
	if (menu.spectators.size() > 0)
		menu.spec_height = 41 + ((ImGui::CalcTextSize(menu.spectators[0].c_str()).y + 5) * menu.spectators.size());
	else
		menu.spec_height = 30;

	ImGui::SetNextWindowSize(ImVec2(175, menu.spec_height));
	ImGui::SetNextWindowPos(ImVec2(1700, 260), ImGuiCond_Once);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);

	ImGui::Begin("Spectators", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);
	{
		ImGui::SetCursorPosX((175 - ImGui::CalcTextSize("Spectators").x)*.5);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.5);
		ImGui::Text("Spectators");
		ImGui::Separator();
		if (!menu.spectators.empty())
		{
			ImGui::PushFont(menu.font_spectators);
			for (int i = 0; i < menu.spectators.size(); i++)
			{
				ImGui::SetCursorPosX((175 - ImGui::CalcTextSize(menu.spectators[i].c_str()).x) * .5);
				ImGui::Text(menu.spectators[i].c_str());
			}
			ImGui::PopFont();
		}
	}
	ImGui::End();
	ImGui::PopStyleVar();
}