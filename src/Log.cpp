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
#include <iostream>
#include <chrono>
#include <ctime>
#include <cassert>
#include <stdexcept>

namespace {
constexpr int maxStringSize = 256;

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
std::mutex Log::generalMutex;

Log::Log() : m_mt(MessageType::Info), m_writeTime(false) {
}

Log::Log(const std::filesystem::path& file)
    : m_mt(MessageType::Info), m_writeTime(true) {
    if (!open(file)) {
        throw std::runtime_error("Failed to open log");
    }
}

Log::~Log() {
    close();
}

Log::Log(Log&& other) noexcept
    : m_mt(other.m_mt), m_writeTime(other.m_writeTime) {
    m_log = std::move(other.m_log);
}

Log& Log::operator=(Log&& other) noexcept {
    m_mt        = other.m_mt;
    m_writeTime = other.m_writeTime;

    m_log = std::move(other.m_log);

    return *this;
}

Log& Log::operator<<(const MessageType message) {
    m_mt = message;

    return *this;
}

Log& Log::operator<<(const bool b) {
    assert(m_log.is_open());

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
        m_log << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
              << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour
              << ":" << t.tm_min << ":" << t.tm_sec << "] ";

        if (consOut) {
            *os << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
                << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour
                << ":" << t.tm_min << ":" << t.tm_sec << "] ";
        }

        m_writeTime = false;
    }

    if (b) {
        m_log << "true";
        if (consOut) {
            *os << "true";
        }
    } else {
        m_log << "false";
        if (consOut) {
            *os << "false";
        }
    }

    return *this;
}

Log& Log::operator<<(const signed int i) {
    assert(m_log.is_open());

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
        m_log << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
              << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour
              << ":" << t.tm_min << ":" << t.tm_sec << "] ";

        if (consOut) {
            *os << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
                << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour
                << ":" << t.tm_min << ":" << t.tm_sec << "] ";
        }

        m_writeTime = false;
    }

    m_log << i;
    if (consOut) {
        *os << i;
    }

    return *this;
}

Log& Log::operator<<(const unsigned int i) {
    assert(m_log.is_open());

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
        m_log << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
              << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour
              << ":" << t.tm_min << ":" << t.tm_sec << "] ";

        if (consOut) {
            *os << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
                << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour
                << ":" << t.tm_min << ":" << t.tm_sec << "] ";
        }

        m_writeTime = false;
    }

    m_log << i;
    if (consOut) {
        *os << i;
    }

    return *this;
}

Log& Log::operator<<(const float f) {
    assert(m_log.is_open());

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
        m_log << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
              << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour
              << ":" << t.tm_min << ":" << t.tm_sec << "] ";

        if (consOut) {
            *os << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
                << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour
                << ":" << t.tm_min << ":" << t.tm_sec << "] ";
        }

        m_writeTime = false;
    }

    m_log << f;
    if (consOut) {
        *os << f;
    }

    return *this;
}

Log& Log::operator<<(const double d) {
    assert(m_log.is_open());

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
        m_log << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
              << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour
              << ":" << t.tm_min << ":" << t.tm_sec << "] ";

        if (consOut) {
            *os << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
                << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour
                << ":" << t.tm_min << ":" << t.tm_sec << "] ";
        }

        m_writeTime = false;
    }

    m_log << d;
    if (consOut) {
        *os << d;
    }

    return *this;
}

Log& Log::operator<<(const std::string_view s) {
    assert(m_log.is_open());

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
        m_log << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
              << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour
              << ":" << t.tm_min << ":" << t.tm_sec << "] ";

        if (consOut) {
            *os << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
                << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour
                << ":" << t.tm_min << ":" << t.tm_sec << "] ";
        }

        m_writeTime = false;
    }

    m_log << s;
    if (consOut) {
        *os << s;
    }

    return *this;
}

Log& Log::operator<<(const char* s) {
    assert(m_log.is_open());

    auto consOut = false;
    auto* os     = &std::cout;
    if (m_mt == MessageType::Error) {
        os = &std::cerr;
    }
    if (this == &general) {
        consOut = true;
    }

    if (s == nullptr) {
        throw std::invalid_argument("Null C-style string");
    }

    if (!isStringSafe(s)) {
        throw std::invalid_argument(
            "C-style string longer than 256 characters");
    }

    if (m_writeTime) {
        const auto t = getLocalTime();
        m_log << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
              << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour
              << ":" << t.tm_min << ":" << t.tm_sec << "] ";

        if (consOut) {
            *os << "[" << getMtText(m_mt) << "][" << t.tm_mday << "/"
                << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "@" << t.tm_hour
                << ":" << t.tm_min << ":" << t.tm_sec << "] ";
        }

        m_writeTime = false;
    }

    m_log << s;
    if (consOut) {
        *os << s;
    }

    return *this;
}

Log& Log::operator<<(const Operation op) {
    assert(m_log.is_open());

    auto consOut = false;
    auto* os     = &std::cout;
    if (m_mt == MessageType::Error) {
        os = &std::cerr;
    }
    if (this == &general) {
        consOut = true;
    }

    if (op == Operation::Endl) {
        m_log << std::endl;
        if (consOut) {
            *os << std::endl;
        }
        m_writeTime = true;
    }

    return *this;
}

bool Log::open(const std::filesystem::path& file) {
    if (m_log.is_open()) {
        close();
    }

    m_mt = MessageType::Info;
    m_log.open(file, std::ios::out | std::ios::app);
    m_writeTime = true;

    const auto t = getLocalTime();
    m_log << "Log started at " << t.tm_mday << "/" << t.tm_mon + 1 << "/"
          << t.tm_year + 1900 << "@" << t.tm_hour << ":" << t.tm_min << ":"
          << t.tm_sec << std::endl;

    return m_log.is_open();
}

bool Log::isOpen() const {
    return m_log.is_open();
}

void Log::close() {
    if (!m_log.is_open()) {
        return;
    }

    if (!m_writeTime) {
        m_log << std::endl;
    }

    m_writeTime = true;
    m_mt        = MessageType::Info;

    const auto t = getLocalTime();
    m_log << "Log ended at " << t.tm_mday << "/" << t.tm_mon + 1 << "/"
          << t.tm_year + 1900 << "@" << t.tm_hour << ":" << t.tm_min << ":"
          << t.tm_sec << std::endl;

    m_log.close();
}

Log::MessageType Log::getMessageType() const {
    return m_mt;
}
}
