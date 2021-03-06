#ifndef IV_I18N_NUMBER_FORMAT_H_
#define IV_I18N_NUMBER_FORMAT_H_
#include <string>
#include <cstdlib>
#include <algorithm>
#include <iv/detail/array.h>
#include <iv/platform_math.h>
#include <iv/dtoa.h>
#include <iv/character.h>
#include <iv/i18n_numbering_system.h>
#include <iv/i18n_currency.h>
#include <iv/conversions_digit.h>
#include <iv/ustring.h>
namespace iv {
namespace core {
namespace i18n {

struct NumberFormatPatternSet {
  std::string positive_pattern;
  std::string negative_pattern;
};

struct NumberFormatData {
  const char* name;
  NumberingSystem::Candidates numbering_systems;

  // 0 => DECIMAL
  // 1 => PRECENT
  // 2 => CURRENCY
  NumberFormatPatternSet patterns[3];

  bool AcceptedNumberingSystem(NumberingSystem::Type type) const {
    for (NumberingSystem::Candidates::const_iterator
         it = numbering_systems.begin(),
         last = numbering_systems.end();
         it != last && *it; ++it) {
      if (*it == type) {
        return true;
      }
    }
    return false;
  }
};

namespace number_format_data {

static const NumberFormatData EN = {
  "en",
  { {
      NumberingSystem::LATN
  } },
  { {
      "{number}",
      "-{number}"
    }, {
      "{number}%",
      "-{number}%"
    }, {
      "{currency} {number}",
      "-{currency} {number}"
  } }
};

static const NumberFormatData JA = {
  "ja",
  { {
      NumberingSystem::LATN, NumberingSystem::FULLWIDE
  } },
  { {
      "{number}",
      "-{number}"
    }, {
      "{number}%",
      "-{number}%"
    }, {
      "{currency} {number}",
      "-{currency} {number}"
  } }
};

}  // namespace number_format_data

typedef std::array<const char*, 2> NumberFormatDataNames;
typedef std::array<const NumberFormatData*, 2> NumberFormatDataValues;

static const NumberFormatDataNames kNumberFormatDataNames = { {
  number_format_data::EN.name,
  number_format_data::JA.name
} };

static const NumberFormatDataValues kNumberFormatDataValues = { {
  &number_format_data::EN,
  &number_format_data::JA
} };

class NumberFormat {
 public:
  static const int kUnspecified = -1;

  typedef NumberFormatData Data;

  enum Style {
    DECIMAL = 0,
    PERCENT,
    CURRENCY
  };

  static const NumberFormatDataNames& AvailableLocales() {
    return kNumberFormatDataNames;
  }

  NumberFormat(const Data* data,
               Style style,
               int minimum_significant_digits = kUnspecified,
               int maximum_significant_digits = kUnspecified,
               int minimum_integer_digits = kUnspecified,
               int minimum_fraction_digits = kUnspecified,
               int maximum_fraction_digits = kUnspecified,
               const NumberingSystem::Data* numbering_system = nullptr,
               const Currency::Data* currency = nullptr,
               Currency::Display currency_display = Currency::NAME,
               bool use_grouping = false)
    : data_(data),
      style_(style),
      minimum_significant_digits_(minimum_significant_digits),
      maximum_significant_digits_(maximum_significant_digits),
      minimum_integer_digits_(minimum_integer_digits),
      minimum_fraction_digits_(minimum_fraction_digits),
      maximum_fraction_digits_(maximum_fraction_digits),
      numbering_system_(numbering_system),
      currency_(currency),
      currency_display_(currency_display),
      use_grouping_(use_grouping) {
  }

  static std::string ToPrecision(double x, int max_precision) {
    assert(math::IsFinite(x));
    dtoa::StringDToA builder;
    return builder.BuildPrecision(x, max_precision, 0);
  }

  // section 12.3.2
  static std::string ToRawPrecision(
      double x,
      int min_precision,
      int max_precision) {
    assert(min_precision >= 1 && min_precision <= 21);
    assert(max_precision >= 1 && max_precision <= 21);
    assert(math::IsFinite(x) && x >= 0);

    std::string m = ToPrecision(x, max_precision);
    // Expand exponential.
    m = ExpandExponential(m);
    assert(m.find('e') == std::string::npos);

    const std::size_t period = m.find('.');
    if (period != std::string::npos && max_precision > min_precision) {
      int cut = max_precision - min_precision;
      while (cut > 0 && m[m.size() - 1] == '0') {
        m.erase(m.size() - 1);
        --cut;
      }
      if (m[m.size() - 1] == '.') {
          m.erase(m.size() - 1);
      }
    }
    return m;
  }

