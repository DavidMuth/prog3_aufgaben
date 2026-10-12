#include <cassert>
#include <cmath>
#include <iostream>
#include <print>
#include <string>

// #define LEVEL 0
#define LEVEL 1
// #define LEVEL 2
// #define LEVEL 3

size_t map_byte2index(uint8_t color, size_t N);
constexpr size_t N = 5;
const std::string COLORS[N] = { " ", "\u2591", "\u2592", "\u2593", "\u2588" };

#if LEVEL > 0
void display(size_t h, size_t w, const uint8_t* image) {
    // TODO
}
#endif

/**
 * Map a byte (0..255) to an index 0..N-1
 *
 * Map the byte values 0..255 into N regions.
 * The first and the last region have half the
 * the "full range" of the other regions.
 *
 * Full region range: 256 / (N-1)
 *
 * For N=5
 * - full region size = 256/(5-1) = 64
 * -> half region size = 32
 *
 * [0   .. 32)             --> 0
 * [32  .. 96)  = 32+64    --> 1
 * [96  .. 160) = 96+64    --> 2
 * [160 .. 224) = 192+64   --> 3
 * [224 .. 256) = 224+32   --> 4
 *
 * @param color: input color (0..255)
 * @param N: the max index+1
 * @return a value between 0..N-1
 */
size_t map_byte2index(uint8_t color, size_t N) {
    // The N indices are points spread over 0..256, with N-1 gaps between them.
    // For N = 5 thats 5 indices with 4, 64 wide gaps.
    // To normalize the gaps + indizes divide by gap size.
    // -> index k now sits at k (0, 1, 2, 3, 4).
    // A color belongs to the nearest index.
    const size_t gaps = N - 1;

    // To normalize the color, color / gap size = color / (256 / gaps) = color * gaps / 256.
    // Only multiply here, divide by 256 later so nothing gets cut off.
    // For color 100: 100 * 4 = 400 (= 400 / 256 = 1.56 gaps from 0).
    const size_t position = static_cast<size_t>(color) * gaps;

    // Nearest index = round(position / 256).
    // Integer division rounds down, + 128 (half of 256) makes it round to nearest.
    // (400 + 128) / 256 = 528 / 256 = 2 -> color 100 maps to index 2.
    const size_t index = (position + 128) / 256;

    return index;
}

#if LEVEL > 1
void set_pixel(size_t h, size_t w, uint8_t* image, size_t y, size_t x, uint8_t color) {
    // TODO
}
#endif

int main() {

    std::println("Implement a display function (for LEVEL==1) to display images with 256 gray LEVELs.");
    std::println("Map the color 0..255 to the 5 gray LEVELs:");
    std::println("- 0..31    => '{0}{0}'", COLORS[0]);
    std::println("- 32..95   => '{0}{0}'", COLORS[1]);
    std::println("- 96..159  => '{0}{0}'", COLORS[2]);
    std::println("- 160..223 => '{0}{0}'", COLORS[3]);
    std::println("- 224..255 => '{0}{0}'", COLORS[4]);
    std::println("For this you need to implement map_byte2index (see unittests/assert/docu).");
    std::cout.flush();

    assert(map_byte2index(0, 5) == 0);
    assert(map_byte2index(31, 5) == 0);
    assert(map_byte2index(32, 5) == 1);
    assert(map_byte2index(95, 5) == 1);
    assert(map_byte2index(96, 5) == 2);
    assert(map_byte2index(159, 5) == 2);
    assert(map_byte2index(160, 5) == 3);
    assert(map_byte2index(223, 5) == 3);
    assert(map_byte2index(224, 5) == 4);
    assert(map_byte2index(255, 5) == 4);

    assert(map_byte2index(0, 2) == 0);
    assert(map_byte2index(127, 2) == 0);
    assert(map_byte2index(128, 2) == 1);
    assert(map_byte2index(255, 2) == 1);

    assert(map_byte2index(0, 3) == 0);
    assert(map_byte2index(63, 3) == 0);
    assert(map_byte2index(64, 3) == 1);
    assert(map_byte2index(191, 3) == 1);
    assert(map_byte2index(192, 3) == 2);
    assert(map_byte2index(255, 3) == 2);

#if LEVEL > 0
    const uint8_t image[] = {
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0xFF,
        0xFF,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0xFF,
        0x00,
        0x00,
        0x00,
        0x77,
        0x00,
        0x00,
        0x00,
        0xAA,
        0x00,
        0x00,
        0x00,
        0xFF,
        0x00,
        0x00,
        0x77,
        0x77,
        0x77,
        0x00,
        0xAA,
        0xAA,
        0xAA,
        0x00,
        0x00,
        0xFF,
        0x00,
        0x00,
        0x00,
        0x77,
        0x00,
        0x00,
        0x00,
        0xAA,
        0x00,
        0x00,
        0x00,
        0x00,
        0xFF,
        0xFF,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
    };

    display(7, 12, image);
#endif

#if LEVEL > 1
    {
        size_t h = 16;
        size_t w = 40;
        uint8_t* myimage = new uint8_t[w * h];
        for (size_t y = 0; y < h; y++) {
            for (size_t x = 0; x < w; x++) {

                // Describe what is the difference between Option 1 and Option 2
                //
                //
                //
                //
                //
                // Option 1:
                uint8_t color = (1.0 + cos(((1.0 * x) / w) * M_PI * 2.0) * cos(((1.0 * y) / h) * M_PI * 2.0)) / 2.0 * 255;
                // Option 2:
                // uint8_t color = (1.0+cos((x/w)*M_PI*2.0)*cos((y/h)*M_PI*2.0))/2.0*255;

                set_pixel(h, w, myimage, y, x, color);
            }
        }

        display(h, w, myimage);
        delete[] myimage;
    }
#endif

#if LEVEL > 2
    {
        size_t h = 40;
        size_t w = 50;
        uint8_t* myimage = new uint8_t[w * h];

        // TODO

        std::println();
        display(h, w, myimage);
        delete[] myimage;
    }
#endif
}