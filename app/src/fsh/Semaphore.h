#include <zephyr/kernel.h>

namespace fsh {
class Semaphore {
 public:
  Semaphore(size_t initial = 0, size_t maximum = K_SEM_MAX_LIMIT) {
    k_sem_init(&_sem, initial, maximum);
  }

  void give() { k_sem_give(&_sem); }
  auto take(k_timeout_t timeout = K_FOREVER) {
    return k_sem_take(&_sem, timeout);
  }

  Semaphore(Semaphore&&) = delete;
  Semaphore(const Semaphore&) = delete;
  Semaphore& operator=(Semaphore&&) = delete;
  Semaphore& operator=(const Semaphore&) = delete;

 private:
  k_sem _sem;
};
}  // namespace fsh
