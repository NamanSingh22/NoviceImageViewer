/*
 * Author:      namansingh22<singhnaman2209@gmail.com>
 * Created:     2026-05-26
 */

#include "app.hpp"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool App::initialize(std::string_view title, int init_w, int init_h)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "SDL3 initializtion failed: " << SDL_GetError() << "\n";
        return false;
    }

    if (!SDL_CreateWindowAndRenderer(title.data(), init_w, init_h, SDL_WINDOW_RESIZABLE, &m_window, &m_renderer))
    {
        std::cerr << "Window/Renderer creation failed: " << SDL_GetError() << "\n";
        return false;
    }

    m_is_running = true;
    return true;
}

bool App::load_img(std::string_view path)
{
    int w = 0;
    int h = 0;
    int channels = 0;

    unsigned char *cpu_pixels = stbi_load(path.data(), &w, &h, &channels, 4);

    if (!cpu_pixels)
    {
        std::cerr << "stbi_load failed for path: " << path << "; " << stbi_failure_reason() << "\n";
        return false;
    }

    m_img_w = static_cast<float>(w);
    m_img_h = static_cast<float>(h);

    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
    }

    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, w, h);

    if (!m_texture)
    {
        std::cerr << "Texture creation failed: " << SDL_GetError() << "\n";
        stbi_image_free(cpu_pixels);
        return false;
    }

    if (!SDL_UpdateTexture(m_texture, nullptr, cpu_pixels, w * 4))
    {
        std::cerr << "Failed to stream texture to VRAM: " << SDL_GetError() << "\n";
    }

    stbi_image_free(cpu_pixels);
    return true;
}

void App ::run()
{
    while (m_is_running)
    {
        handle_events();
        render();
    }
}

void App::handle_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            m_is_running = false;
        }
    }
}

void App::render()
{
    int win_w = 0;
    int win_h = 0;
    SDL_GetWindowSize(m_window, &win_w, &win_h);

    SDL_FRect dest_rect;
    m_view.calculate_dest_rect(m_img_w, m_img_h, static_cast<float>(win_w), static_cast<float>(win_h), dest_rect.x, dest_rect.y, dest_rect.w, dest_rect.h);

    SDL_SetRenderDrawColor(m_renderer, 25, 25, 25, 255);
    SDL_RenderClear(m_renderer);

    if (m_texture)
    {
        SDL_RenderTexture(m_renderer, m_texture, nullptr, &dest_rect);
    }

    SDL_RenderPresent(m_renderer);
}

void App::cleanup()
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }
    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    if (m_window)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    SDL_Quit();
}
