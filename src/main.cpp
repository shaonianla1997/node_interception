#include <napi.h>
#include "interception.h"
#include "types.h"

#include <Windows.h>

#pragma comment(lib, "../interception.lib");

// The width of the virtual screen, in pixels.
static int vscreenWidth = -1; // not initialized

// The height of the virtual screen, in pixels.
static int vscreenHeight = -1; // not initialized

// The coordinates for the left side of the virtual screen.
static int vscreenMinX = 0;

// The coordinates for the top of the virtual screen.
static int vscreenMinY = 0;

void updateScreenMetrics()
{
    vscreenWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    vscreenHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    vscreenMinX = GetSystemMetrics(SM_XVIRTUALSCREEN);
    vscreenMinY = GetSystemMetrics(SM_YVIRTUALSCREEN);
}

// x y screen postion
Napi::Value moveMouse(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 2)
    {
        napi_throw_error(env, "BadParameter", "Two parameters are required");
        return Napi::Boolean::New(env, false);
    }
    int32_t _x = info[0].As<Napi::Number>().Int32Value();
    int32_t _y = info[1].As<Napi::Number>().Int32Value();

    if (vscreenWidth < 0 || vscreenHeight < 0)
        updateScreenMetrics();

#define MOUSE_COORD_TO_ABS(coord, width_or_height) ((65536 * (coord) / width_or_height) + ((coord) < 0 ? -1 : 1))
    size_t x = MOUSE_COORD_TO_ABS(_x - vscreenMinX, vscreenWidth);
    size_t y = MOUSE_COORD_TO_ABS(_y - vscreenMinY, vscreenHeight);

    InterceptionContext context = interception_create_context();
    InterceptionMouseStroke mouseStroke[1];

    ZeroMemory(mouseStroke, sizeof(mouseStroke));
    mouseStroke[0].flags = INTERCEPTION_MOUSE_MOVE_ABSOLUTE;
    mouseStroke[0].x = x;
    mouseStroke[0].y = y;
    interception_send(context, INTERCEPTION_MOUSE(0), (InterceptionStroke *)mouseStroke, sizeof(mouseStroke) / sizeof(InterceptionMouseStroke));
    interception_destroy_context(context);
    return Napi::Number::New(env, 0);
}

//  x <0 move left  x > 0 move right y<0 move up y>0 move down
Napi::Value moveMouseRelative(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 2)
    {
        napi_throw_error(env, "BadParameter", "Two parameters are required");
        return Napi::Boolean::New(env, false);
    }
    int32_t x = info[0].As<Napi::Number>().Int32Value();
    int32_t y = info[1].As<Napi::Number>().Int32Value();
    MMSignedPoint point;
    point = MMSignedPointMake(x, y);

    InterceptionContext context = interception_create_context();
    InterceptionMouseStroke mouseStroke[1];

    ZeroMemory(mouseStroke, sizeof(mouseStroke));
    mouseStroke[0].flags = INTERCEPTION_MOUSE_MOVE_RELATIVE;
    mouseStroke[0].x = point.x;
    mouseStroke[0].y = point.y;
    interception_send(context, INTERCEPTION_MOUSE(0), (InterceptionStroke *)mouseStroke, sizeof(mouseStroke) / sizeof(InterceptionMouseStroke));
    interception_destroy_context(context);
    return Napi::Number::New(env, 0);
}
int CheckMouseButton(int b, InterceptionMouseState *const stateDown, InterceptionMouseState *const stateUp)
{
    if (!stateDown || !stateUp)
        return -1;

    if (b == 0)
    {
        *stateDown = INTERCEPTION_MOUSE_LEFT_BUTTON_DOWN;
        *stateUp = INTERCEPTION_MOUSE_LEFT_BUTTON_UP;
    }
    else if (b == 1)
    {
        *stateDown = INTERCEPTION_MOUSE_RIGHT_BUTTON_DOWN;
        *stateUp = INTERCEPTION_MOUSE_RIGHT_BUTTON_UP;
    }
    else if (b == 2)
    {
        *stateDown = INTERCEPTION_MOUSE_MIDDLE_BUTTON_DOWN;
        *stateUp = INTERCEPTION_MOUSE_MIDDLE_BUTTON_UP;
    }
    else
    {
        return -2;
    }

    return 0;
}
inline char ToCharVersion(const std::string &str)
{
    return str[0];
}

Napi::Value mouseClick(const Napi::CallbackInfo &info)
{
    InterceptionMouseState stateDown = INTERCEPTION_MOUSE_LEFT_BUTTON_DOWN;
    InterceptionMouseState stateUp = INTERCEPTION_MOUSE_LEFT_BUTTON_UP;
    bool doubleC = false;
    Napi::Env env = info.Env();
    if (info.Length() > 0)
    {
        int b = info[0].As<Napi::Number>().Int32Value();
        switch (CheckMouseButton(b, &stateDown, &stateUp))
        {
        case -1:
            napi_throw_error(env, "BadParameter", "Null pointer in mouse button code.");
            break;
        case -2:
            napi_throw_error(env, "BadParameter", "Invalid mouse button specified.");
            break;
        default:
            break;
        }
    }

    if (info.Length() == 2)
    {
        doubleC = info[1].As<Napi::Boolean>().Value();
    }
    else if (info.Length() > 2)
    {
        napi_throw_error(env, "BadParameter", "Invalid number of arguments.");
    }
    InterceptionContext context = interception_create_context();
    InterceptionMouseStroke mouseStroke[4];
    ZeroMemory(mouseStroke, sizeof(mouseStroke));
    mouseStroke[0].state = stateDown;
    mouseStroke[1].state = stateUp;
    if (doubleC)
    {
        mouseStroke[2].state = stateDown;
        mouseStroke[3].state = stateUp;
    }
    interception_send(context, INTERCEPTION_MOUSE(0), (InterceptionStroke *)mouseStroke, sizeof(mouseStroke) / sizeof(InterceptionMouseStroke));
    interception_destroy_context(context);
    return Napi::Number::New(env, 0);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(Napi::String::New(env, "moveMouseRelative"), Napi::Function::New(env, moveMouseRelative));
    exports.Set(Napi::String::New(env, "moveMouse"), Napi::Function::New(env, moveMouse));
    exports.Set(Napi::String::New(env, "mouseClick"), Napi::Function::New(env, mouseClick));

    return exports;
}

NODE_API_MODULE(node_interception, Init);