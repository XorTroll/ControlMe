
#pragma once
#include <switch.h>
#include <stratosphere.hpp>
#include <ns/ns_IReadOnlyApplicationControlDataInterface.hpp>

namespace ns
{
    class IServiceGetterInterface final : public IMitmServiceObject
    {
        public:

            IServiceGetterInterface(std::shared_ptr<Service> s, u64 pid, sts::ncm::TitleId tid) : IMitmServiceObject(s, pid, tid)
            {
            }

            static bool ShouldMitm(u64 pid, sts::ncm::TitleId tid)
            {
                return true;
            }

            static void PostProcess(IMitmServiceObject *obj, IpcResponseContext *ctx)
            {
            }

        private:

            enum class CommandId : u32
            {
                GetReadOnlyApplicationControlDataInterface = 7989
            };

            Result GetReadOnlyApplicationControlDataInterface(Out<std::shared_ptr<IReadOnlyApplicationControlDataInterface>> out_intf);

        public:
        
            DEFINE_SERVICE_DISPATCH_TABLE
            {
                MAKE_SERVICE_COMMAND_META(IServiceGetterInterface, GetReadOnlyApplicationControlDataInterface),
            };
    };
}