  static std::string ToFixed(double x, int frac) {
    assert(math::IsFinite(x));
    if (!(std::fabs(x) < 1e+21)) {
      dtoa::StringDToA builder;
      return builder.Build(x);
    } else {
      dtoa::StringDToA builder;
      return builder.BuildFixed(x, frac, 0);
    }
  }

  static std::string ExpandExponential(const std::string& m) {
    const std::string::size_type dot_pos = m.find('.');
    const std::string::size_type exp_pos = m.find('e');

    std::string before_dot;
    std::string after_dot;
    std::string exp;

    if (dot_pos == std::string::npos) {
      if (exp_pos  == std::string::npos) {
        before_dot = m;
      } else {
        before_dot.assign(m.begin(), m.begin() + exp_pos);
        exp.assign(m.begin() + exp_pos, m.end());
      }
    } else {
      before_dot.assign(m.begin(), m.begin() + dot_pos);
      if (exp_pos == std::string::npos) {
        after_dot.assign(m.begin() + dot_pos + 1, m.end());
      } else {
        after_dot.assign(m.begin() + dot_pos + 1, m.begin() + exp_pos);
        exp.assign(m.begin() + exp_pos, m.end());
      }
    }

    if (exp.empty()) {
      return m;
    }

    const int e = std::atoi(exp.c_str() + 1);
    if (exp[0] == '-') {
      return "0." + std::string(e - 1, '0') + before_dot + after_dot;
    } else {
      return before_dot + after_dot + std::string(e - after_dot.size(), '0');
    }
  }

  // section 12.3.2
  static std::string ToRawFixed(
      double x,
      int minimum_integer_digits,
      int minimum_fraction_digits,
      int maximum_fraction_digits) {
    assert(minimum_integer_digits >= 1 && minimum_integer_digits <= 21);
    assert(minimum_fraction_digits >= 0 && minimum_fraction_digits <= 21);
    assert(maximum_fraction_digits >= 0 && maximum_fraction_digits <= 21);
    assert(math::IsFinite(x) && x >= 0);

    std::string m = ToFixed(x, maximum_fraction_digits);

    // Expand exponential and add trailing zeros.
    // We must ensure digits after dot exactly equals to max_fraction_digits.
    // So If it is less, we should append trailing zeros.
    m = ExpandExponential(m);
    assert(m.find('e') == std::string::npos);

    if (m.find('.') == std::string::npos) {
      m.push_back('.');
      m.append(std::string(maximum_fraction_digits, '0'));
    }

    assert(static_cast<int>(m.size() - m.find('.') - 1)
           == maximum_fraction_digits);

    const int i = m.find('.');
    int cut = maximum_fraction_digits - minimum_fraction_digits;
    while (cut > 0 && m[m.size() - 1] == '0') {
      m.erase(m.size() - 1);
      --cut;
    }
    if (m[m.size() - 1] == '.') {
        m.erase(m.size() - 1);
    }
    if (i < minimum_integer_digits) {
      const std::string zero(minimum_integer_digits - i, '0');
      m = zero + m;
    }
    return m;
  }

