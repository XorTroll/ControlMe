 
#pragma once
#include <switch.h>
#include <stratosphere.hpp>

namespace ns
{
    class IReadOnlyApplicationControlDataInterface final : public IServiceObject
    {
        private:

            u64 title_id;
            u64 process_id;
            std::unique_ptr<Service> srv;

        public:

            IReadOnlyApplicationControlDataInterface(sts::ncm::TitleId tid, u64 pid, Service *s) : title_id(tid), process_id(pid), srv(s)
            {
            }

            IReadOnlyApplicationControlDataInterface(sts::ncm::TitleId tid, u64 pid, std::unique_ptr<Service> s) : title_id(tid), process_id(pid), srv(std::move(s))
            {
            }

            IReadOnlyApplicationControlDataInterface(sts::ncm::TitleId tid, u64 pid, Service s) : title_id(tid), process_id(pid)
            {
			    srv = std::make_unique<Service>(s);
            }

            virtual ~IReadOnlyApplicationControlDataInterface()
            {
                serviceClose(srv.get());
            }

        private:

            enum class CommandId : u32
            {
                GetApplicationControlData = 0,
                GetApplicationDesiredLanguage = 1,
	            ConvertApplicationLanguageToLanguageCode = 2,
	            ConvertLanguageCodeToApplicationLanguage = 3,
            };

            Result GetApplicationControlData(u8 flag, u64 tid, OutBuffer<char> control, Out<u64> out_count);
            Result GetApplicationDesiredLanguage(u32 bitmask, Out<u8> out_langentry);
            Result ConvertApplicationLanguageToLanguageCode(u8 langentry, Out<u64> langcode);
            Result ConvertLanguageCodeToApplicationLanguage(u64 langcode, Out<u8> langentry);

        public:
        
            DEFINE_SERVICE_DISPATCH_TABLE
            {
                MAKE_SERVICE_COMMAND_META(IReadOnlyApplicationControlDataInterface, GetApplicationControlData),
                MAKE_SERVICE_COMMAND_META(IReadOnlyApplicationControlDataInterface, GetApplicationDesiredLanguage),
                MAKE_SERVICE_COMMAND_META(IReadOnlyApplicationControlDataInterface, ConvertApplicationLanguageToLanguageCode),
                MAKE_SERVICE_COMMAND_META(IReadOnlyApplicationControlDataInterface, ConvertLanguageCodeToApplicationLanguage),
            };
    };
}