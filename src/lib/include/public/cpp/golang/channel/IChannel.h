#if defined(_MSC_VER) || (defined(__BORLANDC__) && __BORLANDC__ >= 0x0650) ||  \
    (defined(__COMO__) && __COMO_VERSION__ >= 400) /* ??? */                   \
    || (defined(__DMC__) && __DMC__ >= 0x700)      /* ??? */                   \
    || (defined(__clang__) && __clang_major__ >= 3) ||                         \
    (defined(__GNUC__) &&                                                      \
     (__GNUC__ >= 4 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)))
#pragma once
#endif

#ifndef D0A9C4E8_3697_4ACB_9E90_05DA7B39548F
#define D0A9C4E8_3697_4ACB_9E90_05DA7B39548F

#include <iterator>
#include <memory>

#include <cpp/golang/channel/ChannelBuffer.h>

namespace go {

class Case;

template <typename T, std::size_t Buffer_Size> class OChan;

// Inspired by
// http://h-deb.clg.qc.ca/Sujets/Divers--cplusplus/Iterateurs-generateurs.html
// From Patrice Roy References: https://golang.org/ref/spec#For_statements To be
// improved...
template <typename T, std::size_t Buffer_Size = 0>
class IChan_Iterator : public std::iterator<std::input_iterator_tag,
                                            T> //:public std::shared_ptr<T>
{
  std::shared_ptr<internal::ChannelBuffer<T, Buffer_Size>> m_buffer;
  T val;

public:
  IChan_Iterator(
      std::shared_ptr<internal::ChannelBuffer<T, Buffer_Size>> buffer,
      bool isEnd = false)
      : m_buffer(buffer) {
    if (!isEnd)
      operator++();
  }

  IChan_Iterator(const IChan_Iterator &) = default;

  T &operator*() { return val; }

  IChan_Iterator &operator++() {
    // static_cast<std::shared_ptr<T>>(*this) =
    // std::make_shared<T>(m_buffer->getNextValue());
    val = m_buffer->getNextValue();
    return *this;
  }

  IChan_Iterator operator++(int) {
    IChan_Iterator tmp(*this); // copy
    operator++();              // pre-increment
    return tmp;                // return old value
  }

  inline bool operator==(const IChan_Iterator &rhs) const {
    return m_buffer->isClosed();
  }

  inline bool operator!=(const IChan_Iterator &rhs) const {
    return !operator==(rhs);
  }
};

template <typename T, std::size_t Buffer_Size = 0>
class IChan //: private Chan<T>
{
protected:
  std::shared_ptr<internal::ChannelBuffer<T, Buffer_Size>> m_buffer;
  IChan(std::shared_ptr<internal::ChannelBuffer<T, Buffer_Size>> buffer)
      : m_buffer(buffer) {}

public:
  IChan() = default;
  IChan(const IChan<T, Buffer_Size> &ch) = default; //:m_buffer(ch.m_buffer) {}
  IChan(IChan<T, Buffer_Size> &&ch) { swap(m_buffer, ch.m_buffer); };

  // Extract from channel
  friend IChan<T, Buffer_Size> &operator>>(IChan<T, Buffer_Size> &ch, T &obj) {
    obj = ch.m_buffer->getNextValue();
    return ch;
  }

  friend IChan<T, Buffer_Size> &operator<<(T &obj, IChan<T, Buffer_Size> &ch) {
    obj = ch.m_buffer->getNextValue();
    return ch;
  }

  template <std::size_t OBuffer_Size>
  friend IChan<T, Buffer_Size> &operator>>(IChan<T, Buffer_Size> &ch,
                                           OChan<T, OBuffer_Size> &obj) {
    T temp;
    ch >> temp;
    obj << temp;
    return ch;
  }

  template <std::size_t OBuffer_Size>
  friend IChan<T, Buffer_Size> &operator<<(OChan<T, OBuffer_Size> &obj,
                                           IChan<T, Buffer_Size> &ch) {
    T temp;
    ch >> temp;
    obj << temp;
    return ch;
  }

  // Stream
  friend std::istream &operator>>(std::istream &is, IChan<T, Buffer_Size> &ch) {
    T temp;
    is >> temp;
    ch << temp;
    return is;
  }

  using IChan_EndIterator = IChan_Iterator<T, Buffer_Size>;

  IChan_Iterator<T, Buffer_Size> begin() {
    return IChan_Iterator<T, Buffer_Size>{m_buffer};
  }

  IChan_EndIterator end() { return {m_buffer, true}; }

  friend class go::Case;
};

} // namespace go

#endif /* D0A9C4E8_3697_4ACB_9E90_05DA7B39548F */