  // section 12.3.2 Intl.NumberFormat.prototype.format(value)
  std::u16string Format(double x) const {
    bool negative = false;
    std::u16string n;
    if (!math::IsFinite(x)) {
      if (math::IsNaN(x)) {
        n = ToU16String("NaN");
      } else {
        // infinity mark
        n = ToU16String(0x221e);
        if (x < 0) {
          negative = true;
        }
      }
    } else {
      if (x < 0) {
        negative = true;
        x = -x;
      }

      if (style_ == PERCENT) {
        x *= 100;
      }

      if (minimum_significant_digits_ != kUnspecified &&
          maximum_significant_digits_ != kUnspecified) {
        n = ToU16String(
            ToRawPrecision(x,
                           minimum_significant_digits_,
                           maximum_significant_digits_));
      } else {
        n = ToU16String(
            ToRawFixed(x,
                       minimum_integer_digits_,
                       minimum_fraction_digits_,
                       maximum_fraction_digits_));
      }

      // Conversion of numbers by Numbering System
      // This is ILND
      // section 12.3.2-5-e
      if (numbering_system() &&
          numbering_system() !=
            NumberingSystem::Lookup(NumberingSystem::LATN)) {
        for (std::u16string::iterator it = n.begin(), last = n.end();
             it != last; ++it) {
          const char16_t ch = *it;
          if (character::IsDecimalDigit(ch)) {
            *it = numbering_system()->mapping[DecimalValue(ch)];
          }
        }
      }

      // section 12.3.2-5-f
      // period conversion
      // This is ILND. So we can use simple '.'.

      if (use_grouping()) {
        using std::swap;
        std::u16string temp;
        temp.reserve(n.size());
        std::u16string::size_type p = n.rfind('.');
        if (p != std::u16string::npos) {
          p = n.size() - p;
          temp.append(n.rbegin(), n.rbegin() + p);
        } else {
          p = 0;
        }
        uint32_t count = 0;
        std::u16string::const_reverse_iterator it = n.rbegin() + p;
        const std::u16string::const_reverse_iterator last = n.rend();
        while (it != last) {
          temp.push_back(*it);
          ++it;
          ++count;
          if (count % 3 == 0) {
            if (it != last) {
              temp.push_back(',');
            }
            count = 0;
          }
        }
        n.assign(temp.rbegin(), temp.rend());
      }
    }

    std::string pattern;
    if (negative) {
      pattern = data_->patterns[style_].negative_pattern;
    } else {
      pattern = data_->patterns[style_].positive_pattern;
    }

    const std::size_t i = pattern.find("{number}");
    assert(i != std::string::npos);
    std::u16string result(pattern.begin(), pattern.begin() + i);
    result.append(n);
    result.append(pattern.begin() + i + std::strlen("{number}"), pattern.end());

    if (style_ == CURRENCY && currency()) {
      const std::size_t i = result.find(ToU16String("{currency}"));
      assert(i != std::u16string::npos);
      std::u16string currency_result(result.begin(), result.begin() + i);
      if (currency_display() == Currency::SYMBOL &&
          currency()->symbol.size != 0) {
        currency_result.append(currency()->symbol.data,
                               currency()->symbol.size);
      } else if (currency_display() == Currency::NAME &&
                 currency()->name) {
        currency_result.append(
            currency()->name,
            currency()->name + std::strlen(currency()->name));
      } else {
        currency_result.append(
            currency()->code,
            currency()->code + std::strlen(currency()->code));
      }
      currency_result.append(
          result.begin() + i + std::strlen("{currency}"), result.end());
      return currency_result;
    } else {
      return result;
    }
  }

  typedef std::unordered_map<std::string, const Data*> NumberFormatDataMap;

  static const Data* Lookup(string_view name) {
    const NumberFormatDataMap::const_iterator it = Map().find(name);
    if (it != Map().end()) {
      return it->second;
    }
    return nullptr;
  }

 private:
  static const NumberFormatDataMap& Map() {
    static const NumberFormatDataMap map = InitMap();
    return map;
  }

  static NumberFormatDataMap InitMap() {
    NumberFormatDataMap map;
    for (NumberFormatDataValues::const_iterator it = kNumberFormatDataValues.begin(),  // NOLINT
         last = kNumberFormatDataValues.end();
         it != last; ++it) {
      map.insert(std::make_pair((*it)->name, *it));
    }
    return map;
  }

 public:
  Style style() const { return style_; }
  int minimum_significant_digits() const { return minimum_significant_digits_; }
  int maximum_significant_digits() const { return maximum_significant_digits_; }
  int minimum_integer_digits() const { return minimum_integer_digits_; }
  int minimum_fraction_digits() const { return minimum_fraction_digits_; }
  int maximum_fraction_digits() const { return maximum_fraction_digits_; }
  const NumberingSystem::Data* numbering_system() const {
    return numbering_system_;
  }
  const Data* data() const { return data_; }
  const Currency::Data* currency() const { return currency_; }
  Currency::Display currency_display() const { return currency_display_; }
  bool use_grouping() const { return use_grouping_; }

 private:
  const Data* data_;
  Style style_;
  int minimum_significant_digits_;
  int maximum_significant_digits_;
  int minimum_integer_digits_;
  int minimum_fraction_digits_;
  int maximum_fraction_digits_;
  const NumberingSystem::Data* numbering_system_;
  const Currency::Data* currency_;
  Currency::Display currency_display_;
  bool use_grouping_;
};

} } }  // namespace iv::core::i18n
#endif  // IV_I18N_NUMBER_FORMAT_H_
