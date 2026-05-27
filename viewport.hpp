/*
 * Author:      namansingh22<singhnaman2209@gmail.com>
 * Created:     2026-05-26
 */

#pragma once

struct Viewport
{
    float pan_x = 0.0f;
    float pan_y = 0.0f;
    float zoom = 1.0f;

    void calculate_dest_rect(float img_w, float img_h, float win_w, float win_h,
                             float &out_x, float &out_y, float &out_w, float &out_h)
    {
        float scale = 1.0f;
        if ((win_w / win_h) > (img_w / img_h))
        {
            scale = win_h / img_h;
        }
        else
        {
            scale = win_w / img_w;
        }

        scale *= zoom;

        out_w = img_w * scale;
        out_h = img_h * scale;

        out_x = ((win_w - out_w) / 2.0f) + pan_x;
        out_y = ((win_h - out_h) / 2.0f) + pan_y;
    }

    void adjust_zoom(float mouse_x, float mouse_y, float zoom_delta, float win_w, float win_h, float img_w, float img_h)
    {
        float old_zoom = zoom;

        zoom += zoom_delta * 0.1f * zoom;
        if (zoom < 0.1f)
            zoom = 0.1f;
        if (zoom > 20.0f)
            zoom = 20.0f;

        float rel_x = mouse_x - (win_w / 2.0f);
        float rel_y = mouse_y - (win_h / 2.0f);

        float zoom_ratio = zoom / old_zoom;

        pan_x = rel_x - (rel_x - pan_x) * zoom_ratio;
        pan_y = rel_y - (rel_y - pan_y) * zoom_ratio;
    }
};
