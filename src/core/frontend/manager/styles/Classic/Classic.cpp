
#include "game/pointers/Pointers.hpp"
#include "game/frontend/Menu.hpp"
#include "core/frontend/manager/UIManager.hpp"
#include "core/commands/BoolCommand.hpp"
#include "game/frontend/submenus/ExtraSubmenus.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

namespace YimMenu
{
    static BoolCommand menuChristmas{"menubgchristmas", "Christmas Background", "Toggle the animated Christmas background"};

    struct SnowParticle
    {
        ImVec2 pos;
        float speed;
        float size;
        float drift;
        float phase;
    };

    static std::vector<SnowParticle> g_Snow{};
    static bool g_SnowInit = false;
    static float g_MenuAlpha = 0.0f;
    static float g_MenuSlide = 30.0f;
    static float g_ContentSlide = 0.0f;
    static decltype(UIManager::GetActiveSubmenu()) g_LastSubmenu{};

    static float RandomFloat(float min, float max)
    {
        return min + (max - min) * (static_cast<float>(rand()) / RAND_MAX);
    }

    static float LerpFloat(float a, float b, float t)
    {
        return a + (b - a) * std::clamp(t, 0.0f, 1.0f);
    }

    static void InitSnow(int count, ImVec2 winSize)
    {
        static bool seeded = false;

        if (!seeded)
        {
            srand(static_cast<unsigned int>(time(nullptr)));
            seeded = true;
        }

        g_Snow.clear();
        g_Snow.reserve(count);

        for (int i = 0; i < count; ++i)
        {
            g_Snow.push_back({
                ImVec2(RandomFloat(0.0f, winSize.x), RandomFloat(0.0f, winSize.y)),
                RandomFloat(18.0f, 65.0f),
                RandomFloat(0.8f, 2.8f),
                RandomFloat(4.0f, 14.0f),
                RandomFloat(0.0f, 6.28318f)
            });
        }

        g_SnowInit = true;
    }

    static void DrawStar(ImDrawList* draw, ImVec2 pos, float size, ImU32 color)
    {
        draw->AddLine(ImVec2(pos.x - size, pos.y), ImVec2(pos.x + size, pos.y), color, 1.2f);
        draw->AddLine(ImVec2(pos.x, pos.y - size), ImVec2(pos.x, pos.y + size), color, 1.2f);
        draw->AddCircleFilled(pos, size * 0.28f, color, 8);
    }

