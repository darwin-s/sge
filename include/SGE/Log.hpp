// Copyright 2020 Sirbu Dan
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

#ifndef SGE_LOG_HPP
#define SGE_LOG_HPP

#include <SGE/Export.hpp>
#include <fstream>
#include <filesystem>
#include <string_view>
#include <mutex>

namespace sge {
/**
 * \brief An object representing a log file
 *
 *
 * sge::Log represents a log file and allows
 * writing to it different types of values.
 * A Log can have different types of messages,
 * like Info, Warning, Error or Debug. The Log
 * uses stream insert operators (<<) to write.
 * A message end with an Operation::Endl. Each
 * message is prepended with the Log::MessageType and
 * the current time and date (dd/mm/yyyy@hh:mm:ss).
 * There is a global instance provided for convenience
 * and exceptions, but it is not opened by default. A Log
 * should be opened before you try to write to it.
 * \note The global log instance is not thread-safe and access to it should be accessed while locking the provided mutex
 * Usage example:
 * \code
 * if (!sge::Log::general.open("log.txt")) {
 *     //error...
 * }
 * sge::Log::general << sge::Log::MessageType::Debug <<
 *     "Hello, world!" << sge::Log::Operation::Endl;
 * \endcode
 */
class SGE_API Log {
public:
    /**
     * \brief Message type
     *
     *
     * Represents the type of the message to be written.
     * Changing the message type in the middle of writing the
     * message will influence only the next message (the next one after an Operation::Endl).
     */
    enum class MessageType {
        Info, ///< Purely informational message (status updates, general info, etc.)
        Warning, ///< A warning, that is not critical, but the user should be wary
        Error, ///< An error, that needs to be immediately addressed
        Debug ///< Debug information
    };

    /**
     * \brief Operation on the log
     *
     *
     * Represents the operation to be performed on the Log object.
     */
    enum class Operation {
        Endl ///< End the current message and start a new one
    };

    /**
     * \brief Default construct a Log object
     *
     *
     * Creates a Log object, but does not open the file.
     */
    Log();

    /**
     * \brief Construct a Log object
     *
     *
     * Creates a Log object and opens the log file.
     * \note If the file already exists, the Log object will append to it.
     * \param file Path to the log file to be opened
     */
    explicit Log(const std::filesystem::path& file);

    /**
     * \brief Destroys a Log object
     *
     *
     * Closes and then destroys a Log object.
     */
    ~Log();
    Log(const Log&) = delete;

    /**
     * \brief Move-construct a Log object
     *
     *
     * Moves every member of the other Log and
     * invalidates it by closing it.
     * \param other The Log to move from
     */
    Log(Log&& other) noexcept;
    Log& operator=(const Log&) = delete;

    /**
     * Move-assign a Log object
     *
     *
     * Moves every member of the other Log and
     * invalidates it by closing it
     * \param other The Log to move from
     * \return *this
     */
    Log& operator=(Log&& other) noexcept;

    /**
     * \brief Set message type
     *
     *
     * Sets the message type type for <b>the next</b> message.
     * \note If the current message is not completed (Log::Operation::Endl has not been passed)
     * \note then this function will not have an effect until the next message.
     * \sa Log::MessageType
     * \param message The type of the message
     * \return *this
     */
    Log& operator<<(MessageType message);

    /**
     * \brief Write a boolean.
     *
     *
     * Writes a boolean value to the log file as
     * "true" or "false", depending on the value passed.
     * \param b Boolean to write
     * \return *this
     */
    Log& operator<<(bool b);

    /**
     * \brief Write a signed integer
     *
     *
     * Writes a signed integer to the log file.
     * If the values is negative, then the sign is
     * prepended.
     * \param i Integer to write
     * \return *this
     */
    Log& operator<<(signed int i);

    /**
     * \brief Write an unsigned integer
     *
     *
     * Writes an unsigned integer to the log file.
     * \param i Integer to write
     * \return *this
     */
    Log& operator<<(unsigned int i);

    /**
     * \brief Write a float
     *
     *
     * Writes a float value to the log file.
     * \param f Float to write
     * \return *this
     */
    Log& operator<<(float f);

    /**
     * \brief Write a double
     *
     *
     * Writes a double-precision float to
     * the log file.
     * \param d Double to write
     * \return *this
     */
    Log& operator<<(double d);

    /**
     * \brief Write a string
     *
     *
     * Writes a string to the log file.
     * \note New-lines in messages are allowed, although highly discouraged.
     * \param s String to write
     * \return *this
     */
    Log& operator<<(std::string_view s);

    /**
     * \brief Write a string
     *
     *
     * Writes a C-style string to the log file.
     * \note C-Style strings are limited to 256 characters for safety.
     * \note New-lines in messages are allowed, although highly discouraged.
     * \param s String to write
     * \return *this
     */
    Log& operator<<(const char* s);

    /**
     * \brief Perform an operation on the Log
     *
     *
     * Performs an operation on the log file
     * \sa Log::Operation
     * \param op Operation to be executed
     * \return *this
     */
    Log& operator<<(Operation op);

    /**
     * \brief Open the log file
     *
     *
     * Opens the log file, closing the current one if applicable.
     * \note If the file already exists, the Log object will append to it.
     * \param file Path to the log file to be opened
     * \return true on success, false otherwise
     */
    bool open(const std::filesystem::path& file);

    /**
     * \brief Check if the log file is open
     *
     *
     * Checks if the current Log object has an opened file associated
     * with it.
     * \return true if the file has been opened, false otherwise
     */
    [[nodiscard]] bool isOpen() const;

    /**
     * \brief Close Log
     *
     *
     * Closes the current log file, writing any remaining messages.
     */
    void close();

    /**
     * \brief Get message type
     *
     *
     * Returns the current set message type.
     * \return Current message type
     */
    [[nodiscard]] MessageType getMessageType() const;

    static Log general; ///< A global Log instance for convenience (not opened by default)
    static std::mutex generalMutex; ///< Global mutex to protect the global instance
private:
    MessageType m_mt;
    std::ofstream m_log;
    bool m_writeTime;
};
}

#endif // SGE_LOG_HPP
