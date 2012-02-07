#ifndef IV_LV5_RAILGUN_FRAME_H_
#define IV_LV5_RAILGUN_FRAME_H_
#include <cstddef>
#include <iterator>
#include <iv/utils.h>
#include <iv/static_assert.h>
#include <iv/lv5/jsval.h>
#include <iv/lv5/railgun/fwd.h>
#include <iv/lv5/railgun/code.h>
namespace iv {
namespace lv5 {
namespace railgun {

//
// Frame structure is following
//
// ARG2 | ARG1 | THIS | FRAME | REGISTERS | STACK
//
struct Frame {
  static const int kThisOffset = 1;
  static const int kArgumentsOffset = 2;

  typedef JSVal* iterator;
  typedef const JSVal* const_iterator;

  typedef std::iterator_traits<iterator>::value_type value_type;

  typedef std::iterator_traits<iterator>::pointer pointer;
  typedef std::iterator_traits<const_iterator>::pointer const_pointer;
  typedef std::iterator_traits<iterator>::reference reference;
  typedef std::iterator_traits<const_iterator>::reference const_reference;

  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  typedef std::iterator_traits<iterator>::difference_type difference_type;
  typedef std::size_t size_type;

  JSVal* GetFrameEnd() {
    return GetFrameBase() + GetFrameSize(code_->after_frame_size());
  }

  JSVal* RegisterFile() {
    return GetFrameBase() + GetFrameSize(0);
  }

  JSVal* GetFrameBase() {
    return reinterpret_cast<JSVal*>(this);
  }

  const JSVal* GetFrameBase() const {
    return reinterpret_cast<const JSVal*>(this);
  }

  bool IsGlobalFrame() const {
    return prev_ == NULL;
  }

  JSVal GetThis() const {
    return *(reinterpret_cast<const JSVal*>(this) - kThisOffset);
  }

  void set_this_binding(JSVal val) {
    *(reinterpret_cast<JSVal*>(this) - kThisOffset) = val;
  }

  typedef reverse_iterator arguments_iterator;
  typedef const_reverse_iterator const_arguments_iterator;
  typedef iterator reverse_arguments_iterator;
  typedef const_iterator const_reverse_arguments_iterator;

  arguments_iterator arguments_begin() {
    return arguments_iterator(
        reinterpret_cast<JSVal*>(this) - kThisOffset);
  }

  const_arguments_iterator arguments_begin() const {
    return const_arguments_iterator(
        reinterpret_cast<const JSVal*>(this) - kThisOffset);
  }

  const_arguments_iterator arguments_cbegin() const {
    return arguments_begin();
  }

  arguments_iterator arguments_end() {
    return arguments_begin() + argc_;
  }

  const_arguments_iterator arguments_end() const {
    return arguments_begin() + argc_;
  }

  const_arguments_iterator arguments_cend() const {
    return arguments_end();
  }

  reverse_arguments_iterator arguments_rbegin() {
    return reverse_arguments_iterator(
        reinterpret_cast<JSVal*>(this) - kThisOffset - argc_);
  }

  const_reverse_arguments_iterator arguments_rbegin() const {
    return const_reverse_arguments_iterator(
        reinterpret_cast<const JSVal*>(this) - kThisOffset - argc_);
  }

  const_reverse_arguments_iterator arguments_crbegin() const {
    return arguments_rbegin();
  }

  reverse_arguments_iterator arguments_rend() {
    return arguments_rbegin() + argc_;
  }

  const_reverse_arguments_iterator arguments_rend() const {
    return arguments_crbegin() + argc_;
  }

  const_reverse_arguments_iterator arguments_crend() const {
    return arguments_rend();
  }

  JSVal GetArg(uint32_t index) const {
    if (index < argc_) {
      return *(reinterpret_cast<const JSVal*>(this) - kArgumentsOffset - index);
    }
    return JSUndefined;
  }

  JSVal GetConstant(uint32_t index) const {
    return code()->constants()[index];
  }

  Symbol GetName(uint32_t index) const {
    return code()->names()[index];
  }

  static std::size_t GetFrameSize(std::size_t n) {
    return n + (IV_ROUNDUP(sizeof(Frame), sizeof(JSVal)) / sizeof(JSVal));
  }

  const Code* code() const { return code_; }

  Instruction* data() { return code_->data(); }

  const Instruction* data() const { return code_->data(); }

  JSEnv* lexical_env() { return lexical_env_; }

  void set_lexical_env(JSEnv* lex) { lexical_env_ = lex; }

  JSEnv* variable_env() { return variable_env_; }

  JSVal callee() const { return callee_; }

  Code* code_;
  Instruction* prev_pc_;
  JSEnv* variable_env_;
  JSEnv* lexical_env_;
  Frame* prev_;
  JSVal callee_;
  uint32_t argc_;
  uint32_t dynamic_env_level_;
  uint32_t registers_;
  int32_t r_;
  bool constructor_call_;
};

} } }  // namespace iv::lv5::railgun
#endif  // IV_LV5_RAILGUN_FRAME_H_
