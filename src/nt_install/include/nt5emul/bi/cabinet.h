#pragma once

// creates an array of cab files
void _boot_install_create_cab_files();

// extract cabinet by name
// path value is `{path}/{cab}`
void _boot_install_extract_cabinet(const char *cab, const char *path);