    static void DrawChristmasTree(ImDrawList* draw, ImVec2 pos, float scale, float time)
    {
        const float w = 58.0f * scale;
        const float h = 110.0f * scale;

        ImU32 darkGreen = IM_COL32(14, 65, 43, 255);
        ImU32 green = IM_COL32(22, 105, 65, 255);
        ImU32 lightGreen = IM_COL32(31, 135, 79, 255);
        ImU32 snow = IM_COL32(235, 245, 250, 230);

        draw->AddRectFilled(ImVec2(pos.x - 7.0f * scale, pos.y - 18.0f * scale), ImVec2(pos.x + 7.0f * scale, pos.y + 12.0f * scale), IM_COL32(91, 55, 34, 255), 2.0f);

        draw->AddTriangleFilled(ImVec2(pos.x, pos.y - h), ImVec2(pos.x - w * 0.65f, pos.y - h * 0.35f), ImVec2(pos.x + w * 0.65f, pos.y - h * 0.35f), lightGreen);
        draw->AddTriangleFilled(ImVec2(pos.x, pos.y - h * 0.78f), ImVec2(pos.x - w * 0.85f, pos.y - h * 0.12f), ImVec2(pos.x + w * 0.85f, pos.y - h * 0.12f), green);
        draw->AddTriangleFilled(ImVec2(pos.x, pos.y - h * 0.55f), ImVec2(pos.x - w, pos.y), ImVec2(pos.x + w, pos.y), darkGreen);

        draw->AddLine(ImVec2(pos.x - w * 0.22f, pos.y - h * 0.77f), ImVec2(pos.x + w * 0.22f, pos.y - h * 0.77f), snow, 2.0f * scale);
        draw->AddLine(ImVec2(pos.x - w * 0.40f, pos.y - h * 0.52f), ImVec2(pos.x + w * 0.40f, pos.y - h * 0.52f), snow, 2.0f * scale);
        draw->AddLine(ImVec2(pos.x - w * 0.60f, pos.y - h * 0.27f), ImVec2(pos.x + w * 0.60f, pos.y - h * 0.27f), snow, 2.0f * scale);

        for (int i = 0; i < 9; ++i)
        {
            float y = pos.y - h * (0.18f + (i / 3) * 0.20f);
            float x = pos.x + ((i % 3) - 1) * w * 0.35f;
            float glow = 0.5f + 0.5f * std::sin(time * 2.5f + i * 1.7f);
            ImU32 color = i % 3 == 0 ? IM_COL32(255, 70, 75, 255) : (i % 3 == 1 ? IM_COL32(255, 210, 85, 255) : IM_COL32(110, 200, 255, 255));

            draw->AddCircleFilled(ImVec2(x, y), (5.0f + glow * 2.0f) * scale, IM_COL32(255, 220, 130, 25), 12);
            draw->AddCircleFilled(ImVec2(x, y), 2.7f * scale, color, 12);
        }

        DrawStar(draw, ImVec2(pos.x, pos.y - h - 5.0f * scale), 7.0f * scale, IM_COL32(255, 215, 100, 255));
    }

    static void DrawSnowman(ImDrawList* draw, ImVec2 pos, float scale)
    {
        ImU32 white = IM_COL32(242, 248, 255, 245);
        ImU32 black = IM_COL32(28, 38, 45, 255);

        draw->AddCircleFilled(ImVec2(pos.x, pos.y - 16.0f * scale), 19.0f * scale, white, 24);
        draw->AddCircleFilled(ImVec2(pos.x, pos.y - 45.0f * scale), 14.0f * scale, white, 24);

        draw->AddCircleFilled(ImVec2(pos.x - 5.0f * scale, pos.y - 48.0f * scale), 1.8f * scale, black);
        draw->AddCircleFilled(ImVec2(pos.x + 5.0f * scale, pos.y - 48.0f * scale), 1.8f * scale, black);

        draw->AddTriangleFilled(ImVec2(pos.x, pos.y - 43.0f * scale), ImVec2(pos.x + 13.0f * scale, pos.y - 40.0f * scale), ImVec2(pos.x, pos.y - 39.0f * scale), IM_COL32(255, 135, 35, 255));

        draw->AddCircleFilled(ImVec2(pos.x, pos.y - 22.0f * scale), 2.0f * scale, black);
        draw->AddCircleFilled(ImVec2(pos.x, pos.y - 12.0f * scale), 2.0f * scale, black);

        draw->AddRectFilled(ImVec2(pos.x - 15.0f * scale, pos.y - 61.0f * scale), ImVec2(pos.x + 15.0f * scale, pos.y - 57.0f * scale), black, 2.0f);
        draw->AddRectFilled(ImVec2(pos.x - 10.0f * scale, pos.y - 76.0f * scale), ImVec2(pos.x + 10.0f * scale, pos.y - 59.0f * scale), black, 2.0f);

        draw->AddLine(ImVec2(pos.x - 15.0f * scale, pos.y - 25.0f * scale), ImVec2(pos.x - 30.0f * scale, pos.y - 38.0f * scale), IM_COL32(110, 72, 45, 255), 2.0f);
        draw->AddLine(ImVec2(pos.x + 15.0f * scale, pos.y - 25.0f * scale), ImVec2(pos.x + 30.0f * scale, pos.y - 38.0f * scale), IM_COL32(110, 72, 45, 255), 2.0f);
    }

