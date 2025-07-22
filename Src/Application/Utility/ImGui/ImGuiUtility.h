#pragma once
#include "../Common/CommonConstant.h"
#include "../Common/CommonStruct.h"
#include "../../main.h"

namespace ImGuiUtility
{
	bool SelectFolderPath(const char* Label , std::string& FolderPath);
	
	void BitShiftSelector(const char* Label , uint32_t& Flag, const std::vector<CommonStruct::BitShiftList>& List);

	void DrawSeparate();
}