#include "Themes.hpp"
#include "core/commands/ColorCommand.hpp"
#include "game/frontend/submenus/Settings/GUISettings.hpp"

namespace YimMenu
{
	void DefaultStyle()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.20f, 0.00f, 0.95f);
		style.Colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.15f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.00f, 0.18f, 0.00f, 0.95f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.00f, 0.00f, 0.30f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.30f, 0.00f, 0.54f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.40f, 0.00f, 0.40f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 0.50f, 0.00f, 0.67f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.80f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 0.20f, 0.00f, 0.57f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.60f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.00f, 0.80f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.60f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.80f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.80f, 0.00f, 0.00f, 0.40f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.90f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 0.30f, 0.00f, 0.31f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.40f, 0.00f, 0.80f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 0.50f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_Separator] = ImVec4(0.80f, 0.00f, 0.00f, 0.50f);
		style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.90f, 0.00f, 0.00f, 0.78f);
		style.Colors[ImGuiCol_SeparatorActive] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.80f, 0.60f, 0.00f, 0.25f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.90f, 0.70f, 0.00f, 0.67f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 0.80f, 0.00f, 0.95f);
		style.Colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.20f, 0.00f, 0.86f);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(0.80f, 0.00f, 0.00f, 0.80f);
		style.Colors[ImGuiCol_TabActive] = ImVec4(0.80f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.15f, 0.00f, 0.97f);
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.00f, 0.30f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.80f, 0.00f, 0.00f, 0.35f);
		style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.80f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		style.GrabRounding = style.FrameRounding = style.ChildRounding = style.WindowRounding = 8.0f;
	}

	void christmas_theme()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImVec4* colors = style.Colors;

		style.WindowPadding = ImVec2(10.0f, 10.0f);
		style.FramePadding = ImVec2(8.0f, 5.0f);
		style.ItemSpacing = ImVec2(8.0f, 6.0f);
		style.ItemInnerSpacing = ImVec2(6.0f, 6.0f);
		style.ScrollbarSize = 10.0f;
		style.GrabMinSize = 10.0f;
		style.WindowRounding = 8.0f;
		style.ChildRounding = 6.0f;
		style.FrameRounding = 5.0f;
		style.PopupRounding = 6.0f;
		style.ScrollbarRounding = 8.0f;
		style.GrabRounding = 5.0f;
		style.TabRounding = 5.0f;
		style.WindowBorderSize = 1.0f;
		style.ChildBorderSize = 1.0f;
		style.PopupBorderSize = 1.0f;
		style.FrameBorderSize = 0.0f;

		colors[ImGuiCol_Text] = ImVec4(0.96f, 0.97f, 0.94f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.53f, 0.62f, 0.57f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.045f, 0.085f, 0.075f, 0.98f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.065f, 0.135f, 0.110f, 1.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.055f, 0.105f, 0.085f, 0.98f);
		colors[ImGuiCol_Border] = ImVec4(0.56f, 0.43f, 0.22f, 0.45f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.095f, 0.190f, 0.145f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.145f, 0.270f, 0.190f, 1.00f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.185f, 0.320f, 0.225f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.065f, 0.145f, 0.115f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.095f, 0.205f, 0.155f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.045f, 0.085f, 0.075f, 0.85f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.075f, 0.155f, 0.120f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.045f, 0.095f, 0.075f, 1.00f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.235f, 0.365f, 0.275f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.345f, 0.475f, 0.345f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.720f, 0.175f, 0.210f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.570f, 0.125f, 0.160f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.740f, 0.185f, 0.220f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.850f, 0.235f, 0.265f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.540f, 0.135f, 0.170f, 0.85f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.700f, 0.185f, 0.220f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.790f, 0.220f, 0.255f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.950f, 0.760f, 0.390f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.900f, 0.700f, 0.340f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(1.000f, 0.830f, 0.480f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.670f, 0.510f, 0.260f, 0.50f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.900f, 0.700f, 0.350f, 0.85f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(1.000f, 0.820f, 0.450f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.100f, 0.205f, 0.155f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.700f, 0.175f, 0.210f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(0.570f, 0.135f, 0.170f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.070f, 0.135f, 0.105f, 1.00f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.350f, 0.140f, 0.155f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.850f, 0.680f, 0.350f, 0.25f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.850f, 0.680f, 0.350f, 0.65f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.950f, 0.780f, 0.430f, 1.00f);
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.110f, 0.230f, 0.170f, 1.00f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.390f, 0.340f, 0.200f, 0.65f);
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.230f, 0.280f, 0.210f, 0.40f);
		colors[ImGuiCol_TableRowBg] = ImVec4(0.055f, 0.110f, 0.090f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.110f, 0.205f, 0.155f, 0.35f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.720f, 0.190f, 0.220f, 0.40f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(0.950f, 0.760f, 0.390f, 0.95f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.950f, 0.760f, 0.390f, 0.85f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.015f, 0.035f, 0.025f, 0.75f);
	}

	void SetupStyle()
	{
		// Apply default style first
		christmas_theme();

		// Initialize the color/rounding commands and load saved settings
		InitializeColorCommands(); // This will call LoadSettings internally

		// Apply loaded colors/rounding to ImGui
		ApplyThemeToImGui();
	}
}
