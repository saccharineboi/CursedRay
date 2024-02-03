// clear out the framebuffer

////////////////////////////////////////////////////////////////////////////////////////////////////
__kernel void clear_color(__global uchar4* framebuffer,
                          uint width, uint height,
                          float r, float g, float b, float a)
{
    uint x = get_global_id(0);
    uint y = get_global_id(1);

    if (x < width && y < height) {
        uint index = y * width + x;

        uchar red = (uchar)(r * 255.0f);
        uchar green = (uchar)(g * 255.0f);
        uchar blue = (uchar)(b * 255.0f);
        uchar alpha = (uchar)(a * 255.0f);

        framebuffer[index] = (uchar4)(red, green, blue, alpha);
    }
}
