/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2023  Sergei Baigerov

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Contact Sergei Baigerov -- @dogotrigger in Discord
*/

#include <nt5emul/renderer.h>

#if RENDERER_ENABLE_X11_CAPTURE == 1

void _ntUpdateXWindowStream(renderer_x11_window_stream_t stream) {
    if (stream.texture.width == 0 || stream.texture.height == 0 || stream.window_framebuffer == NULL) return;
   
    int w = stream.texture.width;
    int h = stream.texture.height;

    XColor colors;
    XImage *img = XGetImage(
        stream.display, stream.requested_window,
        0, 0, 
        w, h,
        AllPlanes, ZPixmap
    );

    u_int32_t red_mask = img->red_mask;
    u_int32_t green_mask = img->green_mask;
    u_int32_t blue_mask = img->blue_mask;

    for (int y = 0; y < h; ++y) {
        for (int x = 0; y < w; ++x) {
            unsigned long data = XGetPixel(img, x, y);
            
            stream.window_framebuffer[w * x + y].r = (data & red_mask) >> 16; 
            stream.window_framebuffer[w * x + y].g = (data & green_mask) >> 8;
            stream.window_framebuffer[w * x + y].b = (data & blue_mask);  
            stream.window_framebuffer[w * x + y].a = 0xFF;
        }
    }

    UpdateTexture(stream.texture, stream.window_framebuffer);
}

#endif