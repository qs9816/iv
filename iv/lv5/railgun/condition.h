// analyze condition value
//
// condition value is
//   TRUE / FALSE / INDETERMINATE
//
#ifndef IV_LV5_RAILGUN_CONDITION_H_
#define IV_LV5_RAILGUN_CONDITION_H_
#include <iv/lv5/specialized_ast.h>
#include <iv/lv5/railgun/fwd.h>
namespace iv {
namespace lv5 {
namespace railgun {

class Condition {
 public:
  static bool NoSideEffect(const Expression* expr) {
    const Literal* literal = expr->AsLiteral();
    if (!literal) {
      return false;
    }

    if (literal->AsTrueLiteral()) {
      return true;
    }

    if (literal->AsFalseLiteral()) {
      return true;
    }

    if (literal->AsNullLiteral()) {
      return true;
    }

    if (literal->AsNumberLiteral()) {
      return true;
    }

    if (literal->AsStringLiteral()) {
      return true;
    }

    if (literal->AsFunctionLiteral()) {
      return true;
    }

    // ObjectLiteral and ArrayLiteral have side effect expressions...
    return false;
  }

  enum Type {
    COND_FALSE = 0,
    COND_TRUE = 1,
    COND_INDETERMINATE = 2
  };

  static Type Analyze(const Expression* expr) {
    const Literal* literal = expr->AsLiteral();
    if (!literal) {
      return COND_INDETERMINATE;
    }

    if (literal->AsTrueLiteral()) {
      return COND_TRUE;
    }

    if (literal->AsFalseLiteral()) {
      return COND_FALSE;
    }

    if (const NumberLiteral* num = literal->AsNumberLiteral()) {
      const double val = num->value();
      if (val != 0 && !core::IsNaN(val)) {
        return COND_TRUE;
      } else {
        return COND_FALSE;
      }
    }

    if (const StringLiteral* str = literal->AsStringLiteral()) {
      if (str->value().empty()) {
        return COND_FALSE;
      } else {
        return COND_TRUE;
      }
    }

    if (literal->AsNullLiteral()) {
      return COND_FALSE;
    }

    return COND_INDETERMINATE;
  }
};

} } }  // namespace iv::lv5::railgun
#endif  // IV_LV5_RAILGUN_CONDITION_H_
