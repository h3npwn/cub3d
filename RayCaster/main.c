#include <math.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <mlx.h>
#include <stdbool.h>

char *map[] = {
    "1111111111",
    "1000000001",
    "1011111101",
    "1000000101",
    "1011110101",
    "1000000001",
    "1111111111",
    NULL
};

typedef struct { double x; double y; } t_vector;

#define X 0
#define Y 1
#define TILE_SIZE 64

/* Field of view and ray settings */
#define FOV (60.0 * M_PI / 180.0)
#define NUM_RAYS 120
#define MAX_VIEW_DIST 20.0

typedef struct imageframe{
    void *img;
    char *addr;
    int bpp;
    int line_len;
    int endian;
    int width;
    int height;
} t_img;

typedef struct controls{
    bool up;
    bool down;
    bool left;
    bool right;
    bool rot_left;
    bool rot_right;
} t_controls;

static void mlx_image_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    if (!img || !img->addr)
        return ;
    if (x < 0 || y < 0)
        return ;
    if (x >= img->width || y >= img->height)
        return ;

    dst = img->addr + (y * img->line_len) + (x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}

static bool is_wall_at(double x, double y)
{
    int gx = (int)x;
    int gy = (int)y;
    if (gy < 0 || gy >= 7 || gx < 0 || gx >= 10)
        return true;
    return (map[gy][gx] == '1');
}

static void try_move(t_vector *pos, double nx, double ny)
{
    if (!is_wall_at(nx, ny))
    {
        pos->x = nx;
        pos->y = ny;
    }
}

static void draw_map(t_img *frame)
{
    for (int y = 0; map[y]; y++)
    {
        for (int x = 0; map[y][x]; x++)
        {
            if (map[y][x] == '1')
            {
                for (int py = 0; py < TILE_SIZE; py++)
                    for (int px = 0; px < TILE_SIZE; px++)
                        mlx_image_pixel_put(frame, x * TILE_SIZE + px, y * TILE_SIZE + py, 0x808080);
            }
        }
    }
}

static void draw_circle(t_img *frame, int cx, int cy, int radius, int color)
{
    for (int y = -radius; y <= radius; y++)
        for (int x = -radius; x <= radius; x++)
            if (x * x + y * y <= radius * radius)
                mlx_image_pixel_put(frame, cx + x, cy + y, color);
}

