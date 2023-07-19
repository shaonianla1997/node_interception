#include <napi.h>
#include "interception.h"

#include <Windows.h>

#pragma comment(lib, "../interception.lib");

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
    InterceptionMouseStroke mouseStroke[3];

    ZeroMemory(mouseStroke, sizeof(mouseStroke));
    mouseStroke[0].flags = INTERCEPTION_MOUSE_MOVE_RELATIVE;
    mouseStroke[0].x = point.x;
    mouseStroke[0].y = point.y;
    interception_send(context, INTERCEPTION_MOUSE(0), (InterceptionStroke *)mouseStroke, sizeof(mouseStroke) / sizeof(InterceptionMouseStroke));
    interception_destroy_context(context);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(Napi::String::New(env, "moveMouseRelative"), Napi::Function::New(env, moveMouseRelative));
    return exports;
}

NODE_API_MODULE(node_interception, Init);