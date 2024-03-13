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

#include <stdio.h>

void _ntUpdateXWindowStream(renderer_x11_window_stream_t *stream) {
    if (stream->texture.width == 0 || stream->texture.height == 0 || stream->window_framebuffer == NULL) return;
   
    XWindowAttributes window_attributes;

    // get window attribute
    XGetWindowAttributes(stream->display, stream->requested_window, &window_attributes);

    // get window sizes
    int _width = window_attributes.width;
    int _height = window_attributes.height;

    stream->window_attributes = window_attributes;

    // printf("_width=%d; _height=%d\n", _width, _height);

    int w = stream->texture.width;
    int h = stream->texture.height;

    XColor colors;
    XImage *img = XGetImage(
        stream->display, stream->requested_window,
        0, 0, 
        _width, _height,
        AllPlanes, ZPixmap
    );

    // check if image can be created
    if (!img) return;

    if (_width != w || _height != h) {
        printf("----------- resizing texture\n");

        // unload old texture
        UnloadTexture(stream->texture);

        // update width and height variables
        w = _width;
        h = _height;

        // create new texture with updated width and/or height
        stream->texture.id = rlLoadTexture(NULL, w, h, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);
        stream->texture.width = w;
        stream->texture.height = h;
        stream->texture.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
        stream->texture.mipmaps = 1;

        // reallocate framebuffer to have updated width and/or height
        stream->window_framebuffer = (Color *)MemRealloc(stream->window_framebuffer, _width * _height * sizeof(Color));
    }

    Color *color_data = (Color *)img->data;

    // for (int y = 0; y < h; y++) {
    //     for (int x = 0; x < w; x++) {
    //         int pos = h * y + x;

    //         stream->window_framebuffer[pos].r = color_data[pos].b;
    //         stream->window_framebuffer[pos].g = color_data[pos].g;
    //         stream->window_framebuffer[pos].b = color_data[pos].r;

    //         stream->window_framebuffer[pos].a = 0xFF;
    //     }
    // }

    int sz = w * h;
    for (int i = 0; i < sz; i++) {
        stream->window_framebuffer[i].r = color_data[i].b;
        stream->window_framebuffer[i].g = color_data[i].g;
        stream->window_framebuffer[i].b = color_data[i].r;

        stream->window_framebuffer[i].a = 0xFF;

    }

    UpdateTexture(stream->texture, stream->window_framebuffer);

    free(img->data);
}

#endif