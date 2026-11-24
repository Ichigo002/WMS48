#ifndef BYTE_READER
#define BYTE_READER

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/*
u8 - unsigned integer 8 bits 0 - 255
i8 - signed integer 8 bits -127 - 127
*/

class ByteReader
{
public:
    ByteReader(const uint8_t *data, size_t len)
        : p(data), left(data ? len : 0) {}

    size_t remaining() const { return left; }
    bool empty() const { return left == 0; }

    bool u8(uint8_t &out) {
        if (left < 1) return false;
        out = p[0];
        advance(1);
        return true;
    }
    bool i8(int8_t &out) {
        uint8_t v;
        if (!u8(v)) return false;
        out = (int8_t)v;
        return true;
    }

    bool u16(uint16_t &out) {
        if (left < 2) return false;
        out = (uint16_t)(p[0] | (p[1] << 8));
        advance(2);
        return true;
    }
    bool i16(int16_t &out) {
        uint16_t v;
        if (!u16(v)) return false;
        out = (int16_t)v;
        return true;
    }

    bool u32(uint32_t &out) {
        if (left < 4) return false;
        out = (uint32_t)p[0] | ((uint32_t)p[1] << 8) |
              ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
        advance(4);
        return true;
    }
    bool i32(int32_t &out) {
        uint32_t v;
        if (!u32(v)) return false;
        out = (int32_t)v;
        return true;
    }

    bool f32(float &out) {
        uint32_t v;
        if (!u32(v)) return false;
        memcpy(&out, &v, sizeof(out));   // safe way to reinterpret bits
        return true;
    }

    bool bytes(const uint8_t *&out, size_t len) {
        if (left < len) return false;
        out = p;
        advance(len);
        return true;
    }

    bool skip(size_t len) {
        if (left < len) return false;
        advance(len);
        return true;
    }

    // Copies len bytes into buf as a C string. Fails if len doesn't fit.
    bool string(char *buf, size_t bufSize, size_t len) {
        if (bufSize == 0 || len > bufSize - 1 || left < len) return false;
        memcpy(buf, p, len);
        buf[len] = '\0';
        advance(len);
        return true;
    }

private:
    void advance(size_t n) { p += n; left -= n; }

    const uint8_t *p;
    size_t left;
};


#endif