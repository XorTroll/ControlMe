
#pragma once
#include <duk/duktape.h>
#include <switch.h>

namespace duk
{
    duk_context *CreateControlContext(NsApplicationControlData *control);
    void ProcessCodeChangesToControl(duk_context *ctx, NsApplicationControlData *control);
    void DisposeControlContext(duk_context *ctx);
}