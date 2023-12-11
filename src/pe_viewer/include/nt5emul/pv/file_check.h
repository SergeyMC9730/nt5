#pragma once

#include <nt5emul/tui/file_selector.h>

// is file pe
bool _ntPVFileCheck(const char *file_path);

void _ntPVOnFileClick(struct nt_file_selector_menu *menu, const char *file_path);