    static void DrawPresent(ImDrawList* draw, ImVec2 pos, ImVec2 size, ImU32 color)
    {
        draw->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), color, 3.0f);
        draw->AddRectFilled(ImVec2(pos.x + size.x * 0.43f, pos.y), ImVec2(pos.x + size.x * 0.57f, pos.y + size.y), IM_COL32(245, 205, 105, 255));
        draw->AddRectFilled(ImVec2(pos.x, pos.y + size.y * 0.40f), ImVec2(pos.x + size.x, pos.y + size.y * 0.58f), IM_COL32(245, 205, 105, 255));
        draw->AddRect(pos, ImVec2(pos.x + size.x, pos.y + size.y), IM_COL32(255, 255, 255, 75), 3.0f);
    }

    static void DrawChristmasLights(ImDrawList* draw, ImVec2 pos, ImVec2 size, float time)
    {
        const int count = std::max(2, static_cast<int>(size.x / 34.0f));

        for (int i = 0; i < count; ++i)
        {
            float x = pos.x + (size.x * i / static_cast<float>(count - 1));
            float y = pos.y + 10.0f + std::sin(i * 0.35f) * 7.0f;

            if (i > 0)
            {
                float px = pos.x + size.x * (i - 1) / static_cast<float>(count - 1);
                float py = pos.y + 10.0f + std::sin((i - 1) * 0.35f) * 7.0f;
                draw->AddLine(ImVec2(px, py), ImVec2(x, y), IM_COL32(50, 90, 65, 230), 1.5f);
            }

            float glow = 0.5f + 0.5f * std::sin(time * 2.0f + i * 0.8f);
            ImU32 color = i % 3 == 0 ? IM_COL32(255, 70, 80, 255) : (i % 3 == 1 ? IM_COL32(255, 215, 95, 255) : IM_COL32(95, 220, 135, 255));

            draw->AddCircleFilled(ImVec2(x, y + 5.0f), 7.0f + glow * 2.0f, IM_COL32(255, 210, 125, 18), 12);
            draw->AddCircleFilled(ImVec2(x, y + 5.0f), 3.5f, color, 12);
        }
    }

    static void RenderChristmasBackground(ImVec2 winPos, ImVec2 winSize)
    {
        if (!menuChristmas.GetState() || !UIManager::ShowingContentWindow())
        {
            g_Snow.clear();
            g_SnowInit = false;
            return;
        }

        if (winSize.x <= 1.0f || winSize.y <= 1.0f)
            return;

        ImGuiIO& io = ImGui::GetIO();
        ImDrawList* draw = ImGui::GetWindowDrawList();

        float time = static_cast<float>(ImGui::GetTime());
        float dt = std::clamp(io.DeltaTime, 0.0f, 0.05f);

        ImVec2 end(winPos.x + winSize.x, winPos.y + winSize.y);
        draw->PushClipRect(winPos, end, true);

        // Winter night sky
        draw->AddRectFilledMultiColor(winPos, end, IM_COL32(9, 24, 35, 255), IM_COL32(9, 24, 35, 255), IM_COL32(21, 55, 64, 255), IM_COL32(21, 55, 64, 255));

        // Moon
        ImVec2 moon(winPos.x + winSize.x * 0.78f, winPos.y + winSize.y * 0.19f);
        draw->AddCircleFilled(moon, 39.0f, IM_COL32(220, 235, 255, 12), 48);
        draw->AddCircleFilled(moon, 29.0f, IM_COL32(220, 235, 255, 22), 48);
        draw->AddCircleFilled(moon, 19.0f, IM_COL32(245, 247, 220, 220), 48);

        // Night stars
        for (int i = 0; i < 32; ++i)
        {
            float x = winPos.x + winSize.x * (0.04f + std::fmod(i * 0.173f, 0.92f));
            float y = winPos.y + winSize.y * (0.06f + std::fmod(i * 0.117f, 0.57f));
            float twinkle = 0.55f + 0.45f * std::sin(time * 1.5f + i * 2.3f);

            draw->AddCircleFilled(ImVec2(x, y), 0.8f + twinkle, IM_COL32(255, 255, 230, 135), 8);
        }

        // Distant snow hills
        draw->AddEllipseFilled(ImVec2(winPos.x + winSize.x * 0.20f, end.y + 52.0f), ImVec2(winSize.x * 0.58f, 125.0f), IM_COL32(180, 211, 220, 155));
        draw->AddEllipseFilled(ImVec2(winPos.x + winSize.x * 0.85f, end.y + 45.0f), ImVec2(winSize.x * 0.60f, 110.0f), IM_COL32(218, 234, 240, 185));

        // Christmas scenery
        float ground = end.y - 13.0f;

        DrawChristmasTree(draw, ImVec2(winPos.x + winSize.x * 0.12f, ground), 0.85f, time);
        DrawChristmasTree(draw, ImVec2(winPos.x + winSize.x * 0.88f, ground), 1.05f, time);
        DrawSnowman(draw, ImVec2(winPos.x + winSize.x * 0.68f, ground), 0.85f);

        // Presents
        DrawPresent(draw, ImVec2(winPos.x + winSize.x * 0.19f, ground - 23.0f), ImVec2(24.0f, 23.0f), IM_COL32(195, 45, 55, 255));
        DrawPresent(draw, ImVec2(winPos.x + winSize.x * 0.24f, ground - 18.0f), ImVec2(20.0f, 18.0f), IM_COL32(35, 125, 80, 255));
        DrawPresent(draw, ImVec2(winPos.x + winSize.x * 0.80f, ground - 26.0f), ImVec2(25.0f, 26.0f), IM_COL32(190, 45, 65, 255));

        // Animated lights
        DrawChristmasLights(draw, winPos, winSize, time);

        // Snowfall
        if (!g_SnowInit)
            InitSnow(120, winSize);

        for (auto& p : g_Snow)
        {
            p.pos.y += p.speed * dt;
            p.pos.x += std::sin(time * 1.3f + p.phase) * p.drift * dt;

            if (p.pos.y > winSize.y + 5.0f)
            {
                p.pos.y = -5.0f;
                p.pos.x = RandomFloat(0.0f, winSize.x);
            }

            if (p.pos.x < 0.0f)
                p.pos.x = winSize.x;

            if (p.pos.x > winSize.x)
                p.pos.x = 0.0f;

            ImVec2 snowPos(winPos.x + p.pos.x, winPos.y + p.pos.y);

            draw->AddCircleFilled(snowPos, p.size + 2.0f, IM_COL32(220, 240, 255, 22), 12);
            draw->AddCircleFilled(snowPos, p.size, IM_COL32(255, 255, 255, 175), 12);
        }

        // Gold border
        draw->AddRect(ImVec2(winPos.x + 1.0f, winPos.y + 1.0f), ImVec2(end.x - 1.0f, end.y - 1.0f), IM_COL32(225, 185, 100, 210), 8.0f, 0, 1.5f);

        draw->PopClipRect();
    }

    void RenderClassicTheme()
    {
        ImGuiIO& io = ImGui::GetIO();

        float screenX = Pointers.ScreenResX ? static_cast<float>(*Pointers.ScreenResX) : io.DisplaySize.x;
        float screenY = Pointers.ScreenResY ? static_cast<float>(*Pointers.ScreenResY) : io.DisplaySize.y;

        float windowWidth = screenX / 2.5f;
        float centerX = (screenX - windowWidth) * 0.5f;
        float centerY = screenY / 5.0f;

        ImVec2 windowSize(windowWidth, screenY / 2.5f);

        float t = std::clamp(io.DeltaTime * 10.0f, 0.0f, 1.0f);

        g_MenuAlpha = LerpFloat(g_MenuAlpha, 1.0f, t);
        g_MenuSlide = LerpFloat(g_MenuSlide, 0.0f, t);

        bool christmas = menuChristmas.GetState();

        if (christmas)
        {
            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.035f, 0.09f, 0.11f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.045f, 0.12f, 0.12f, 0.90f));
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.86f, 0.68f, 0.35f, 0.75f));
            ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.55f, 0.12f, 0.16f, 0.95f));
            ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.72f, 0.18f, 0.22f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.80f, 0.22f, 0.26f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.55f, 0.12f, 0.16f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.72f, 0.18f, 0.22f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.80f, 0.22f, 0.26f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(0.95f, 0.77f, 0.40f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.95f, 0.77f, 0.40f, 1.0f));
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 6.0f);
        }

        ImGui::SetNextWindowBgAlpha(g_MenuAlpha);
        ImGui::SetNextWindowSize(windowSize, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(centerX, centerY + g_MenuSlide), ImGuiCond_FirstUseEver);

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;

        if (!ImGui::Begin("##ClassicInputWindow", nullptr, flags))
        {
            ImGui::End();

            if (christmas)
            {
                ImGui::PopStyleColor(11);
                ImGui::PopStyleVar();
            }

            return;
        }

        ImVec2 winPos = ImGui::GetWindowPos();
        ImVec2 winSize = ImGui::GetWindowSize();

        RenderChristmasBackground(winPos, winSize);

        if (ImGui::BeginChild("##submenus", ImVec2(120, ImGui::GetContentRegionAvail().y), true))
        {
            const auto& submenus = UIManager::GetSubmenus();
            auto activeSubmenu = UIManager::GetActiveSubmenu();

           for (auto& submenu : submenus)
			{
				if (submenu->m_Name == "TinkerScripts" && !g_ShowExtraSubmenus)
					continue;

				if (ImGui::Selectable(submenu->m_Name.data(), submenu == activeSubmenu))
				{
					UIManager::SetActiveSubmenu(submenu);
					UIManager::SetShowContentWindow(true);
				}
			}
        }
        ImGui::EndChild();

        ImGui::SameLine();
        ImGui::BeginGroup();

        if (christmas)
            ImGui::TextColored(ImVec4(0.95f, 0.77f, 0.40f, 1.0f), "YimMenuV2 | Merry Christmas!");
        else
            ImGui::TextUnformatted("YimMenuV2");

        if (ImGui::BeginChild("##minisubmenus", ImVec2(0, 50), true))
        {
            auto activeSubmenu = UIManager::GetActiveSubmenu();

            if (activeSubmenu)
                activeSubmenu->DrawCategorySelectors();
        }
        ImGui::EndChild();

        auto activeSubmenu = UIManager::GetActiveSubmenu();

        if (activeSubmenu != g_LastSubmenu)
        {
            g_ContentSlide = 20.0f;
            g_LastSubmenu = activeSubmenu;
        }

        g_ContentSlide = LerpFloat(g_ContentSlide, 0.0f, t);

        ImGui::Dummy(ImVec2(g_ContentSlide, 0.0f));
        ImGui::SameLine(0.0f, 0.0f);

        if (ImGui::BeginChild("##options", ImVec2(0, 0), true))
        {
            bool pushedFont = false;

            if (ImFont* optionsFont = UIManager::GetOptionsFont())
            {
                ImGui::PushFont(optionsFont);
                pushedFont = true;
            }

            if (activeSubmenu)
                activeSubmenu->Draw();

            if (pushedFont)
                ImGui::PopFont();
        }
        ImGui::EndChild();

        ImGui::EndGroup();
        ImGui::End();

        if (christmas)
        {
            ImGui::PopStyleColor(11);
            ImGui::PopStyleVar();
        }
    }
}
