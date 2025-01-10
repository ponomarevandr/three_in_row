#include "worker.h"


namespace Thread {

void Worker::run() {
	while (true) {
		{
			std::unique_lock lock(mutex);
			while (is_ready && !shall_be_terminated) {
				action_pending.wait(lock);
			}
			if (shall_be_terminated)
				break;
		}
		action();
		{
			std::lock_guard lock(mutex);
			is_ready = true;
		}
		action_pending.notify_one();
	}
}

void Worker::nextAction() {
	{
		std::lock_guard lock(mutex);
		is_ready = false;
	}
	action_pending.notify_one();
}

bool Worker::isReady() const {
	std::lock_guard lock(mutex);
	return is_ready;
}

void Worker::waitReady() const {
	std::unique_lock lock(mutex);
	while (!is_ready) {
		action_pending.wait(lock);
	}
}

void Worker::terminate() {
	{
		std::lock_guard lock(mutex);
		shall_be_terminated = true;
	}
	action_pending.notify_one();
}

}