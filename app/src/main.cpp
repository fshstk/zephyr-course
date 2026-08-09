#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

namespace {
void t_low_fn() {
  size_t count = 0;
  while (true) {
    LOG_INF("T_LOW running\t[count %d]", ++count);
    k_msleep(300);
  }
}

void t_med_fn() {
  size_t count = 0;
  while (true) {
    LOG_INF("T_MED running\t[count %d]", ++count);
    k_msleep(200);
  }
}

void t_high_fn() {
  size_t count = 0;
  while (true) {
    LOG_INF("T_HIGH running\t[count %d]", ++count);
    k_msleep(100);
  }
}

const auto STACK_SIZE = 1024;
const auto PRIO_LOW = 7;
const auto PRIO_MED = 5;
const auto PRIO_HIGH = 3;

// clang-format off
K_THREAD_DEFINE(t_low,  STACK_SIZE, t_low_fn,  nullptr, nullptr, nullptr, PRIO_LOW,  0, 0);
K_THREAD_DEFINE(t_med,  STACK_SIZE, t_med_fn,  nullptr, nullptr, nullptr, PRIO_MED,  0, 0);
K_THREAD_DEFINE(t_high, STACK_SIZE, t_high_fn, nullptr, nullptr, nullptr, PRIO_HIGH, 0, 0);
// clang-format on
}  // namespace

int main() {
  LOG_INF("main() entered");
  return 0;
}
