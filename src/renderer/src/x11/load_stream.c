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

#include <string.h>
#include <stdio.h>

renderer_x11_window_stream_t _ntLoadXWindowStream(const char *_window_name) {
    renderer_x11_window_stream_t stream = {};

    stream.window_name = _window_name;

    // open main display
    stream.display = XOpenDisplay(NULL);
    // get root window
    stream.root_window = XRootWindow(stream.display, DefaultScreen(stream.display));

    printf("stream.display = %p\nstream.window_name = %s\nstream.root_window = %d\ndefault screen=%d", stream.display, _window_name, stream.root_window, DefaultScreen(stream.display));

    bool window_exists = false;

    // get internal x atom by name
    Atom atom = XInternAtom(stream.display, "_NET_CLIENT_LIST", true);
    Atom actual_atom;

    // init some valuse

    int format = 0;

    u_int32_t items = 0;
    u_int32_t sz = 0;

    // init window data buffer
    u_int8_t *data = NULL;
    char *window_name = NULL;

    // get root window properties
    int prop_status = XGetWindowProperty(
        stream.display, stream.root_window, atom, 
        0L, (~0L), false, 
        AnyPropertyType, &actual_atom, &format,
        &items, &sz, &data
    );

    Window *list = (Window *)data;

    printf("list=%p; items=%d; sz=%d\n", list, items, sz);

    if (prop_status < Success || items == 0 || list == NULL) {
        // free memory on fail

        printf("XGetWindowProperty failed; items variable failed; list variable is null\n");

        if (window_name != NULL) XFree(window_name);
        if (data != NULL) XFree(data);

        return stream;
    }

    for (int i = 0; i < items; i++) {
        printf("list[i(%d)]=%d\n", i, list[i]);

        prop_status = XFetchName(stream.display, list[i], &window_name);
    
        if (prop_status < Success || !window_name) continue;

        // check if window titles are matching
        if (!strcmp(window_name, _window_name)) {
            // set window values
            stream.requested_window = list[i];
            window_exists = true;

            break;
        }
    }

    // free memory
    if (window_name != NULL) XFree(window_name);
    if (data != NULL) XFree(data);

    // check if window has been not found:
    // return invalid stream
    if (!window_exists) return stream;
    
    // get window attribute
    XGetWindowAttributes(stream.display, stream.requested_window, &stream.window_attributes);

    // get window sizes
    int width = stream.window_attributes.width;
    int height = stream.window_attributes.height;

    // load new texture
    stream.texture.id = rlLoadTexture(NULL, width, height, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);
	stream.texture.width = width;
	stream.texture.height = height;
	stream.texture.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
	stream.texture.mipmaps = 1;

    // allocate framebuffer
    stream.window_framebuffer = (Color *)MemAlloc(width * height * sizeof(Color));

    return stream;
}

#endif