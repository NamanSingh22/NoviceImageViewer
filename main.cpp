/*
 * Author:      namansingh22<singhnaman2209@gmail.com>
 * Created:     2026-05-26
 */

#include <windows.h>
#include "app.hpp"

int main(int argc, char *argv[])
{
    SetDllDirectory("./bin");
    const int window_w = 1280;
    const int window_h = 720;
    App app;
    if (!app.initialize("NoviceImageViewer", window_w, window_h))
    {
        return 1;
    }

    app.load_img("image.jpg");

    app.run();
    return 0;
}