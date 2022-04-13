#ifndef __WADL_H__
#define __WADL_H__
#include <string>
#include <cstdint>
#include <unordered_map>
#include <mutex>

namespace sep
{
    class WADL
    {
    public:
        // rule of 5
        WADL(WADL &other) = delete;             // clonable
        void operator=(const WADL &) = delete;  // assignable
        static WADL* getInstance(const std::string& wadl_path);
        uint16_t getAccess (const std::string& uri);

    protected:
        WADL(const std::string& wadl_path);
        ~WADL() noexcept;

    private:
        std::unordered_map<std::string, uint16_t> wadl_;

    private:
    private:
        // thread-safe singleton instance
        static WADL *instance_;
        static std::mutex mutex_;
    };
} // namespace sep

#endif // __WADL_H__