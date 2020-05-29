#include "../menu.h"
#include "../menu_helpers.h"

const char* chams_type[] =
{
	"Textured",
	"Metallic",
	"Flat",
	"Dark Chrome",
	"Glow",
	"Crystal"
	"Wildfire"
};

std::vector<std::pair<const char*, bool&>> flags = { std::pair<const char*, bool&>{ "flashed", menu.config.flashed}, std::pair<const char*, bool&>{"money", menu.config.money}, 
													 std::pair<const char*, bool&>{"armor", menu.config.armor}, std::pair<const char*, bool&>{"bomb", menu.config.bomb}, 
													 std::pair<const char*, bool&>{"scoped", menu.config.scoped}, std::pair<const char*, bool&>{"defuse kit", menu.config.defuse_kit},
													 std::pair<const char*, bool&>{"defusing", menu.config.defusing} };

void main_child();
void weapon_child();
void chams_child();
void misc_child();
void world_child();

ImVec2 padding{ 5, 10 }; //  y = 17 with child title text
ImVec2 real_padding{ 12, 17 }; // the real padding applied

void Menu::visuals_tab()
{
	// no need for sepreate functions
	// but imo its just more ogranized
	main_child();
	weapon_child();
	helpers::change_pos(ImVec2((menu.menu_size.x - real_padding.x * 3) * .5 + (real_padding.x * 2) - 4, padding.y - 2));
	chams_child();
	helpers::change_pos(ImVec2((menu.menu_size.x - real_padding.x * 3) * .5 + (real_padding.x * 2) - 4, (padding.y * 2) + ((menu.menu_size.y - real_padding.y * 3) * .4)));
	misc_child();
	helpers::change_pos(ImVec2((menu.menu_size.x - real_padding.x * 3) * .5 + (real_padding.x * 2) - 4, (padding.y * 3) + ((menu.menu_size.y - real_padding.y * 3) * .7 + 1)));
	world_child();
}

void main_child()
{
	helpers::apply_padding(padding);
	ImGui::BeginChild("ESP Main", ImVec2((menu.menu_size.x - real_padding.x * 3) * .5, (menu.menu_size.y - real_padding.y * 3) * .65), true, ImGuiCorner_TopLeft, 10, ImGuiWindowFlags_AlwaysUseWindowPadding);
	{
		auto window = ImGui::GetCurrentWindow();
		helpers::toggle("Toggle ESP", &menu.config.visuals, helpers::to_color(helpers::main_red));
		helpers::color_picker(&menu.config.box_clr);
		helpers::slider<float>("Size", &menu.config.clan_tag_delay, 0, 100);
		helpers::slider<int>("Distance", &menu.config.third_person_distance, 0, 100);
		helpers::combo_selectable("flags", flags);
		helpers::combo("Selection Type", &menu.config.legit_selection, chams_type, IM_ARRAYSIZE(chams_type));
	}
	ImGui::EndChild(true, menu.font_child_title);
}

void weapon_child()
{
	helpers::apply_padding(padding);
	helpers::change_pos(ImVec2(ImGui::GetCursorPosX() , ImGui::GetCursorPosY() - 6));
	ImGui::BeginChild("Weapons", ImVec2((menu.menu_size.x - real_padding.x * 3) * .5, (menu.menu_size.y - real_padding.y * 3) * .35 + 9), true, 0, -1, ImGuiWindowFlags_AlwaysUseWindowPadding);
	{
		auto window = ImGui::GetCurrentWindow();
	}
	ImGui::EndChild(true, menu.font_child_title);
}

void chams_child()
{
	helpers::apply_padding(padding);
	ImGui::BeginChild("Chams", ImVec2((menu.menu_size.x - real_padding.x * 3) * .5, (menu.menu_size.y - real_padding.y * 3) * .4), true, ImGuiCorner_TopRight, 10, ImGuiWindowFlags_AlwaysUseWindowPadding);
	{
		auto window = ImGui::GetCurrentWindow();
	}
	ImGui::EndChild(true, menu.font_child_title);
}

void misc_child()
{
	helpers::apply_padding(padding);
	ImGui::BeginChild("Misc", ImVec2((menu.menu_size.x - real_padding.x * 3) * .5, (menu.menu_size.y - real_padding.y * 3) * .3), true, 0, -1, ImGuiWindowFlags_AlwaysUseWindowPadding);
	{
		auto window = ImGui::GetCurrentWindow();
	}
	ImGui::EndChild(true, menu.font_child_title);
}

void world_child()
{
	helpers::apply_padding(padding);
	ImGui::BeginChild("World", ImVec2((menu.menu_size.x - real_padding.x * 3) * .5, (menu.menu_size.y - real_padding.y * 3) * .3 - 2), true, 0, -1, ImGuiWindowFlags_AlwaysUseWindowPadding);
	{
		auto window = ImGui::GetCurrentWindow();
	}
	ImGui::EndChild(true, menu.font_child_title);
}
