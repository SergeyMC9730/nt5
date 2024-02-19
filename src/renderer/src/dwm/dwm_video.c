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

#include <nt5emul/dwm/video.h>

struct dwm_video _ntDwmLoadVideo(const char *path) {
    // create object
    struct dwm_video vid = {
        .stream = NULL,
        .path = path
    };
    
    // check if file exists
    if (!FileExists(path)) return vid;

    vid.stream = OpenVideoStream(path);
    vid.texture = LoadTextureFromVideoStream(vid.stream);

    return vid;
}

void _ntDwmUnloadVideo(struct dwm_video obj) {
    // check if videostream has been created.
    // if not - don't do anything
    if (!obj.stream) return;

    // unload video stream
    UnloadVideoStream(obj.stream);

    return;
}

void _ntDwmUpdateVideo(struct dwm_video vid) {
    // check if videostream has been created.
    // if not - don't do anything
    if (!vid.stream) return;

    // update texture of the videostream
    UpdateTextureFromVideoStream(&vid.texture, vid.stream);
}