static void draw_line(t_img *frame, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;

    while (1)
    {
        mlx_image_pixel_put(frame, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

/* Raycast single ray in direction (dx,dy) starting at pos; returns hit grid pos in hitx,hity */
static void cast_ray(t_vector pos, t_vector dir, double max_dist, double *hitx, double *hity)
{
    double dist = 0.0;
    while (dist < max_dist)
    {
        double hx = pos.x + dir.x * dist;
        double hy = pos.y + dir.y * dist;
        int gx = (int)hx;
        int gy = (int)hy;
        if (gy < 0 || gy >= 7 || gx < 0 || gx >= 10 || map[gy][gx] == '1')
        {
            *hitx = hx;
            *hity = hy;
            return;
        }
        dist += 0.01;
    }
    *hitx = pos.x + dir.x * max_dist;
    *hity = pos.y + dir.y * max_dist;
}

/* Clear frame quickly by zeroing data */
static void clear_frame(t_img *frame)
{
    if (!frame || !frame->addr) return;
    memset(frame->addr, 0, frame->line_len * frame->height);
}

/* Controls and state (kept in static for simplicity) */
static t_controls g_ctrl = {0};
static t_vector g_player_pos = {3.5, 3.5};
static double g_rot_angle = 0.0; /* radians */

static int on_key_press(int keycode, void *param)
{
    (void)param;
    if (keycode == 65307) /* ESC */ exit(0);
    if (keycode == 'w') g_ctrl.up = true;
    if (keycode == 's') g_ctrl.down = true;
    if (keycode == 'a') g_ctrl.left = true;
    if (keycode == 'd') g_ctrl.right = true;
    if (keycode == 65361) g_ctrl.rot_left = true;
    if (keycode == 65363) g_ctrl.rot_right = true;
    return (0);
}
static int on_key_release(int keycode, void *param)
{
    (void)param;
    if (keycode == 'w') g_ctrl.up = false;
    if (keycode == 's') g_ctrl.down = false;
    if (keycode == 'a') g_ctrl.left = false;
    if (keycode == 'd') g_ctrl.right = false;
    if (keycode == 65361) g_ctrl.rot_left = false;
    if (keycode == 65363) g_ctrl.rot_right = false;
    return (0);
}
#include <sys/time.h>
static void sleep(int microseconds)
{
    struct timeval start, current;
    gettimeofday(&start, NULL);
    do {
        gettimeofday(&current, NULL);
        long elapsed = (current.tv_sec - start.tv_sec) * 1000000L
                        + (current.tv_usec - start.tv_usec);
        if (elapsed >= microseconds)
            break;
    } while (1);
}

static int update_loop(void *data)
{
    t_img *frame = (t_img *)data;
    double move_speed = 0.06; /* units per tick */
    double rot_speed = 5.0 * (M_PI / 180.0);
    sleep(60000); /* simple frame limiter ~60fps */
    /* handle rotation */
    if (g_ctrl.rot_left) g_rot_angle -= rot_speed;
    if (g_ctrl.rot_right) g_rot_angle += rot_speed;

    /* compute forward/backward direction */
    t_vector dir = { cos(g_rot_angle), sin(g_rot_angle) };
    t_vector right = { cos(g_rot_angle + (M_PI / 2.0)), sin(g_rot_angle + (M_PI / 2.0)) };
 
    clear_frame(frame);
    draw_map(frame);

    int sx = (int)(g_player_pos.x * TILE_SIZE);
    int sy = (int)(g_player_pos.y * TILE_SIZE);

    /* cast NUM_RAYS across the player's FOV */
    for (int i = 0; i < NUM_RAYS; i++)
    {   
        
    }

    /* draw player marker */
    draw_circle(frame, sx, sy, 4, 0xFF0000);

    /* push to window */
    void *mlx = NULL; /* we don't store mlx here; mlx_put_image_to_window will be called from main's stored mlx */
    /* To avoid changing function signature, fetch mlx and win from frame->img via platform specifics is not portable here.
       Instead, we'll store current mlx and win as static globals in main below by setting g_mlx/g_win before starting loop. */

    /* We'll call mlx_put_image_to_window via global variables updated in main */
    extern void *g_mlxp(void);
    extern void *g_winp(void);
    void *g_m = g_mlxp();
    void *g_w = g_winp();
    if (g_m && g_w)
        mlx_put_image_to_window(g_m, g_w, frame->img, 0, 0);

    return (0);
}

/* globals for access inside update */
static void *g_mlx = NULL;
static void *g_win = NULL;
void *g_mlxp(void) { return g_mlx; }
void *g_winp(void) { return g_win; }

int main(void)
{
    g_mlx = mlx_init();
    if (!g_mlx) return (1);
    g_win = mlx_new_window(g_mlx, 640, 480, "RayCaster");
    t_img frame;
    memset(&frame, 0, sizeof(frame));
    frame.img = mlx_new_image(g_mlx, 640, 480);
    frame.width = 640;
    frame.height = 480;
    frame.addr = mlx_get_data_addr(frame.img, &frame.bpp, &frame.line_len, &frame.endian);

    /* initial draw */
    clear_frame(&frame);
    draw_map(&frame);
    mlx_put_image_to_window(g_mlx, g_win, frame.img, 0, 0);

    /* hooks */
    mlx_hook(g_win, 2, 1L<<0, on_key_press, NULL);
    mlx_hook(g_win, 3, 1L<<1, on_key_release, NULL);
    mlx_loop_hook(g_mlx, update_loop, &frame);
    mlx_loop(g_mlx);

}

