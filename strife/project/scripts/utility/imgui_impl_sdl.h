#ifndef IMGUI_IMPL_SDL_H
#define IMGUI_IMPL_SDL_H

// dear imgui: Platform Binding for SDL2
// This needs to be used along with a Renderer (e.g. DirectX11, OpenGL3, Vulkan..)
// (Info: SDL2 is a cross-platform general purpose library for handling windows, inputs, graphics context creation, etc.)

// Implemented features:
//  [X] Platform: Mouse cursor shape and visibility. Disable with 'io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange'.
//  [X] Platform: Clipboard support.
//  [X] Platform: Keyboard arrays indexed using SDL_SCANCODE_* codes, e.g. ImGui::IsKeyPressed(SDL_SCANCODE_SPACE).
// Missing features:
//  [ ] Platform: SDL2 handling of IME under Windows appears to be broken and it explicitly disable the regular Windows IME. You can restore Windows IME by compiling SDL with SDL_DISABLE_WINDOWS_IME.
//  [ ] Platform: Gamepad support (need to use SDL_GameController API to fill the io.NavInputs[] value when ImGuiConfigFlags_NavEnableGamepad is set).

// You can copy and use unmodified imgui_impl_* files in your project. See main.cpp for an example of using this.
// If you are new to dear imgui, read examples/README.txt and read the documentation at the top of imgui.cpp.
// https://github.com/ocornut/imgui

struct SDL_Window;
typedef union SDL_Event SDL_Event;

bool ImGui_ImplSDL2_InitForOpenGL(SDL_Window* window);
bool ImGui_ImplSDL2_InitForVulkan(SDL_Window* window);
void ImGui_ImplSDL2_Shutdown();
void ImGui_ImplSDL2_NewFrame(SDL_Window* window);
bool ImGui_ImplSDL2_ProcessEvent(SDL_Event* event);
void ImGui_ImplSDL2_UpdateMouse();

#endif  // IMGUI_IMPL_SDL_H
