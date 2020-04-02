#include "rapidjson/document.h"

#define PARSE_STRING(var, name)                                                                                        \
  if (d.HasMember(name) && d[name].IsString()) {                                                                       \
    var = d[name].GetString();                                                                                         \
  }

#define PARSE_INT(var, name)                                                                                           \
  if (d.HasMember(name) && d[name].IsInt()) {                                                                          \
    var = d[name].GetInt();                                                                                            \
  }

#define PARSE_BOOL(var, name)                                                                                          \
  if (d.HasMember(name) && d[name].IsBool()) {                                                                         \
    var = d[name].GetBool();                                                                                           \
  }