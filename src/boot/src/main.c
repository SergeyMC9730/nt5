#include <stdio.h>

#include <nt5emul/boot.h>
#include <nt5emul/renderer.h>
#include <nt5emul/boot_install.h>

#include <cJSON.h>

#include <raylib.h>

#include <sys/stat.h>

void _boot_begin() {
	printf("hello world\n");

	_renderer_create_environment();
	
	mkdir("nt", 0777);

	if (!FileExists("nt/config.json")) {
		_boot_install_begin();
	}
}
