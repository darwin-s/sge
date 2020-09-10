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

#ifndef SGE_APPLICATION_HPP
#define SGE_APPLICATION_HPP

#include <SGE/Export.hpp>

namespace sge {
/**
 * \brief Abstract base class for applications
 *
 *
 * This class is used as a base for applications
 * build on top of SGE. It is recommended to use
 * this base class, as it does all the initializations
 * needed for a properly functioning application. It
 * opens the global log file and initializes all the needed
 * sub-systems. A derived class should implement the onInit
 * and onRun functions.
 * \note Only one application can exist at a time.
 * \note An application must be created only in the main thread
 *
 * Usage example:
 * \code
 * class MyApp : public sge::Application {
 * public:
 *     MyApp(int argc, char** argv)
 *         : sge::Application(argc, argv) {
 *         // Program initialization(perquisites, custom library initialization)...
 *     }
 *
 *     ~MyApp() override {
 *         // Program termination...
 *     }
 * private:
 *     sge::Application::ReturnCode onInit() override {
 *         // Resource initialization...
 *         return sge::Application::ReturnOk;
 *     }
 *
 *     sge::Application::ReturnCode onRun() override {
 *         // Program execution...
 *         return sge::Application::ReturnOk;
 *     }
 * }
 *
 * int main(int argc, char** argv) {
 *     MyApp ma(argc, argv);
 *     return ma.run();
 * }
 * \endcode
 */
class SGE_API Application {
public:
    /**
     * \brief Application return code
     *
     *
     * Represents the result of an application
     */
    enum ReturnCode {
        ReturnError = -1,///< Problems were encountered
        ReturnOk    = 0  ///< Operation completed successfully
    };

    /**
     * \brief Construct an application
     *
     *
     * Constructs an application without any arguments (the argument list is empty.
     */
    Application();

    /**
     * \brief Construct an application
     *
     *
     * Constructs an application with arguments
     * \param argc Number of arguments
     * \param argv Array of C-style argument strings
     */
    Application(int argc, char** argv);

    /**
     * \brief Destruct an application
     *
     *
     * Destructs an application and closes all libraries used.
     */
    virtual ~Application();
    Application(const Application&) = delete;
    Application(Application&&)      = delete;
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;

    /**
     * \brief Run application
     *
     *
     * Starts the application, first by calling Application::onInit and if succeeds
     * it will call Application::onRun.
     * \return Application return code
     * \sa Application::ReturnCode
     */
    ReturnCode run();

    /**
     * \brief Get arguments
     *
     *
     * Get the arguments used to create the current application.
     * \return Pointer to application arguments
     */
    [[nodiscard]] const char* const* getArgs() const;

    /**
     * \brief Get argument cound
     *
     *
     * Get the number of arguments passed to the application.
     * \return Number of application arguments
     */
    [[nodiscard]] int getArgCount() const;

    [[noreturn]] static void crashApplication(const char* reason);

private:
    /**
     * \brief Application initialization
     *
     *
     * Initialize the resources needed to start the application
     * \note This method should be overwritten by child classes.
     * \return Application return code
     * \sa Application::ReturnCode
     */
    virtual ReturnCode onInit() = 0;

    /**
     * \brief Application execution
     *
     *
     * Run the application.
     * \note This method should be overwritten by child classes.
     * \return Application return code
     * \sa Application::ReturnCode
     */
    virtual ReturnCode onRun() = 0;

    const char* const* m_args;
    int m_argc;
};
}

#endif//SGE_APPLICATION_HPP
