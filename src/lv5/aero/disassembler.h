#ifndef IV_LV5_AERO_DISASSEMBLER_H_
#define IV_LV5_AERO_DISASSEMBLER_H_
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdio>
#include "detail/array.h"
#include "detail/cstdint.h"
#include "noncopyable.h"
#include "stringpiece.h"
#include "lv5/aero/op.h"
#include "lv5/aero/utility.h"
namespace iv {
namespace lv5 {
namespace aero {

template<typename Derived>
class DisAssembler : private core::Noncopyable<> {
 public:
  void DisAssemble(const std::vector<uint8_t>& code) {
    {
      // code description
      std::ostringstream ss;
      ss << "[regexp] captures: ";
      OutputLine(ss.str());
    }
    std::vector<char> line;
    int index = 0;
    std::array<char, 30> buf;
    for (std::vector<uint8_t>::const_iterator it = code.begin(),
         last = code.end(); it != last;) {
      const uint8_t opcode = *it;
      uint32_t length = kOPLength[opcode];
      if (opcode == OP::CHECK_RANGE || opcode == OP::CHECK_RANGE_INVERTED) {
        length += Load4Bytes(it + 1);
      }
      const int len = snprintf(buf.data(), buf.size(), "%05d: ", index);
      line.insert(line.end(), buf.data(), buf.data() + len);
      const core::StringPiece piece(OP::String(opcode));
      line.insert(line.end(), piece.begin(), piece.end());
      for (uint32_t first = 1; first < length; ++first) {
        line.push_back(' ');
        std::string val = core::DoubleToStringWithRadix(*(it + first), 10);
        line.insert(line.end(), val.begin(), val.end());
      }
      OutputLine(core::StringPiece(line.data(), line.size()));
      line.clear();
      std::advance(it, length);
      index += length;
    }
  }

 private:
  void OutputLine(const core::StringPiece& str) {
    static_cast<Derived*>(this)->OutputLine(str);
  }
};

class OutputDisAssembler : public DisAssembler<OutputDisAssembler> {
 public:
  OutputDisAssembler(FILE* file) : file_(file) { }

  void OutputLine(const core::StringPiece& str) {
    const std::size_t rv = std::fwrite(str.data(), 1, str.size(), file_);
    if (rv == str.size()) {
      std::fputc('\n', file_);
    }
  }

 private:
  FILE* file_;
};

} } }  // namespace iv::lv5::aero
#endif  // IV_LV5_AERO_DISASSEMBLER_H_