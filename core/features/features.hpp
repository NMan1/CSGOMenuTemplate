#pragma once
#include "../../dependencies/common_includes.hpp"

namespace features 
{
	namespace skins 
	{
		extern std::string file_skins;
		int find_paint_kit(int item_definition_index, bool is_knife);
		int find_knife_model(int item_definition_index);
		void replace_paint_model_kit(int item_definition_index, int paint_kit, int knife_index = -1);
		std::vector<std::pair<std::string, std::pair<int, int>>> get_weapon_skins(int item_index); // name, id, quality
		void run();
		void create();
		void save();
		void load();
	}
}