#include "mbedtls/gcm.h"
#include "mbedtls/utils.h"
#include <stdio.h>

static void single_encryption(void) {
    mbedtls_gcm_context ctx;
    unsigned char buf[64];
    unsigned char tag_buf[16];
    int ret;
    mbedtls_cipher_id_t cipher = MBEDTLS_CIPHER_ID_AES;
    // 32 bytes.. that's 256 bits
    const unsigned char key[32] = { 0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
      0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08,
      0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c,
      0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08 };
    unsigned char plaintext[64] = { 0xd9, 0x31, 0x32, 0x25, 0xf8, 0x84, 0x06, 0xe5,
      0xa5, 0x59, 0x09, 0xc5, 0xaf, 0xf5, 0x26, 0x9a,
      0x86, 0xa7, 0xa9, 0x53, 0x15, 0x34, 0xf7, 0xda,
      0x2e, 0x4c, 0x30, 0x3d, 0x8a, 0x31, 0x8a, 0x72,
      0x1c, 0x3c, 0x0c, 0x95, 0x95, 0x68, 0x09, 0x53,
      0x2f, 0xcf, 0x0e, 0x24, 0x49, 0xa6, 0xb5, 0x25,
      0xb1, 0x6a, 0xed, 0xf5, 0xaa, 0x0d, 0xe6, 0x57,
      0xba, 0x63, 0x7b, 0x39, 0x1a, 0xaf, 0xd2, 0x55 };
    unsigned char expected_ciphertext[64] = { 0x42, 0x83, 0x1e, 0xc2, 0x21, 0x77, 0x74, 0x24,
      0x4b, 0x72, 0x21, 0xb7, 0x84, 0xd0, 0xd4, 0x9c,
      0xe3, 0xaa, 0x21, 0x2f, 0x2c, 0x02, 0xa4, 0xe0,
      0x35, 0xc1, 0x7e, 0x23, 0x29, 0xac, 0xa1, 0x2e,
      0x21, 0xd5, 0x14, 0xb2, 0x54, 0x66, 0x93, 0x1c,
      0x7d, 0x8f, 0x6a, 0x5a, 0xac, 0x84, 0xaa, 0x05,
      0x1b, 0xa3, 0x0b, 0x39, 0x6a, 0x0a, 0xac, 0x97,
      0x3d, 0x58, 0xe0, 0x91, 0x47, 0x3f, 0x59, 0x85};
    const unsigned char initial_value[12] = { 0xca, 0xfe, 0xba, 0xbe, 0xfa, 0xce, 0xdb, 0xad,
      0xde, 0xca, 0xf8, 0x88 };
    const unsigned char additional[] = {};

    mbedtls_gcm_init( &ctx );
    // 128 bits, not bytes!
    ret = mbedtls_gcm_setkey( &ctx, cipher, key, 128 );

    ret = mbedtls_gcm_crypt_and_tag(&ctx, MBEDTLS_GCM_ENCRYPT, 64, initial_value, 12, additional, 0, plaintext, buf, 16, tag_buf);
    mbedtls_gcm_free( &ctx );
    if (memcmp(buf, expected_ciphertext, 64) == 0) {
        printf("My local test also works\n");
    } else {
        printf("local test failed\n");
    }

}

int main(void) {
    mbedtls_gcm_self_test(1);
    single_encryption();
    return 0;
}
