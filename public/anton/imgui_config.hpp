#pragma once

#include <anton/types.hpp>
#include <anton/math/vector2.hpp>
#include <anton/string_view.hpp>
#include <anton/vector.hpp>

namespace anton::imgui {
    class Context;
    class Native_Window;
    class Font_Face;

    class Font_Render_Info {
    public:
        u32 points;
        u32 h_dpi;
        u32 v_dpi;
    };

    // All metrics are expressed in font units.
    //
    class Face_Metrics {
    public:
        // The typographic ascender of the face.
        i32 ascender;
        // The typographic descender of the face (negative if below baseline).
        i32 descender;
        // Distance between 2 consecutive baselines.
        i32 line_height;
        i32 glyph_x_max;
        i32 glyph_x_min;
        i32 glyph_y_max;
        i32 glyph_y_min;
        i32 max_advance;
        // font units per em
        i32 units_per_em;
    };

    // All metrics are expressed in 26.6 pixel format (1/64 of a pixel precision).
    //
    class Glyph_Metrics {
    public:
        // Width of the glyph.
        i32 width;
        // Height of the glyph.
        i32 height;
        // Horizontal offset from the pen position.
        i32 bearing_x;
        // Height above the baseline.
        i32 bearing_y;
        i32 advance;
    };

    class Glyph {
    public:
        Glyph_Metrics metrics;
        // Handle to a texture.
        u64 texture;
        // uv coordinates of the glyph in the texture.
        Rect_f32 uv;
    };

    using window_activate_fn = void (*)(Native_Window* window, bool activated, void* user_data);

    class Client_Interface {
    public:
        virtual Native_Window* create_window(i64 width, i64 height, bool decorated) = 0;
        virtual void destroy_window(Native_Window* window) = 0;
        virtual void set_window_activate_callback(Native_Window* window, window_activate_fn, void* user_data) = 0;
        virtual math::Vector2 get_window_size(Native_Window* window) = 0;
        virtual void set_window_size(Native_Window* window, math::Vector2 size) = 0;
        virtual math::Vector2 get_window_pos(Native_Window* window) = 0;
        virtual void set_window_pos(Native_Window* window, math::Vector2 pos) = 0;

        virtual Face_Metrics get_face_metrics(Font_Face* face) = 0;
        virtual i64 compute_text_width(Font_Face* face, Font_Render_Info info, String_View text) = 0;
        virtual Vector<Glyph> render_text(Font_Face* face, Font_Render_Info info, String_View text) = 0;
    };
}
