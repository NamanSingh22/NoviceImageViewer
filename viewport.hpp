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
};
