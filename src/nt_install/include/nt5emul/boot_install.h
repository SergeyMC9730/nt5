#pragma once

// include compile time settings
#include <nt5emul/boot_install_settings.h>

// include background renderer functions
#include <nt5emul/boot_install_background.h>

// include all installation steps
#include <nt5emul/boot_install_steps.h>

// installation process structure
#include <nt5emul/nt_install.h>

void _boot_install_begin();
void _boot_install_shortcuts_update(); // global shortcuts

void _boot_install_throw_error(const char *error);