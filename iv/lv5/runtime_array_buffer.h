#ifndef IV_LV5_RUNTIME_ARRAY_BUFFER_H_
#define IV_LV5_RUNTIME_ARRAY_BUFFER_H_
#include <iv/lv5/error_check.h>
#include <iv/lv5/constructor_check.h>
#include <iv/lv5/arguments.h>
#include <iv/lv5/jsval.h>
#include <iv/lv5/error.h>
#include <iv/lv5/jsarray_buffer.h>
namespace iv {
namespace lv5 {
namespace runtime {

// section 15.13.5.1 ArrayBuffer(len)
// section 15.13.5.2.1 new ArrayBuffer(len)
inline JSVal ArrayBufferConstructor(const Arguments& args, Error* e) {
  const uint32_t len = args.At(0).ToUInt32(args.ctx(), IV_LV5_ERROR(e));
  return JSArrayBuffer::New(args.ctx(), len);
}

} } }  // namespace iv::lv5::runtime
#endif  // IV_LV5_RUNTIME_ARRAY_BUFFER_H_
