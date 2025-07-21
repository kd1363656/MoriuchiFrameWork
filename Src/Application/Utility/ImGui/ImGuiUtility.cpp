#include "ImGuiUtility.h"

void ImGuiUtility::ImGuiBitShiftSelector(const char* Label, uint32_t& Flag, const std::vector<CommonStruct::BitShiftList>& List)
{
	ImGui::PushID(Label);

	if (ImGui::BeginCombo(Label , Label))
	{
		for (const auto& item_ : List)
		{
			bool isSelected_ = (Flag & item_.type);

			if (ImGui::Checkbox(item_.label , &isSelected_))
			{
				if(isSelected_)
				{
					Flag |= item_.type;
				}
				else
				{
					Flag &= ~item_.type;
				}
			}
		}
		ImGui::EndCombo();
	}

	ImGui::PopID();
}

bool ImGuiUtility::ImGuiSelectFolderPath(std::string& FolderPath)
{
	if (ImGui::Button(("FilePath : %s", FolderPath.c_str())))
	{
		std::string defPath_ = CommonConstant::ASSET_FOLDER_PATH;

		if (Application::Instance().GetWindow().OpenFileDialog(defPath_))
		{
			// 変更したファイルパスを取得して変数に代入
			FolderPath = defPath_;
			return true;
		}
	}

	return false;
}
