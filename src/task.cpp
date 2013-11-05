#include "task.h"

Task::Task(int id) : id_(id) {}

Task::Task(const Task & task) {
    id_ = task.get_id();
}

Task::Task() = default;

Task::~Task() {}

int Task::get_id() const {
    return id_;
}

