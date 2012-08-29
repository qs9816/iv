#ifndef IV_LV5_I18N_NUMBER_FORMAT_H_
#define IV_LV5_I18N_NUMBER_FORMAT_H_
#include <iv/i18n.h>
#include <iv/lv5/jsobject.h>
#include <iv/lv5/bind.h>
#include <iv/lv5/context_fwd.h>
#include <iv/lv5/context_utils.h>
#include <iv/lv5/i18n/utility.h>
namespace iv {
namespace lv5 {
namespace i18n {

class JSNumberFormatHolder : public JSObject {
 public:
  typedef GCHandle<core::i18n::NumberFormat> FormatHandle;

  explicit JSNumberFormatHolder(Context* ctx, JSString* currency)
    : JSObject(Map::NewUniqueMap(ctx)),
      format_(new FormatHandle()),
      currency_(currency),
      bound_(NULL) { }

  static JSNumberFormatHolder* New(Context* ctx,
                                   JSString* currency,
                                   core::i18n::NumberFormat* number_format) {
    JSNumberFormatHolder* const format = new JSNumberFormatHolder(ctx, currency);
    format->set_cls(JSObject::GetClass());
    format->set_prototype(
        context::GetClassSlot(ctx, Class::Object).prototype);
    format->set_format(number_format);
    return format;
  }

  core::i18n::NumberFormat* format() const {
    return format_->handle.get();
  }

  JSVal Format(Context* ctx, double value, Error* e) {
    if (value == 0) {
      // if value is -0, we overwrite it as +0
      value = 0;
    }
    return JSString::New(ctx, format()->Format(value), e);
  }

  JSFunction* Bound(Context* ctx, Error* e);

  JSObject* ResolveOptions(Context* ctx, Error* e) {
    JSObject* obj = JSObject::New(ctx);
    bind::Object object(ctx, obj);

    switch (format()->style()) {
      case core::i18n::NumberFormat::DECIMAL:
        object.def(symbol::style(),
                   JSString::NewAsciiString(ctx, "decimal", e),
                   ATTR::W | ATTR::E | ATTR::C);
        break;

      case core::i18n::NumberFormat::PERCENT:
        object.def(symbol::style(),
                   JSString::NewAsciiString(ctx, "percent", e),
                   ATTR::W | ATTR::E | ATTR::C);
        break;

      case core::i18n::NumberFormat::CURRENCY:
        object.def(symbol::style(),
                   JSString::NewAsciiString(ctx, "currency", e),
                   ATTR::W | ATTR::E | ATTR::C);
        if (currency_) {
          object.def(context::Intern(ctx, "currency"),
                     currency_, ATTR::W | ATTR::E | ATTR::C);
        }
        switch (format()->currency_display()) {
          case core::i18n::Currency::CODE:
            object.def(symbol::style(),
                       JSString::NewAsciiString(ctx, "code", e),
                       ATTR::W | ATTR::E | ATTR::C);
            break;
          case core::i18n::Currency::SYMBOL:
            object.def(symbol::style(),
                       JSString::NewAsciiString(ctx, "symbol", e),
                       ATTR::W | ATTR::E | ATTR::C);
            break;
          case core::i18n::Currency::NAME:
            object.def(symbol::style(),
                       JSString::NewAsciiString(ctx, "name", e),
                       ATTR::W | ATTR::E | ATTR::C);
            break;
        }
        break;
    }

    if (format()->minimum_integer_digits() != core::i18n::NumberFormat::kUnspecified) {
      object.def(context::Intern(ctx, "minimumIntegerDigits"),
                 JSVal::Int32(format()->minimum_integer_digits()),
                 ATTR::W | ATTR::E | ATTR::C);
    }

    if (format()->minimum_fraction_digits() != core::i18n::NumberFormat::kUnspecified) {
      object.def(context::Intern(ctx, "minimumFractionDigits"),
                 JSVal::Int32(format()->minimum_fraction_digits()),
                 ATTR::W | ATTR::E | ATTR::C);
    }

    if (format()->maximum_fraction_digits() != core::i18n::NumberFormat::kUnspecified) {
      object.def(context::Intern(ctx, "maximumFractionDigits"),
                 JSVal::Int32(format()->maximum_fraction_digits()),
                 ATTR::W | ATTR::E | ATTR::C);
    }

    if (format()->minimum_significant_digits() != core::i18n::NumberFormat::kUnspecified) {
      object.def(context::Intern(ctx, "minimumSignificantDigits"),
                 JSVal::Int32(format()->minimum_significant_digits()),
                 ATTR::W | ATTR::E | ATTR::C);
    }

    if (format()->maximum_significant_digits() != core::i18n::NumberFormat::kUnspecified) {
      object.def(context::Intern(ctx, "maximumSignificantDigits"),
                 JSVal::Int32(format()->maximum_significant_digits()),
                 ATTR::W | ATTR::E | ATTR::C);
    }

    object.def(context::Intern(ctx, "useGrouping"),
               JSVal::Bool(format()->use_grouping()),
               ATTR::W | ATTR::E | ATTR::C);

    if (const core::i18n::NumberingSystem::Data* data = format()->numbering_system()) {
      object.def(context::Intern(ctx, "numberingSystem"),
                 JSString::NewAsciiString(ctx, data->name, e),
                 ATTR::W | ATTR::E | ATTR::C);
    }

    if (const core::i18n::NumberFormat::Data* data = format()->data()) {
      object.def(context::Intern(ctx, "locale"),
                 JSString::NewAsciiString(ctx, data->name, e),
                 ATTR::W | ATTR::E | ATTR::C);
    }
    return obj;
  }

