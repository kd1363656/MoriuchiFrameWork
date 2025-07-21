#pragma once
#include "../Common/CommonConstant.h"
#include "../Common/CommonStruct.h"
#include "../../main.h"

namespace ImGuiUtility
{
	void ImGuiBitShiftSelector(const char* Label , uint32_t& Flag, const std::vector<CommonStruct::BitShiftList>& List);
	
	bool ImGuiSelectFolderPath(std::string& FolderPath);
}