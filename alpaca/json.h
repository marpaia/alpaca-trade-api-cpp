#include "rapidjson/document.h"

#define PARSE_STRING(var, name)                                                                                        \
  if (d.HasMember(name) && d[name].IsString()) {                                                                       \
    var = d[name].GetString();                                                                                         \
  } else {                                                                                                             \
    return Status(1, "JSON didn't have field: " name);                                                                 \
  }

#define PARSE_INT(var, name)                                                                                           \
  if (d.HasMember(name) && d[name].IsInt()) {                                                                          \
    var = d[name].GetInt();                                                                                            \
  } else {                                                                                                             \
    return Status(1, "JSON didn't have field: " name);                                                                 \
  }

#define PARSE_BOOL(var, name)                                                                                          \
  if (d.HasMember(name) && d[name].IsBool()) {                                                                         \
    var = d[name].GetBool();                                                                                           \
  } else {                                                                                                             \
    return Status(1, "JSON didn't have field: " name);                                                                 \
  }