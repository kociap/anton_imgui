#pragma once

#include <anton/slice.hpp>
#include <anton/string_view.hpp>
#include <anton/math/vector2.hpp>
#include <anton/math/vector4.hpp>

namespace anton::imgui {
    class Context;
    class Viewport;
    class Native_Window;
    class Font_Face;

    using Color = math::Vector4;

    class Widget_Style {
    public:
        Color background_color;
    };

    class Font_Style {
    public:
        Font_Face* face;
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

    class Client_Interface;
    Context* create_context(Client_Interface* interface, Font_Style default_font);
    
    // destroy_context
    // Does not destroy the Client_Interface.
    //
    void destroy_context(Context* ctx);

    // set_main_viewport_native_window
    // Main viewport's native window is not owned by imgui.
    //
    void set_main_viewport_native_window(Context& ctx, Native_Window* native_window);

    void set_default_font(Context& ctx, Font_Style font_style);
    void set_default_style_default_dark(Context& ctx);
    void set_default_style(Context& ctx, Style style);
    Style get_default_style(Context& ctx);

    void begin_frame(Context& ctx);
    void end_frame(Context& ctx);

    class Input_State {
    public:
        math::Vector2 cursor_position;
        bool left_mouse_button;
        bool right_mouse_button;
    };

    void set_input_state(Context& ctx, Input_State input_state);
    Input_State get_input_state(Context& ctx);

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
        // texture 0 means no texture is associated with this draw command
        u64 texture;
        u32 element_count;
        u32 vertex_offset;
        u32 index_offset;
    };

    Slice<Viewport* const> get_viewports(Context& ctx);
    Native_Window* get_viewport_native_window(Context& ctx, Viewport& viewport);
    Slice<Draw_Command const> get_viewport_draw_commands(Context& ctx, Viewport& viewport);

    Slice<Vertex const> get_vertex_data(Context& ctx);
    Slice<u32 const> get_index_data(Context& ctx);

    void begin_window(Context& ctx, String_View identifier);
    void end_window(Context& ctx);

    enum class Button_State {
        inactive, hot, clicked,
    };

    // Generic widget to group other widgets and manage layout.
    void begin_widget(Context& ctx, String_View identifier, Widget_Style options);
    void end_widget(Context& ctx);

    void text(Context& ctx, String_View text, Font_Style font);
    Button_State button(Context& ctx, String_View text);
    Button_State button(Context& ctx, String_View text, Button_Style style, Button_Style hovered_style, Button_Style active_style);
    void image(Context& ctx, u64 texture, math::Vector2 size, math::Vector2 uv_top_left, math::Vector2 uv_bottom_right);

    // Modifiers

    // Get style of current widget or window.
    Style get_style(Context& ctx);
    // Set style of current widget or window.
    void set_style(Context& ctx, Style style);

    void set_window_border_area(Context& ctx, f32 width);

    // Sets the content size of the current window.
    // This function has any effect only when the current window is the only one in
    // a viewport, in which case both the window and the viewport are resized.
    // Otherwise this function has no effect.
    //
    void set_window_size(Context& ctx, math::Vector2 size);

    // Sets the screen position of the current window.
    // This function has any effect only when the current window is the only one in
    // a viewport, in which case both the window and the viewport are repositioned.
    // Otherwise this function has no effect.
    //
    void set_window_pos(Context& ctx, math::Vector2 screen_pos);

    void set_width(Context& ctx, f32 width);
    void set_height(Context& ctx, f32 height);
    math::Vector2 get_window_dimensions(Context& ctx);
    math::Vector2 get_cursor_position(Context& ctx);

    // State queries

    bool is_window_hot(Context& ctx);
    bool is_window_active(Context& ctx);
} // namespace anton::imgui
