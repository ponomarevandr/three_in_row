#pragma once

#include <mutex>
#include <condition_variable>


namespace Thread {

// Абстрактный исполнитель, работающий в отдельном потоке, строго для одного родительского потока
class Worker {
private:
	bool is_ready = true;
	bool shall_be_terminated = false;
	mutable std::mutex mutex;
	mutable std::condition_variable action_pending;

protected:
	virtual void action() = 0;

public:
	Worker() = default;
	void run();					// В отдельном потоке
	void nextAction();			// Только при условии готовности
	bool isReady() const;
	void waitReady() const;
	void terminate();			// Только при условии готовности
};

}