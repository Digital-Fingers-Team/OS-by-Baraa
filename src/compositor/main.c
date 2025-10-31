// Minimal Wayland compositor using wlroots
// Based on wlroots examples

#include <wayland-server.h>
#include <wlr/backend.h>
#include <wlr/render/wlr_renderer.h>
#include <wlr/types/wlr_output.h>
#include <wlr/util/log.h>

struct blackbox_server
{
    struct wl_display *wl_display;
    struct wlr_backend *backend;
    struct wlr_renderer *renderer;
};

int main()
{
    wlr_log_init(WLR_DEBUG, NULL);

    struct blackbox_server server = {0};

    server.wl_display = wl_display_create();
    server.backend = wlr_backend_autocreate(server.wl_display, NULL);
    server.renderer = wlr_renderer_autocreate(server.backend);

    wl_display_run(server.wl_display);

    wl_display_destroy(server.wl_display);
    return 0;
}
