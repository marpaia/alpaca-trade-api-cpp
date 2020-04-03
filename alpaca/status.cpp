#include "alpaca/status.h"

namespace alpaca {

std::string actionStatusToString(const ActionStatus status) {
  switch (status) {
  case ActionStatus::Open:
    return "open";
  case ActionStatus::Closed:
    return "closed";
  case ActionStatus::Active:
    return "active";
  case ActionStatus::All:
    return "all";
  }
}
} // namespace alpaca