#include <nt5emul/arrays/rsb_array_int.h>
#include <stdio.h>

RSB_ARRAY_IMPL_GEN(int, Int)

void RSBPrintArrayInt(rsb_array_Int *array) {
    for (int i = 0; i < array->len; i++) {
        int obj = RSBGetAtIndexInt(array, i);

        printf("%d ", obj);
    }
}