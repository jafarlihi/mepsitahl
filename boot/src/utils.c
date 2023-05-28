int memcmp(const void *a, const void *b, int n) {
  const unsigned char *aptr = a, *bptr = b;
  for (int i = 0; i < n; i++) {
    if (aptr[i] < bptr[i]) return -1;
    else if (aptr[i] > bptr[i]) return 1;
  }
  return 0;
}
