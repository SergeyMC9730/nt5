int _ntSortComparison(const int *a, const int *b) {
    int i_a = *a;
    int i_b = *b;

    if (i_a == i_b) return 0;
    if (i_a < i_b) return -1;

    return 1;
}