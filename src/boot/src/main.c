#include <stdio.h>

#include <nt5emul/boot.h>
#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

#include <cJSON.h>

#include <raylib.h>

#include <sys/stat.h>

void _boot_begin() {
	// create "nt" folder
	mkdir("nt", 0777);

	// init NT renderer
	_renderer_create_environment();
	
	// begin installation process if config is not found
	if (!FileExists("nt/config.json")) {
		_boot_install_begin();

		return;
	}

	_boot_try_parse_explorer();
}
