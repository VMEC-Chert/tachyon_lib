
namespace tyon
{
struct bmp_rgba_header
{

    u8 signature[2];
    u32 file_size;
    u32 _reserved;
    u32 data_offset;
    // infoheader
    u32 info_header_size;
    i32 image_width;
    i32 image_height;
    u16 image_planes;
    u16 bit_depth;
    u32 compression_type;
    u32 compressed_image_size;
    i32 x_pixels_per_meter;
    i32 y_pixels_per_meter;
    u32 colors_used;
    u32 colors_important;
    u32 red_mask;
    u32 green_mask;
    u32 blue_mask;
    u32 alpha_mask;
    u32 colorspace;
};
#pragma pack(pop)

inline
PROC asset_image_save_bmp( image<rgba>* arg ) -> fresult
{
    push_allocator _al1 {g_thread->scratch };
    i64 redzone = 64;
    i64 size_bytes =arg->size_bytes();
    bmp_rgba_header header {
        .signature = { 'B', 'M' },
        .file_size = sizeof(bmp_rgba_header) + size_bytes + redzone,
        ._reserved = 0,
        .data_offset = sizeof(bmp_rgba_header),
        // BITMAPV4HEADER info header (108 bytes)
        .info_header_size = 108,
        .image_width = arg->size.x,
        .image_height = arg->size.y,
        .image_planes = 1,
        .bit_depth = 32,
        .compression_type = size_bytes,
        .compressed_image_size = 3,
        .x_pixels_per_meter = 2835,
        .y_pixels_per_meter = 2835,
        // Use all colours
        .colors_used = 0,
        .colors_important = 0,

        .red_mask = 0x000000FFu,
        .green_mask = 0x0000FF00u,
        .blue_mask = 0x00FF0000u,
        .alpha_mask = 0xFF000000u,
        // LCS_CALIBRATED_RGB
        .colorspace = 0x73524742u,
    };

    file output_file { .filename = "test_text.bmp" };
    output_file.memory.data = memory_allocate_raw( size_bytes );
    output_file.memory.size = size_bytes;
    bool write_ok = file_write_binary( &output_file );
    if (! write_ok)
    {   TYON_ERRORF( "Failed to write bmp file '{}'", output_file.filename );
    }
    return write_ok;
}

}
