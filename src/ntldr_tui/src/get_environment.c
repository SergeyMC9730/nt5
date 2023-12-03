#include <nt5emul/tui/environment.h>

extern struct nt_tui_environment _ntTuiEnvironment;

struct nt_tui_environment *_ntGetTuiEnvironment() {
    return &_ntTuiEnvironment;
}