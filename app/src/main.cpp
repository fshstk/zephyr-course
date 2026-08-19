#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include "fsh/Semaphore.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

namespace {
size_t count = 0;
fsh::Semaphore count_done;
const size_t MAX_COUNT = 100'000;

void increment() {
  for (size_t i = 0; i < MAX_COUNT; ++i)
    count++;
  count_done.give();
  const auto* thread_name = k_thread_name_get(k_current_get());
  LOG_INF("[%s]: increment finished", thread_name);
}

const size_t STACK_SIZE = 1024;
const int PRIO_MED = 5;

// clang-format off
K_THREAD_DEFINE(increment_a, STACK_SIZE, increment, nullptr, nullptr, nullptr, PRIO_MED, 0, 0);
K_THREAD_DEFINE(increment_b, STACK_SIZE, increment, nullptr, nullptr, nullptr, PRIO_MED, 0, 0);
// clang-format on
}  // namespace

int main() {
  auto t_start = k_uptime_get();
  LOG_INF("main() entered");
  count_done.take();
  count_done.take();
  const auto t_delta = k_uptime_delta(&t_start);
  const auto expected = 2 * MAX_COUNT;
  LOG_INF("count done: %d (expected %d)\t[%lld ms]", count, expected, t_delta);
  if (count != expected)
    LOG_ERR("expected and actual values do not match");
  return 0;
}
