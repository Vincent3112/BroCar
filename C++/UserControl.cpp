#include "UserControl.h"

UserControl::UserControl()
    : mStroke('0')
{
    printf("\t\n\n\n");
    printf("\t\t    _/_/_/_/  \n");
    printf("\t\t   _/    _/   \n");
    printf("\t\t  _/_/_/      \n");
    printf("\t\t _/    _/     \n");
    printf("\t\t_/_/_/_/  ROCAR\n\n\n");

    printf("\t\t\t/////////////////////////////////////////////\n");
    printf("\t\t\t// Programme Principal BroCar Raspberry Pi //\n");
    printf("\t\t\t// Bibilotheques : OpenCV 		     //\n");
    printf("\t\t\t// Version: 1.0				      //\n");
    printf("\t\t\t// Auteurs : 		                  //\n");
    printf("\t\t\t/////////////////////////////////////////////\n\n");

}

UserControl::~UserControl(){

}

std::thread UserControl::start(){
    return std::thread([=] { detectUserInput(); });
}

UserControl::UserInput UserControl::hashit(std::string const& inString) {
    std::cout << "in hashit : " << inString << '\n';
    if (inString == "f") return Forward;
    if (inString == "l") return Left;
    if (inString == "b") return Backward;
    if (inString == "r") return Right;
    if (inString == "s") return Stop;
    if (inString == "x") return Exit;
    return Undefined;
}

void UserControl::detectUserInput(){
    displayInputInformation();

    do
    {
        std::string line;
        //std::getline(std::cin, line);
        std::cin >> line;
        std::cout << line << '\n';
        //usleep(250*1000);
        //scanf(" %c\n", &mStroke);
        //mStroke = getchar();
        //std::cout << mStroke;
        switch(hashit(line))
        {
            case Forward: // Forward
            case 65 :// key up
            transmitUserInput(Forward);
            break;

            case Left: // Left
            case 68 :// key left
            transmitUserInput(Left);
            break;

            case Backward: // Backward
            case 66 :// key down
            transmitUserInput(Backward);
            break;

            case Right:// Right
            case 67 :// key right
            transmitUserInput(Right);
            break;

            case Stop: // Stop left right
            case 32:// space
            transmitUserInput(Stop);
            break;
            /*
            case str2int('q') : // Stop front back
            case '\n':
            transmitUserInput(Stop);
            break;
            */
            case Exit: //Fin
            transmitUserInput(Stop);
            mUserData.running = false;
            break;
/*
            case str2int('w'): //Sensor
            //@todo
            break;

            case str2int('g'): // GPS
            //@todo
            break;*/
            default:
            std::cout << "Nothing detected" << '\n';
            std::cout << line << '\n';
            break;
        }// SWITCH
        //printf("%c", mStroke);
    } while (mUserData.running);
}

void UserControl::transmitUserInput(UserInput direction){
    mUserData.direction = direction;
    printf("%u", direction);
    //@todo Send to Controller through Communication maybe.
}

void UserControl::displayInputInformation(){
    printf("Front = f \n");
	printf("Left = l \n");
	printf("Back = b \n");
	printf("Right = r \n");
	printf("Stop Left & Right = s ou espace \n");
	printf("Stop Front & back = s ou enter \n");
    printf("Exit program = x \n");
}
