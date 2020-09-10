// Copyright 2020 Dan Sirbu
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <SGE/Log.hpp>
#include <SGE/Application.hpp>
#include <fstream>
#include <mutex>
#include <iostream>
#include <chrono>
#include <ctime>
#include <cassert>
#include <stdexcept>

namespace {
constexpr int maxStringSize = 1024;

std::tm getLocalTime() {
    std::tm t{};

    const auto now = std::chrono::system_clock::now();
    auto time      = std::chrono::system_clock::to_time_t(now);

#ifdef SGE_UNIX
    localtime_r(&time, &t);
#elif defined SGE_WIN32
    localtime_s(&t, &time);
#else
#error "No safe localtime alternative"
#endif

    return t;
}

const char* getMtText(const sge::Log::MessageType mt) {
    switch (mt) {
    case sge::Log::MessageType::Info:
        return "INF";
    case sge::Log::MessageType::Warning:
        return "WRN";
    case sge::Log::MessageType::Error:
        return "ERR";
    case sge::Log::MessageType::Debug:
        return "DBG";
    default:
        return "UNK";// Should not reach this path, but who knows
    }
}

bool isStringSafe(const char* s) {
    for (auto i = 0; i < maxStringSize; i++) {
        if (s[i] == '\0') {
            return true;
        }
    }

    return true;
}
}

