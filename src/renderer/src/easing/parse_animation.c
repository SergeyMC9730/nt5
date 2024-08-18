/*
    nt5 -- Windows XP simulator.
    Copyright (C) 2024  Sergei Baigerov

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

#include <nt5emul/renderer_animation.h>
#include <nt5emul/renderer_keyframe.h>
#include <cJSON.h>
#include <raylib.h>
#include <stdio.h>
#include <string.h>

struct renderer_animation *_ntRendererLoadAnimation(const char *path) {
    if (path == NULL || !FileExists(path)) return NULL;

    // load data from PATH to text. we expect data from path to be UTF-8 or ASCII text
    char *text = LoadFileText(path);

    // lets try to interpret this text as JSON object
    cJSON *root = cJSON_Parse(text);

    if (root == NULL) {
        // parsing failed. cleaning everything
        // and returning NULL

        MemFree(text);
        return NULL;
    }

    // create renderer_animation object
    struct renderer_animation *result = (struct renderer_animation *)MemAlloc(sizeof(struct renderer_animation));

    // now we need to get some variables and
    // put them into the renderer_animation struct

    // single pointer would be used for getting all
    // required entries because it would save some
    // stack space

    // try to get reference to the linked animation. 
    // we need a file path to this anim
    cJSON *tmp_obj = cJSON_GetObjectItem(root, "linked_animation_path");
    if (tmp_obj) {
        // we expect this object to be string so lets try to get
        // the string from it
        const char *linked_animation_path = cJSON_GetStringValue(tmp_obj);

        if (linked_animation_path) {
            // path should be valid inside the dir where
            // root file is located
            const char *root_path = GetDirectoryPath(path);

            // allocate enough memory to work with
            size_t sz = strlen(root_path) + strlen(linked_animation_path) + 4;
            char *tmp = MemAlloc(sz);
            
            // create filepath for the linked animation
            snprintf(tmp, sz, "%s/%s", root_path, linked_animation_path);
        
            // try to parse this linked animation
            struct renderer_animation *lanim = _ntRendererLoadAnimation(tmp);
            result->linked_animation = lanim;

            MemFree(tmp);
        }
    }

    // try to get 'influenced' flag
    tmp_obj = cJSON_GetObjectItem(root, "influenced");
    if (tmp_obj) {
        bool value = cJSON_IsTrue(tmp_obj);

        // we also need to check if linked_animation is valid
        result->influenced = value && result->linked_animation != NULL;
    }

    // try to get animation id
    tmp_obj = cJSON_GetObjectItem(root, "anim_id");
    if (tmp_obj) {
        // we should check if object is number this time
        // cjson would return NAN if object is not a number

        if (cJSON_IsNumber(tmp_obj)) {
            result->anim_id = (int)cJSON_GetNumberValue(tmp_obj);
        } else {
            printf("parse_animation.c: anim_id is not a number (NAN)\n");
        }
    }

    // try to get starting value
    tmp_obj = cJSON_GetObjectItem(root, "starting_value");
    if (tmp_obj) {
        if (cJSON_IsNumber(tmp_obj)) {
            result->starting_value = cJSON_GetNumberValue(tmp_obj);
        } else {
            printf("parse_animation.c: starting_value is not a number (NAN)\n");
        }
    }

    // try to get keyframes array
    tmp_obj = cJSON_GetObjectItem(root, "keyframes");
    
    // check if tmp_obj is valid and is an array
    if (tmp_obj && cJSON_IsArray(tmp_obj)) {
        // get size of this array
        size_t array_size = cJSON_GetArraySize(tmp_obj);
        result->count = array_size;

        // allocate enough memory for the keyframe array
        result->keyframes = (struct renderer_keyframe *)MemAlloc(array_size * sizeof(struct renderer_keyframe));

        // now lets go through each element in the
        // array and parse them

        for (int i = 0; i < cJSON_GetArraySize(tmp_obj); i++) {
            // get object from the array
            cJSON *obj = cJSON_GetArrayItem(tmp_obj, i);
            
            // check if obj is valid and is an object
            if (obj && cJSON_IsObject(obj)) {
                // parse keyframe
                struct renderer_keyframe keyframe = _ntRendererLoadKeyframe(obj);
            
                // check if keyframe is not valid
                if (keyframe.length < 0) continue;

                // copy keyframe to the keyframe array
                result->keyframes[i] = keyframe;
            } else {
                printf("parse_animation.c: array element with invalid type found\n");
            }
        }
    }

    // set 'valid' flag. 
    // we should take in a mind that keyframes array should be valid

    result->valid = true && result->keyframes != NULL;

    return result;
}