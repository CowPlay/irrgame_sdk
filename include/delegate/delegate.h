#ifndef __DELEGATE_H_INCLUDED__
#define __DELEGATE_H_INCLUDED__

// 1 parameter
#define SUFFIX       1
#define TEMPLATE_PARAMS  \
  , class TP1
#define TEMPLATE_ARGS    , TP1
#define PARAMS       TP1 p1
#define ARGS         p1

#include "IDelegate.h"
#include "CStaticDelegate.h"
#include "CMethodDelegate.h"
#include "CDelegate.h"

#undef SUFFIX
#undef TEMPLATE_PARAMS
#undef TEMPLATE_ARGS
#undef PARAMS
#undef ARGS

#endif
