#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1024

typedef struct {
    char filename[100];
    char password[50];
} FileMetadata;

void xor_encrypt_decrypt(char *data, const char *key) {
    size_t len = strlen(data);
    size_t key_len = strlen(key);
    for (size_t i = 0; i < len; i++) {
        data[i] ^= key[i % key_len];
    }
}

void protect_file(const FileMetadata *meta) {
    FILE *fp = fopen(meta->filename, "r+");
    if (!fp) {
        perror("File open failed");
        return;
    }

    char buffer[MAX_LEN];
    fread(buffer, sizeof(char), MAX_LEN, fp);
    xor_encrypt_decrypt(buffer, meta->password);

    rewind(fp);
    fwrite(buffer, sizeof(char), strlen(buffer), fp);
    fclose(fp);

    printf("File '%s' encrypted/decrypted successfully.\n", meta->filename);
}

int main() {
    FileMetadata meta;

    printf("Enter file name to protect: ");
    scanf("%s", meta.filename);

    printf("Enter password: ");
    scanf("%s", meta.password);

    protect_file(&meta);

    return 0;
}
