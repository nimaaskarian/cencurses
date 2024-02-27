#define init_2darray(T, name, n, m) T ** #name = malloc(n * sizeof(*T)); \\
for (int i = 0; i < n; i++) { \\
  #name[i] = malloc(m * sizeof(*#name[i])); \\
} \\
