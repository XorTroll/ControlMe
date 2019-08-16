#include <duk/duk_ControlContext.hpp>

namespace duk
{
    duk_context *CreateControlContext(NsApplicationControlData *control)
    {
        u8 *controlbuf = (u8*)control;
        auto ctx = duk_create_heap_default();
        auto ctx_control = duk_push_object(ctx);
        duk_push_string(ctx, control->nacp.version);
        duk_put_prop_string(ctx, ctx_control, "version");
        auto ctx_control_entries = duk_push_array(ctx);
        for(u32 i = 0; i < 0x10; i++)
        {
            auto ctx_control_entries_i = duk_push_object(ctx);
            char *name = control->nacp.lang[i].name;
            if(name[0] != 0) duk_push_string(ctx, name);
            else duk_push_null(ctx);
            duk_put_prop_string(ctx, ctx_control_entries_i, "name");
            char *author = control->nacp.lang[i].author;
            if(author[0] != 0) duk_push_string(ctx, author);
            else duk_push_null(ctx);
            duk_put_prop_string(ctx, ctx_control_entries_i, "author");
            duk_put_prop_index(ctx, ctx_control_entries, i);
        }
        duk_put_prop_string(ctx, ctx_control, "entries");
        duk_push_uint(ctx, (u8)controlbuf[0x3025]);
        duk_put_prop_string(ctx, ctx_control, "startupUserAccount");
        duk_put_global_string(ctx, "control");
        return ctx;
    }

    void ProcessCodeChangesToControl(duk_context *ctx, NsApplicationControlData *control)
    {
        u8 *controlbuf = (u8*)control;
        duk_get_global_string(ctx, "control");
        duk_get_prop_string(ctx, -1, "version");
        const char *version = duk_get_string(ctx, -1);
        strcpy(control->nacp.version, version);
        duk_pop(ctx);
        duk_get_prop_string(ctx, -1, "startupUserAccount");
        duk_uint_t startup_user_acc = duk_get_uint(ctx, -1);
        controlbuf[0x3025] = startup_user_acc;
        duk_pop(ctx);
        duk_get_prop_string(ctx, -1, "entries");
        for(u32 i = 0; i < 0x10; i++)
        {
            duk_get_prop_index(ctx, -1, i);

            duk_get_prop_string(ctx, -1, "name");
            if(duk_is_string(ctx, -1))
            {
                const char *name = duk_get_string(ctx, -1);
                strcpy(control->nacp.lang[i].name, name);
            }
            duk_pop(ctx);

            duk_get_prop_string(ctx, -1, "author");
            if(duk_is_string(ctx, -1))
            {
                const char *author = duk_get_string(ctx, -1);
                strcpy(control->nacp.lang[i].author, author);
            }
            duk_pop(ctx);

            duk_pop(ctx);
        }
        duk_pop(ctx);
    }

    void DisposeControlContext(duk_context *ctx)
    {
        duk_destroy_heap(ctx);
    }
}