namespace sge {
Log Log::general;

Log::Log()
    : m_mt(MessageType::Info), m_log(nullptr), m_writeTime(false),
      m_mutex(nullptr) {
    try {
        m_log = new std::ofstream;
        m_mutex = new std::mutex;
    } catch (...) {
        Application::crashApplication("Bad alloc");
    }
}

Log::Log(const char* file)
    : m_mt(MessageType::Info), m_log(new std::ofstream), m_writeTime(true),
      m_mutex(new std::mutex) {
    if (!open(file)) {
        Application::crashApplication("Failed to open log");
    }
}

Log::~Log() {
    auto* l = reinterpret_cast<std::ofstream*>(m_log);
    auto* m = reinterpret_cast<std::mutex*>(m_mutex);

    close();
    delete m;
    delete l;
}

Log::Log(Log&& other) noexcept
    : m_mt(other.m_mt), m_writeTime(other.m_writeTime) {
    m_log       = other.m_log;
    other.m_log = nullptr;
}

Log& Log::operator=(Log&& other) noexcept {
    m_mt        = other.m_mt;
    m_writeTime = other.m_writeTime;

    m_log       = other.m_log;
    other.m_log = nullptr;

    return *this;
}

Log& Log::operator<<(const MessageType message) {
    auto* m = reinterpret_cast<std::mutex*>(m_mutex);

    try {
        std::scoped_lock lck(*m);

        m_mt = message;

        return *this;
    } catch (...) {
        Application::crashApplication("Failed to lock mutex");
    }
}

Log& Log::operator<<(const bool b) {
    auto* l = reinterpret_cast<std::ofstream*>(m_log);
    auto* m = reinterpret_cast<std::mutex*>(m_mutex);
    assert(l->is_open());

    try {
        std::scoped_lock lck(*m);

        auto consOut = false;
        auto* os     = &std::cout;
        if (m_mt == MessageType::Error) {
            os = &std::cerr;
        }
        if (this == &general) {
            consOut = true;
        }

        if (m_writeTime) {
            const auto t = getLocalTime();
            *l << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
               << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour
               << ":" << t.tm_min << ":" << t.tm_sec << "] ";

            if (consOut) {
                *os << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
                    << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@"
                    << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << "] ";
            }

            m_writeTime = false;
        }

        if (b) {
            *l << "true";
            if (consOut) {
                *os << "true";
            }
        } else {
            *l << "false";
            if (consOut) {
                *os << "false";
            }
        }

        return *this;
    } catch (...) {
        Application::crashApplication("Failed to lock mutex");
    }
}

Log& Log::operator<<(const signed int i) {
    auto* l = reinterpret_cast<std::ofstream*>(m_log);
    auto* m = reinterpret_cast<std::mutex*>(m_mutex);
    assert(l->is_open());

    try {
        std::scoped_lock lck(*m);

        auto consOut = false;
        auto* os     = &std::cout;
        if (m_mt == MessageType::Error) {
            os = &std::cerr;
        }
        if (this == &general) {
            consOut = true;
        }

        if (m_writeTime) {
            const auto t = getLocalTime();
            *l << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
               << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour
               << ":" << t.tm_min << ":" << t.tm_sec << "] ";

            if (consOut) {
                *os << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
                    << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@"
                    << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << "] ";
            }

            m_writeTime = false;
        }

        *l << i;
        if (consOut) {
            *os << i;
        }

        return *this;
    } catch (...) {
        Application::crashApplication("Failed to lock mutex");
    }
}

Log& Log::operator<<(const unsigned int i) {
    auto* l = reinterpret_cast<std::ofstream*>(m_log);
    auto* m = reinterpret_cast<std::mutex*>(m_mutex);
    assert(l->is_open());

    try {
        std::scoped_lock lck(*m);

        auto consOut = false;
        auto* os     = &std::cout;
        if (m_mt == MessageType::Error) {
            os = &std::cerr;
        }
        if (this == &general) {
            consOut = true;
        }

        if (m_writeTime) {
            const auto t = getLocalTime();
            *l << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
               << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour
               << ":" << t.tm_min << ":" << t.tm_sec << "] ";

            if (consOut) {
                *os << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
                    << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@"
                    << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << "] ";
            }

            m_writeTime = false;
        }

        *l << i;
        if (consOut) {
            *os << i;
        }

        return *this;
    } catch (...) {
        Application::crashApplication("Failed to lock mutex");
    }
}

Log& Log::operator<<(const float f) {
    auto* l = reinterpret_cast<std::ofstream*>(m_log);
    auto* m = reinterpret_cast<std::mutex*>(m_mutex);
    assert(l->is_open());

    try {
        std::scoped_lock lck(*m);

        auto consOut = false;
        auto* os     = &std::cout;
        if (m_mt == MessageType::Error) {
            os = &std::cerr;
        }
        if (this == &general) {
            consOut = true;
        }

        if (m_writeTime) {
            const auto t = getLocalTime();
            *l << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
               << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour
               << ":" << t.tm_min << ":" << t.tm_sec << "] ";

            if (consOut) {
                *os << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
                    << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@"
                    << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << "] ";
            }

            m_writeTime = false;
        }

        *l << f;
        if (consOut) {
            *os << f;
        }

        return *this;
    } catch (...) {
        Application::crashApplication("Failed to lock mutex");
    }
}

Log& Log::operator<<(const double d) {
    auto* l = reinterpret_cast<std::ofstream*>(m_log);
    auto* m = reinterpret_cast<std::mutex*>(m_mutex);
    assert(l->is_open());

    try {
        std::scoped_lock lck(*m);

        auto consOut = false;
        auto* os     = &std::cout;
        if (m_mt == MessageType::Error) {
            os = &std::cerr;
        }
        if (this == &general) {
            consOut = true;
        }

        if (m_writeTime) {
            const auto t = getLocalTime();
            *l << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
               << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour
               << ":" << t.tm_min << ":" << t.tm_sec << "] ";

            if (consOut) {
                *os << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
                    << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@"
                    << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << "] ";
            }

            m_writeTime = false;
        }

        *l << d;
        if (consOut) {
            *os << d;
        }

        return *this;
    } catch (...) {
        Application::crashApplication("Failed to lock mutex");
    }
}

Log& Log::operator<<(const char* s) {
    auto* l = reinterpret_cast<std::ofstream*>(m_log);
    auto* m = reinterpret_cast<std::mutex*>(m_mutex);
    assert(l->is_open());

    try {
        std::scoped_lock lck(*m);

        auto consOut = false;
        auto* os     = &std::cout;
        if (m_mt == MessageType::Error) {
            os = &std::cerr;
        }
        if (this == &general) {
            consOut = true;
        }

        if (s == nullptr) {
            Application::crashApplication("Null C-style string");
        }

        if (!isStringSafe(s)) {
            Application::crashApplication(
                "C-style string longer than 256 characters");
        }

        if (m_writeTime) {
            const auto t = getLocalTime();
            *l << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
               << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour
               << ":" << t.tm_min << ":" << t.tm_sec << "] ";

            if (consOut) {
                *os << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
                    << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@"
                    << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << "] ";
            }

            m_writeTime = false;
        }

        *l << s;
        if (consOut) {
            *os << s;
        }

        return *this;
    } catch (...) {
        Application::crashApplication("Failed to lock mutex");
    }
}

Log& Log::operator<<(const Operation op) {
    auto* l = reinterpret_cast<std::ofstream*>(m_log);
    auto* m = reinterpret_cast<std::mutex*>(m_mutex);
    assert(l->is_open());

    try {
        std::scoped_lock lck(*m);

        auto consOut = false;
        auto* os     = &std::cout;
        if (m_mt == MessageType::Error) {
            os = &std::cerr;
        }
        if (this == &general) {
            consOut = true;
        }

        if (op == Operation::Endl) {
            *l << std::endl;
            if (consOut) {
                *os << std::endl;
            }
            m_writeTime = true;
        }

        return *this;
    } catch (...) {
        Application::crashApplication("Failed to lock mutex");
    }
}

bool Log::open(const char* file) {
    auto* l = reinterpret_cast<std::ofstream*>(m_log);
    auto* m = reinterpret_cast<std::mutex*>(m_mutex);

    try {
        std::scoped_lock lck(*m);

        if (l->is_open()) {
            close();
        }

        m_mt = MessageType::Info;
        l->open(file, std::ios::out | std::ios::app);
        m_writeTime = true;

        const auto t = getLocalTime();
        *l << "Log started at " << t.tm_mday << "/" << t.tm_mon + 1 << "/"
           << t.tm_year + 1900 << "@" << t.tm_hour << ":" << t.tm_min << ":"
           << t.tm_sec << std::endl;

        return l->is_open();
    } catch (...) {
        Application::crashApplication("Failed to lock mutex");
    }
}

bool Log::isOpen() const {
    auto* l = reinterpret_cast<std::ofstream*>(m_log);
    auto* m = reinterpret_cast<std::mutex*>(m_mutex);

    try {
        std::scoped_lock lck(*m);
        return l->is_open();
    } catch (...) {
        Application::crashApplication("Failed to lock mutex");
    }
}

void Log::close() {
    auto* l = reinterpret_cast<std::ofstream*>(m_log);
    auto* m = reinterpret_cast<std::mutex*>(m_mutex);

    try {
        std::scoped_lock lck(*m);
        if (!l->is_open()) {
            return;
        }

        if (!m_writeTime) {
            *l << std::endl;
        }

        m_writeTime = true;
        m_mt        = MessageType::Info;

        const auto t = getLocalTime();
        *l << "Log ended at " << t.tm_mday << "/" << t.tm_mon + 1 << "/"
           << t.tm_year + 1900 << "@" << t.tm_hour << ":" << t.tm_min << ":"
           << t.tm_sec << std::endl;

        l->close();
    } catch (...) {
        Application::crashApplication("Failed to lock mutex");
    }
}

Log::MessageType Log::getMessageType() const {
    auto* m = reinterpret_cast<std::mutex*>(m_mutex);
    try {
        std::scoped_lock lck(*m);
        return m_mt;
    } catch (...) {
        Application::crashApplication("Failed to lock mutex");
    }
}
}
