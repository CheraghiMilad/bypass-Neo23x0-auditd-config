#include <stdio.h>
#include <dlfcn.h>

int main() {
    void *handle;
    char *error;

    handle = dlopen("./libstealer.so", RTLD_NOW);
    if (!handle) {
        fprintf(stderr, "[-] dlopen failed: %s\n", dlerror());
        return 1;
    }

    printf("[+] Library loaded successfully.\n");

    dlclose(handle);
    return 0;
}
