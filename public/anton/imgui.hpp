#pragma once

#include <anton/slice.hpp>
#include <anton/string_view.hpp>
#include <anton/math/vector2.hpp>
#include <anton/math/vector4.hpp>

namespace anton::imgui {
    class Context;
    class Viewport;

    using Color = math::Vector4;

    class Widget_Style {
    public:
        Color background_color;
    };

    class Font_Style {
    public:
        rendering::Font_Face* face;
        // Font size in points
        u32 size;
        u32 h_dpi;
        u32 v_dpi;
    };

    class Button_Style {
    public:
        Color border_color;
        Color background_color;
        Color border;
        Color padding;
        Font_Style font;
    };

    class Style {
    public:
        Color background_color;
        Color preview_guides_color;
        Color preview_color;
        Widget_Style widgets;
        Button_Style button;
        Button_Style hot_button;
        Button_Style active_button;
    };

    class Settings {
    public:
        f32 window_drop_area_width;
    };

    Context* create_context(Font_Style default_font);
    void destroy_context(Context*);

    // Main viewport's native window is not owned by imgui.
    void set_main_viewport_native_window(Context&, windowing::Window*);

    void set_default_font(Context&, Font_Style);
    void set_default_style_default_dark(Context&);
    void set_default_style(Context&, Style);
    Style get_default_style(Context&);

    void begin_frame(Context&);
    void end_frame(Context&);

    class Input_State {
    public:
        math::Vector2 cursor_position;
        bool left_mouse_button;
        bool right_mouse_button;
    };

    void set_input_state(Context&, Input_State);
    Input_State get_input_state(Context&);

    class Vertex {
    public:
        math::Vector2 position;
        math::Vector2 uv;
        struct Color {
            u8 r;
            u8 g;
            u8 b;
            u8 a;
        } color;
    };

    class Draw_Command {
    public:
        u32 element_count;
        u32 vertex_offset;
        u32 index_offset;
        // texture 0 means no texture is associated with this draw command
        u64 texture;
    };

    Slice<Viewport* const> get_viewports(Context&);
    windowing::Window* get_viewport_native_window(Context&, Viewport&);
    Slice<Draw_Command const> get_viewport_draw_commands(Context&, Viewport&);

    Slice<Vertex const> get_vertex_data(Context&);
    Slice<u32 const> get_index_data(Context&);

    void begin_window(Context&, String_View, bool new_viewport = false);
    void end_window(Context&);

    enum class Button_State {
        inactive, hot, clicked,
    };

    // Generic widget to group other widgets and manage layout.
    void begin_widget(Context&, String_View identifier, Widget_Style options);
    void end_widget(Context&);

    void text(Context&, String_View text, Font_Style font);
    Button_State button(Context&, String_View text);
    Button_State button(Context&, String_View text, Button_Style style, Button_Style hovered_style, Button_Style active_style);
    void image(Context&, u64 texture, math::Vector2 size, math::Vector2 uv_top_left, math::Vector2 uv_bottom_right);

    // Modifiers

    // Get style of current widget or window.
    Style get_style(Context&);
    // Set style of current widget or window.
    void set_style(Context&, Style);

    void set_window_border_area(Context&, f32);

    // Sets the content size of the current window.
    // This function has any effect only when the current window is the only one in
    // a viewport, in which case both the window and the viewport are resized.
    // Otherwise this function has no effect.
    //
    void set_window_size(Context&, math::Vector2 size);

    // Sets the screen position of the current window.
    // This function has any effect only when the current window is the only one in
    // a viewport, in which case both the window and the viewport are repositioned.
    // Otherwise this function has no effect.
    //
    void set_window_pos(Context&, math::Vector2 screen_pos);

    void set_width(Context&, f32 width);
    void set_height(Context&, f32 height);
    math::Vector2 get_window_dimensions(Context&);
    math::Vector2 get_cursor_position(Context&);

    // State queries

    bool is_window_hot(Context&);
    bool is_window_active(Context&);
} // namespace anton::imgui
