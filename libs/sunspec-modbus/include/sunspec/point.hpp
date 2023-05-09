#ifndef __POINT_H__
#define __POINT_H__
#include <cstdint>
#include <string>

namespace sunspec
{
    namespace point
    {
        enum class Access : uint8_t
        {
            kRead,
            kReadWrite
        };

        enum class Category : uint8_t
        {
            kNone,
            kMeasurement,
            kMetered,
            kStatus,
            kEvent,
            kSetting,
            kControl
        };

        template <typename T>
        class Point
        {
        public:
            virtual ~Point();
            void Print();
            virtual T GetValue() = 0;
            virtual void SetValue(T value);

        private:
            std::string id;
            uint8_t len;
            uint16_t offset;
            T value;
            std::string sf;
            std::string units;
            Access access;
            bool mandatory;
            Category category;
        };
    } // namespace point

} // namespace sunspec

#endif // __POINT_H__