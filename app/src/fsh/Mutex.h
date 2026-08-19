#include <zephyr/kernel.h>

namespace fsh {
class Mutex {
 public:
  Mutex() { k_mutex_init(&_mutex); }

  Mutex(Mutex&&) = delete;
  Mutex(const Mutex&) = delete;
  Mutex& operator=(Mutex&&) = delete;
  Mutex& operator=(const Mutex&) = delete;

  auto lock(k_timeout_t max_wait = K_FOREVER) {
    return k_mutex_lock(&_mutex, max_wait);
  }
  auto unlock() { return k_mutex_unlock(&_mutex); }

 private:
  k_mutex _mutex;
};
}  // namespace fsh
