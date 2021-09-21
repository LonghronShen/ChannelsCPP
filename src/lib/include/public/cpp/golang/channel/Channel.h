#if defined(_MSC_VER) || (defined(__BORLANDC__) && __BORLANDC__ >= 0x0650) ||  \
    (defined(__COMO__) && __COMO_VERSION__ >= 400) /* ??? */                   \
    || (defined(__DMC__) && __DMC__ >= 0x700)      /* ??? */                   \
    || (defined(__clang__) && __clang_major__ >= 3) ||                         \
    (defined(__GNUC__) &&                                                      \
     (__GNUC__ >= 4 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)))
#pragma once
#endif

#ifndef B5D7FDC5_851F_4965_8C11_A2662FCB2760
#define B5D7FDC5_851F_4965_8C11_A2662FCB2760

#include <atomic>
#include <condition_variable>
#include <deque>
#include <limits>
#include <memory>
#include <mutex>
#include <queue>

#include <cpp/golang/channel/ChannelBuffer.h>
#include <cpp/golang/channel/ChannelUtility.h>
#include <cpp/golang/channel/Circular_buffer.h>
#include <cpp/golang/channel/IChannel.h>
#include <cpp/golang/channel/OChannel.h>

namespace go {

// Channel Type references: https://golang.org/ref/spec#Channel_types
template <typename T, std::size_t Buffer_Size = 1>
class Chan : public IChan<T, Buffer_Size>, public OChan<T, Buffer_Size> {
public:
  Chan() {
    Chan::IChan::m_buffer = Chan::OChan::m_buffer =
        std::make_shared<internal::ChannelBuffer<T, Buffer_Size>>();
    // IChan<T, Buffer_Size>::m_buffer = OChan<T, Buffer_Size>::m_buffer =
    // std::make_shared<internal::ChannelBuffer<T, Buffer_Size>>();
  }

  ~Chan() = default;

  // Insert in channel
  friend OChan<T, Buffer_Size> &operator<<(Chan<T, Buffer_Size> &ch,
                                           const T &obj) {
    return static_cast<OChan<T, Buffer_Size> &>(ch) << obj;
    /*ch.m_buffer->insertValue(obj);
    return ch;*/
  }

  friend OChan<T, Buffer_Size> &operator>>(const T &obj,
                                           Chan<T, Buffer_Size> &ch) {
    return static_cast<OChan<T, Buffer_Size> &>(ch) << obj;

    /*ch.m_buffer->insertValue(obj);
    return  ch;*/
  }

  // Stream
  friend std::ostream &operator<<(std::ostream &os, Chan<T, Buffer_Size> &ch) {
    return os << static_cast<OChan<T, Buffer_Size> &>(ch);
  }

  friend std::istream &operator>>(std::istream &is, Chan<T, Buffer_Size> &ch) {
    return is >> static_cast<IChan<T, Buffer_Size> &>(ch);
  }
};

} // namespace go

#endif /* B5D7FDC5_851F_4965_8C11_A2662FCB2760 */