 private:
  void set_format(core::i18n::NumberFormat* number_format) {
    format_->handle.reset(number_format);
  }

  FormatHandle* format_;
  JSString* currency_;
  JSFunction* bound_;
};

class JSNumberFormatBoundFunction : public JSFunction {
 public:
  virtual JSVal Call(Arguments* args, JSVal this_binding, Error* e) {
    const double value = args->At(0).ToNumber(args->ctx(), IV_LV5_ERROR(e));
    return format_->Format(args->ctx(), value, e);
  }

  virtual JSVal Construct(Arguments* args, Error* e) {
    e->Report(Error::Type, "Intl.NumberFormat bound function does not have [[Construct]]");
    return JSEmpty;
  }

  virtual bool IsNativeFunction() const { return true; }

  virtual bool IsBoundFunction() const { return false; }

  virtual bool IsStrict() const { return false; }

  virtual JSAPI NativeFunction() const { return NULL; }

  static JSNumberFormatBoundFunction* New(Context* ctx, JSNumberFormatHolder* format) {
    JSNumberFormatBoundFunction* const obj =
        new JSNumberFormatBoundFunction(ctx, format);
    obj->Initialize(ctx);
    return obj;
  }

 private:
  explicit JSNumberFormatBoundFunction(Context* ctx, JSNumberFormatHolder* format)
    : JSFunction(ctx),
      format_(format) {
    Error::Dummy dummy;
    DefineOwnProperty(
        ctx, symbol::length(),
        DataDescriptor(JSVal::UInt32(1u), ATTR::NONE), false, NULL);
    DefineOwnProperty(
        ctx, symbol::name(),
        DataDescriptor(
            JSString::NewAsciiString(ctx, "format", &dummy),
            ATTR::NONE), false, NULL);
  }

