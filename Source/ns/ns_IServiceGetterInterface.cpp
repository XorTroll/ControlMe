#include <ns/ns_IServiceGetterInterface.hpp>
#include <ns/ns_Forward.h>

namespace ns
{
    Result IServiceGetterInterface::GetReadOnlyApplicationControlDataInterface(Out<std::shared_ptr<IReadOnlyApplicationControlDataInterface>> out_intf)
    {
        std::shared_ptr<IReadOnlyApplicationControlDataInterface> intf = nullptr;
        u32 out_domain_id = 0;
        Result rc = ResultSuccess;

        ON_SCOPE_EXIT
        {
            if(R_SUCCEEDED(rc))
            {
                out_intf.SetValue(std::move(intf));
                if(out_intf.IsDomain()) out_intf.ChangeObjectId(out_domain_id);
            }
        };

        Service s;
        rc = nsGetReadOnlyApplicationControlDataInterface_Fwd(this->forward_service.get(), &s);
        if(R_SUCCEEDED(rc))
        {
            intf = std::make_shared<IReadOnlyApplicationControlDataInterface>(this->title_id, this->process_id, s);
            if(out_intf.IsDomain()) out_domain_id = s.object_id;
        }
        return rc;
    }
}