#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

class Task {
    public:
        Task(int id);
        Task(const Task & task);
        Task();
        ~Task();

        int get_id() const;

        bool operator <(const Task & t) const {
            return id_ < t.get_id();
        }
        bool operator ==(const Task & t) const {
            return id_ == t.get_id();
        }
        bool operator !=(const Task & t) const {
            return id_ != t.get_id();
        }

    private:
        int id_;
};


#endif
