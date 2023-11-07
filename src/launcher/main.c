#include <stdio.h>

#include <nt5emul/boot.h>
#include <nt5emul/renderer.h>

int main() {
	_boot_begin();

	_renderer_join();

	return 0;
}