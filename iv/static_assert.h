#ifndef IV_STATICASSERT_H_
#define IV_STATICASSERT_H_
namespace iv {
namespace detail {
template<bool b>
struct StaticAssertFailure;

template<>
struct StaticAssertFailure<true> {
  enum {
    value = 1
  };
};

template<int x>
struct StaticAssertTest {
};

} }  // namespace iv::detail

#ifndef IV_CONCAT
#define IV_CONCAT1(x, y) x##y
#define IV_CONCAT(x, y) IV_CONCAT1(x, y)
#endif  // IV_CONCAT
#define IV_STATIC_ASSERT(cond)\
  typedef ::iv::detail::StaticAssertTest\
    <sizeof(::iv::detail::StaticAssertFailure<static_cast<bool>((cond))>)>\
    IV_CONCAT(StaticAssertTypedef, __LINE__)

#endif  // IV_STATICASSERT_H_