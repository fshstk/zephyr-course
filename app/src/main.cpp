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

void t_coop_fn() {
  constexpr auto num_loops = 5;
  for (auto count = 1U; count <= num_loops; ++count) {
    LOG_INF("T_COOP running\t[count %d/%d]", count, num_loops);
    k_busy_wait(500'000);
  }
  k_yield();  // technically redundant since function exits...
}

const size_t STACK_SIZE = 1024;
const int PRIO_LOW = 7;
const int PRIO_MED = 5;
const int PRIO_HIGH = 3;
const int PRIO_COOP = -1;

// clang-format off
K_THREAD_DEFINE(t_low,  STACK_SIZE, t_low_fn,  nullptr, nullptr, nullptr, PRIO_LOW,  0, 0);
K_THREAD_DEFINE(t_med,  STACK_SIZE, t_med_fn,  nullptr, nullptr, nullptr, PRIO_MED,  0, 0);
K_THREAD_DEFINE(t_high, STACK_SIZE, t_high_fn, nullptr, nullptr, nullptr, PRIO_HIGH, 0, 0);
K_THREAD_DEFINE(t_coop, STACK_SIZE, t_coop_fn, nullptr, nullptr, nullptr, PRIO_COOP, 0, 0);
// clang-format on
}  // namespace

int main() {
  LOG_INF("main() entered");
  return 0;
}
