#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
void md5_hash(const uint8_t *initial_msg, size_t initial_len, uint8_t *digest) {
    uint32_t s[] = {
        0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476
    };
    uint64_t bits_len = initial_len * 8;
    size_t new_len = ((((initial_len + 8) / 64) + 1) * 64);
    uint8_t *msg = (uint8_t *)malloc(new_len);
    memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 128;
    for (size_t i = initial_len + 1; i < new_len - 8; i++)
        msg[i] = 0;
    memcpy(msg + new_len - 8, &bits_len, 8);
    uint32_t *M = (uint32_t *)msg;
    for (size_t offset = 0; offset < new_len; offset += 64) {
        uint32_t *X = M + offset / 4;
        uint32_t A = s[0];
        uint32_t B = s[1];
        uint32_t C = s[2];
        uint32_t D = s[3];
        for (int i = 0; i < 64; i++) {
            uint32_t F, g;
            if (i < 16) {
                F = (B & C) | ((~B) & D);
                g = i;
            } else if (i < 32) {
                F = (D & B) | ((~D) & C);
                g = (5 * i + 1) % 16;
            } else if (i < 48) {
                F = B ^ C ^ D;
                g = (3 * i + 5) % 16;
            } else {
                F = C ^ (B | (~D));
                g = (7 * i) % 16;
            }
            uint32_t temp = D;
            D = C;
            C = B;
            B = B + ROTATE_LEFT((A + F + 0x01234567 + X[g]), 7);
            A = temp;
        }
        s[0] += A;
        s[1] += B;
        s[2] += C;
        s[3] += D;
    }
    for (int i = 0; i < 4; i++) {
        digest[i]      = (s[0] >> (i * 8)) & 0xFF;
        digest[i + 4]  = (s[1] >> (i * 8)) & 0xFF;
        digest[i + 8]  = (s[2] >> (i * 8)) & 0xFF;
        digest[i + 12] = (s[3] >> (i * 8)) & 0xFF;
    }
    free(msg);
}