  JSNumberFormatHolder* format_;
};

inline JSFunction* JSNumberFormatHolder::Bound(Context* ctx, Error* e) {
  if (bound_) {
    return bound_;
  }
  bound_ = JSNumberFormatBoundFunction::New(ctx, this);
  return bound_;
}

// 10.1.1.1 InitializeNumberFormat(numberFormat, locales, options)
inline JSObject* InitializeNumberFormat(Context* ctx,
                                        JSObject* format,
                                        JSVal locales, JSVal op, Error* e) {
  if (format->HasOwnProperty(ctx, ctx->i18n()->symbols().initializedIntlObject())) {
    e->Report(Error::Type, "object has been already initialized as Intl group object");
    return NULL;
  }

  format->DefineOwnProperty(
      ctx,
      ctx->i18n()->symbols().initializedIntlObject(),
      DataDescriptor(JSTrue, ATTR::N),
      false, IV_LV5_ERROR_WITH(e, NULL));

  JSVector* requested_locales = CanonicalizeLocaleList(ctx, locales, IV_LV5_ERROR_WITH(e, NULL));

  JSObject* o = NULL;
  if (op.IsUndefined()) {
    o = JSObject::New(ctx);
  } else {
    o = op.ToObject(ctx, IV_LV5_ERROR_WITH(e, NULL));
  }

  NumberOptions options(o);
  JSObject* opt = JSObject::New(ctx);

  static const std::array<core::StringPiece, 2> k7 = { {
    "lookup",
    "best fit"
  } };
  JSString* matcher = options.GetString(ctx, symbol::localeMatcher(), k7.begin(), k7.end(), "best fit", IV_LV5_ERROR_WITH(e, NULL));

  opt->DefineOwnProperty(
      ctx,
      symbol::localeMatcher(),
      DataDescriptor(matcher, ATTR::N),
      false, IV_LV5_ERROR_WITH(e, NULL));

  const core::i18n::LookupResult result =
      detail_i18n::ResolveLocale(
          ctx,
          core::i18n::NumberFormat::AvailableLocales().begin(),
          core::i18n::NumberFormat::AvailableLocales().end(),
          requested_locales,
          opt,
          IV_LV5_ERROR_WITH(e, NULL));

  const core::i18n::NumberFormat::Data* locale =
      core::i18n::NumberFormat::Lookup(result.locale());

  // relevantExtensionKeys are ['nu']
  const core::i18n::NumberingSystem::Data* nu = NULL;
  {
    typedef core::i18n::LookupResult::UnicodeExtensions Ext;
    const Ext::const_iterator key =
        std::find(result.extensions().begin(), result.extensions().end(), "nu");
    if (key != result.extensions().end()) {
      const Ext::const_iterator val = key + 1;
      if (val != result.extensions().end() && val->size() > 2) {
        const core::i18n::NumberingSystem::Data* data =
            core::i18n::NumberingSystem::Lookup(*val);
        if (data && locale->AcceptedNumberingSystem(data->type)) {
          nu = data;
        }
      }
    }
  }

  core::i18n::NumberFormat::Style style = core::i18n::NumberFormat::DECIMAL;
  core::i18n::Currency::Display display = core::i18n::Currency::SYMBOL;
  const core::i18n::Currency::Data* currency_data = NULL;
  JSString* c = NULL;
  {
    static const std::array<core::StringPiece, 3> k15 = { {
      "decimal",
      "percent",
      "currency"
    } };
    JSString* s =
        options.GetString(ctx, symbol::style(), k15.begin(), k15.end(), "decimal", IV_LV5_ERROR_WITH(e, NULL));

    if (s->compare("decimal") == 0) {
      style = core::i18n::NumberFormat::DECIMAL;
    } else if (s->compare("percent") == 0) {
      style = core::i18n::NumberFormat::PERCENT;
    } else {
      style = core::i18n::NumberFormat::CURRENCY;
    }

    // currency option
    JSString* currency  =
        options.GetString(ctx, symbol::currency(),
                          static_cast<const char**>(NULL),
                          static_cast<const char**>(NULL), NULL, IV_LV5_ERROR_WITH(e, NULL));
    if (currency) {
      if (!core::i18n::IsWellFormedCurrencyCode(currency->begin(), currency->end())) {
        e->Report(Error::Range, "invalid currency code");
        return NULL;
      }
    } else {
      if (style == core::i18n::NumberFormat::CURRENCY) {
        e->Report(Error::Type, "currency is not specified");
        return NULL;
      }
    }

    if (style == core::i18n::NumberFormat::CURRENCY) {
      JSStringBuilder builder;
      for (JSString::const_iterator it = currency->begin(), last = currency->end();
           it != last; ++it) {
        if (core::character::IsASCII(*it)) {
          builder.Append(core::character::ToUpperCase(*it));
        } else {
          builder.Append(*it);
        }
      }
      c = builder.Build(ctx, false, IV_LV5_ERROR_WITH(e, NULL));
      currency_data = core::i18n::Currency::Lookup(std::string(c->begin(), c->end()));
    }

    // currencyDisplay option
    static const std::array<core::StringPiece, 3> kd = { {
      "code",
      "symbol",
      "name"
    } };
    JSString* cd =
        options.GetString(ctx, symbol::currencyDisplay(), kd.begin(), kd.end(), "symbol", IV_LV5_ERROR_WITH(e, NULL));
    display =
        (cd->compare("code") == 0) ?
          core::i18n::Currency::CODE :
        (cd->compare("name") == 0) ?
          core::i18n::Currency::NAME : core::i18n::Currency::SYMBOL;
  }

  const int32_t minimum_integer_digits =
      options.GetNumber(ctx,
                        symbol::minimumIntegerDigits(),
                        1,
                        21,
                        1, IV_LV5_ERROR_WITH(e, NULL));

  const int32_t minimum_fraction_digits_default =
      (style != core::i18n::NumberFormat::CURRENCY) ? 0 :
      currency_data ? currency_data->CurrencyDigits() : 2;
  const int32_t minimum_fraction_digits =
      options.GetNumber(ctx,
                        symbol::minimumFractionDigits(),
                        0,
                        20,
                        minimum_fraction_digits_default,
                        IV_LV5_ERROR_WITH(e, NULL));

  const int32_t maximum_fraction_digits_default =
      (style == core::i18n::NumberFormat::CURRENCY) ?
        (std::max)(minimum_fraction_digits,
                   currency_data ? currency_data->CurrencyDigits() : 2) :
      (style == core::i18n::NumberFormat::PERCENT) ?
        (std::max)(minimum_fraction_digits, 0) :
        (std::max)(minimum_fraction_digits, 3);
  const int32_t maximum_fraction_digits =
      options.GetNumber(ctx,
                        symbol::maximumFractionDigits(),
                        minimum_fraction_digits,
                        20,
                        maximum_fraction_digits_default,
                        IV_LV5_ERROR_WITH(e, NULL));

  int32_t minimum_significant_digits = core::i18n::NumberFormat::kUnspecified;
  int32_t maximum_significant_digits = core::i18n::NumberFormat::kUnspecified;
  if (o->HasOwnProperty(ctx, symbol::minimumSignificantDigits()) ||
      o->HasOwnProperty(ctx, symbol::maximumSignificantDigits())) {
    minimum_significant_digits =
        options.GetNumber(ctx,
                          symbol::minimumSignificantDigits(),
                          1,
                          21,
                          1, IV_LV5_ERROR_WITH(e, NULL));

    maximum_significant_digits =
        options.GetNumber(ctx,
                          symbol::maximumSignificantDigits(),
                          minimum_significant_digits,
                          21,
                          21, IV_LV5_ERROR_WITH(e, NULL));
  }

  bool use_grouping = false;
  {
    const JSVal ug = options.Get(ctx,
                                 symbol::useGrouping(),
                                 Options::BOOLEAN, NULL,
                                 JSTrue, IV_LV5_ERROR_WITH(e, NULL));
    use_grouping = ug.ToBoolean();
  }

  // TODO(Constellation) positie / negative patterns

  JSObject* f =
      JSNumberFormatHolder::New(
          ctx,
          c,
          new core::i18n::NumberFormat(
              locale,
              style,
              minimum_significant_digits,
              maximum_significant_digits,
              minimum_integer_digits,
              minimum_fraction_digits,
              maximum_fraction_digits,
              nu,
              currency_data,
              display,
              use_grouping));

  format->DefineOwnProperty(
      ctx,
      ctx->i18n()->symbols().initializedNumberFormat(),
      DataDescriptor(f, ATTR::N),
      false, IV_LV5_ERROR_WITH(e, NULL));

  return format;
}

inline JSVal NumberFormatSupportedLocalesOf(Context* ctx,
                                            JSVal val,
                                            JSVal options, Error* e) {
  JSVector* requested =
      CanonicalizeLocaleList(ctx, val, IV_LV5_ERROR(e));
  return SupportedLocales(
      ctx,
      core::i18n::NumberFormat::AvailableLocales().begin(),
      core::i18n::NumberFormat::AvailableLocales().end(),
      requested, options, e);
}

} } }  // namespace iv::lv5::i18n
#endif  // IV_LV5_I18N_NUMBER_FORMAT_H_