#include "ImGuiUtility.h"

bool ImGuiUtility::SelectFolderPath(const char* Label, std::string& FolderPath)
{
	std::string label_ = std::format("{} : {}" , Label , FolderPath);

	if (ImGui::Button((label_.c_str())))
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

void ImGuiUtility::BitShiftSelector(const char* Label, uint32_t& Flag, const std::vector<CommonStruct::BitShiftList>& List)
{
	ImGui::PushID(&List);

	if (ImGui::BeginCombo(Label , Label))
	{
		for (const auto& item_ : List)
		{
			bool isSelected_ = (Flag & item_.type);

			if (ImGui::Checkbox(item_.label , &isSelected_))
			{
				if (isSelected_)
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

void ImGuiUtility::DrawSeparate()
{
	ImGui::Spacing  ();
	ImGui::Separator();
	ImGui::Spacing  ();
}