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

#ifndef SGE_KEYBOARD_HPP
#define SGE_KEYBOARD_HPP

#include <SGE/Export.hpp>
#include <string>

namespace sge {
class Window;

/**
 * \brief Class representing the keyboard
 *
 *
 * This object is used to represent the keyboard on the user's machine.
 * It describes events for the keyboard and maps all the keys in the Key enum.
 * Also the current key state for a window can be quarried through this class.
 * \note All the functions from this class should be called from the main thread
 */
class SGE_API Keyboard {
public:
    /**
     * \brief Keys
     *
     *
     * Represents all the keys on a US layout IBM compatible keyboard.
     */
    enum class Key {
        Escape,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        Tilde,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,
        Num0,
        Minus,
        Equal,
        Backspace,
        Tab,
        CapsLock,
        LShift,
        LCtrl,
        LAlt,
        Menu,
        LSystem,
        Space,
        RAlt,
        RSystem,
        RCtrl,
        RShift,
        Enter,
        Q,
        W,
        E,
        R,
        T,
        Y,
        U,
        I,
        O,
        P,
        LeftBracket,
        RightBracket,
        Backslash,
        A,
        S,
        D,
        F,
        G,
        H,
        J,
        K,
        L,
        Semicolon,
        Apostrophe,
        Z,
        X,
        C,
        V,
        B,
        N,
        M,
        Comma,
        Period,
        Slash,
        PageUp,
        PageDown,
        End,
        Home,
        Insert,
        Delete,
        ScrollLock,
        NumLock,
        PrintScreen,
        Pause,
        NumPad0,
        NumPad1,
        NumPad2,
        NumPad3,
        NumPad4,
        NumPad5,
        NumPad6,
        NumPad7,
        NumPad8,
        NumPad9,
        NumPadDivide,
        NumPadMultiply,
        NumPadMinus,
        NumPadPlus,
        NumPadDecimal,
        NumPadEnter,
        ArrowUp,
        ArrowDown,
        ArrowLeft,
        ArrowRight,
        Unknown
    };

    /**
     * \brief Key state
     *
     *
     * Represents the state of a key on the keyboard.
     */
    enum class KeyState {
        Pressed, ///< They key was pressed
        Repeating, ///< The key is held. This works like processing a held key as constantly generating press events
        Released ///< The key was released
    };

    /**
     * \brief Keyboard event
     *
     *
     * This structure is used to represent an event generated by the keyboard
     */
    struct KeyboardEvent {
        Key key; ///< The key that modified it's state
        KeyState state; ///< The new state of the key
        int scancode; ///< The platform-specific scancode of the key
        bool ctrl; ///< Ctrl was held
        bool shift; ///< Shift was held
        bool alt; ///< Alt was held
        bool system; ///< System(Windows) key was held
        bool capsLock; ///< Caps lock was enabled
        bool numLock; ///< Num lock was enabled
    };

    /**
     * \brief Get key from internal representation
     *
     *
     * Returns a Keyboard::Key type from an internally used integer.
     * \param keyCode The internal code of the key
     * \return Key type
     */
    static Key getKeyFromInternal(int keyCode);

    /**
     * \brief Get the internal representation of a key
     *
     *
     * Returns the internal integer used to represent the Keyboard::Key type.
     * \param key Keyboard::Key type
     * \return Integer used to represent the key
     */
    static int getCodeFromKey(Key key);

    /**
     * \brief Get key scancode
     *
     *
     * Returns the platform-specific scancode of a key.
     * \param key Keyboard::Key type
     * \return Scancode of the key
     */
    static int getKeyScancode(Key key);

    /**
     * \brief Get key name
     *
     *
     * Returns the human-readable name of a key from it's Keyboard::Key representation.
     * \note This only works for alphanumeric keys and grammar signs + the arithmetic operation signs.
     * \param key Keyboard::Key type
     * \return String containing the key name
     */
    static std::string getKeyName(Key key);

    /**
     * \brief Get key name
     *
     *
     * Returns the human-readable name of a key using it's platform-specific scancode
     * \note This only works for alphanumeric keys and grammar signs + the arithmetic operation signs.
     * \param scancode Key scancode
     * \return String containing the key name
     */
    static std::string getKeyName(int scancode);

    /**
     * \brief Get key state
     *
     *
     * Returns the current key state for a window.
     * \param window Window to pe polled for the state of the key
     * \param key The Keyboard::Key type
     * \return State of the key
     */
    static KeyState getKeyState(const Window& window, Key key);
};
}

#endif //SGE_KEYBOARD_HPP
