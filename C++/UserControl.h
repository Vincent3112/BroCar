/** Class providing information about the user interaction.
 *
 * The user must be able to take control of the car at any moment.
 */

#ifndef USER_CONTROL_H
#define USER_CONTROL_H

#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <unistd.h>
#include <string>

class UserControl
{
    public:

    /** Mode influencing the decision process.
     *
     */
    enum ControlType {
        Manual,         /**< The user controls the car with the keyboard. */
        Autonomous,     /**< The car drives by itself using sensors. */
    };

    /** The user input from the terminal
     *
     */
    enum UserInput {
        Forward,        /**< Action needs to be taken to go forward */
        Right,          /**< Action needs to be taken to go right */
        Backward,       /**< Action needs to be taken to go backward */
        Left,           /**< Action needs to be taken to go left */
        Stop,           /*!< Action needs to be taken to stop the car */
        Exit,
        Undefined,
    };

    /*!
       \brief "Description"
       \param "Param description"
       \pre "Pre-conditions"
       \post "Post-conditions"
       \return "Return of the function"
    */
    struct UserData {
        ControlType controlType;
        UserInput direction;
        std::chrono::duration<double> timeSinceLastInput;
        bool running;                                       /**< This variable triggers a shutdown total once set to False. */

        /** Ctor initializes the status of the car to be running
         *
         */
        UserData() : running(true) {}
    };

    UserControl();
    ~UserControl();

    /** Initialize the connection to the keyboard.
     *
     * Start listening and log information form keystrokes
     * @return a thread identifier
     */
    std::thread start();

    /** Monitor user input for shutdown.
     *
     * @Note Any key stop the execution at the moment
     */
    void detectUserInput();

    /*!
       \brief Setup the UserData struct according to the detected user input
       \param
    */
    void transmitUserInput(UserInput direction);

    /*!
       \brief Parse user input as a string and convert it to an enum
       \param "Param description"
       \pre "Pre-conditions"
       \post "Post-conditions"
       \return Return UserInput enum
    */
    UserInput hashit(std::string const& inString);

    /*!
       \brief Display every possible input that have an effect
    */
    void displayInputInformation();

    UserData    mUserData;  /**< Struct keeping track of the user interaction */
    char        mStroke;    /**< keystroke from user input; */
};

#endif //END: USER_CONTROL_H
