#include <ns/ns_IReadOnlyApplicationControlDataInterface.hpp>
#include <ns/ns_Forward.h>
#include <duk/duk_ControlContext.hpp>

extern char *jscode;

namespace ns
{
    Result IReadOnlyApplicationControlDataInterface::GetApplicationControlData(u8 flag, u64 tid, OutBuffer<char> control, Out<u64> out_count)
    {
        R_TRY(nsGetApplicationControlData_Fwd(this->srv.get(), flag, tid, control.buffer, control.num_elements, out_count.GetPointer()));

        if(control.num_elements == sizeof(NsApplicationControlData)) // Anything else would not make sense...?
        {
            if(jscode != NULL)
            {
                auto ctx = duk::CreateControlContext((NsApplicationControlData*)control.buffer);
                if(duk_peval_string(ctx, jscode) == 0) duk::ProcessCodeChangesToControl(ctx, (NsApplicationControlData*)control.buffer);
                duk::DisposeControlContext(ctx);
            }
        }
        
        return ResultSuccess;
    }

    Result IReadOnlyApplicationControlDataInterface::GetApplicationDesiredLanguage(u32 bitmask, Out<u8> out_langentry)
    {
        return nsGetApplicationDesiredLanguage_Fwd(this->srv.get(), bitmask, out_langentry.GetPointer());
    }

    Result IReadOnlyApplicationControlDataInterface::ConvertApplicationLanguageToLanguageCode(u8 langentry, Out<u64> langcode)
    {
        return nsConvertApplicationLanguageToLanguageCode_Fwd(this->srv.get(), langentry, langcode.GetPointer());
    }

    Result IReadOnlyApplicationControlDataInterface::ConvertLanguageCodeToApplicationLanguage(u64 langcode, Out<u8> langentry)
    {
        return nsConvertLanguageCodeToApplicationLanguage_Fwd(this->srv.get(), langcode, langentry.GetPointer());
    }
}