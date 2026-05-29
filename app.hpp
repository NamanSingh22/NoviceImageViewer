/*
 * Author:      namansingh22<singhnaman2209@gmail.com>
 * Created:     2026-05-26
 */

#pragma once
#include <string_view>
#include <SDL3/SDL.h>
#include "viewport.hpp"
#include <string>

class App
{
public:
    App() = default;
    ~App() { cleanup(); }

    bool initialize(std::string_view title, int init_w, int init_h);
    bool load_img(std::string_view path);
    void run();

private:
    void handle_events();
    void render();
    void cleanup();
    void render_default_splash_screen(float win_w, float win_h);

    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;
    SDL_Texture *m_texture = nullptr;

    bool m_is_running = false;

    float m_img_w = 0.0f;
    float m_img_h = 0.0f;

    Viewport m_view;
};