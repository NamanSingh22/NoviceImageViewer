/*
 * Author:      namansingh22<singhnaman2209@gmail.com>
 * Created:     2026-05-26
 */

#include <windows.h>
#include "app.hpp"

int main(int argc, char *argv[])
{
    SetDllDirectory("./bin");

    App app;
    if (!app.initialize("NoviceImageViewer", 1280, 720))
    {
        return 1;
    }

    if (!app.load_img("image.jpg"))
    {
        return 1;
    }

    app.run();
    return 0;
}