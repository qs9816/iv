#ifndef _IV_LV5_RUNTIME_TELEPORTER_H_
#define _IV_LV5_RUNTIME_TELEPORTER_H_
#include "lv5/teleporter.h"
#include "lv5/internal.h"
namespace iv {
namespace lv5 {
namespace teleporter {

inline JSVal InDirectCallToEval(const Arguments& args, Error* error) {
  if (!args.size()) {
    return JSUndefined;
  }
  const JSVal& first = args[0];
  if (!first.IsString()) {
    return first;
  }
  Context* const ctx = args.ctx();
  JSScript* const script = CompileScript(args.ctx(), first.string(),
                                         false, ERROR(error));
                                         //  ctx->IsStrict(), ERROR(error));
  if (script->function()->strict()) {
    JSDeclEnv* const env = NewDeclarativeEnvironment(ctx, ctx->global_env());
    const Interpreter::ContextSwitcher switcher(ctx,
                                                env,
                                                env,
                                                ctx->global_obj(),
                                                true);
    ctx->Run(script);
  } else {
    const Interpreter::ContextSwitcher switcher(ctx,
                                                ctx->global_env(),
                                                ctx->global_env(),
                                                ctx->global_obj(),
                                                false);
    ctx->Run(script);
  }
  if (ctx->IsShouldGC()) {
    GC_gcollect();
  }
  return ctx->ret();
}

inline JSVal DirectCallToEval(const Arguments& args, Error* error) {
  if (!args.size()) {
    return JSUndefined;
  }
  const JSVal& first = args[0];
  if (!first.IsString()) {
    return first;
  }
  Context* const ctx = args.ctx();
  JSScript* const script = CompileScript(args.ctx(), first.string(),
                                         ctx->IsStrict(), ERROR(error));
  if (script->function()->strict()) {
    JSDeclEnv* const env = NewDeclarativeEnvironment(ctx, ctx->lexical_env());
    const Interpreter::ContextSwitcher switcher(ctx,
                                                env,
                                                env,
                                                ctx->this_binding(),
                                                true);
    ctx->Run(script);
  } else {
    ctx->Run(script);
  }
  if (ctx->IsShouldGC()) {
    GC_gcollect();
  }
  return ctx->ret();
}

inline JSVal FunctionConstructor(const Arguments& args, Error* e) {
  Context* const ctx = args.ctx();
  StringBuilder builder;
  BuildFunctionSource(&builder, args, ERROR(e));
  JSString* const source = builder.Build(ctx);
  JSScript* const script = CompileScript(ctx, source, false, ERROR(e));
  IsOneFunctionExpression(*script->function(), ERROR(e));
  const Interpreter::ContextSwitcher switcher(ctx,
                                              ctx->global_env(),
                                              ctx->global_env(),
                                              ctx->global_obj(),
                                              false);
  ctx->Run(script);
  if (ctx->IsShouldGC()) {
    GC_gcollect();
  }
  return ctx->ret();
}

}  // iv::lv5::teleporter
namespace runtime {
} } }  // iv::lv5::runtime
#endif  // _IV_LV5_RUNTIME_TELEPORTER_H_