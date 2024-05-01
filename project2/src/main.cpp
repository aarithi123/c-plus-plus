#include <iostream>
#include <strings.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Tasks.h"


using namespace std;

bool fileCheck (string fileName) {
    bool tagFile = false;
    if ( fileName.find(".tga") != std::string::npos) {   // file does not exist
        tagFile = true;
    }
    return tagFile;
}

bool fileExists (string fileName) {
    bool filePresent = false;
    fstream file;
    file.open(fileName.c_str());
    if ( file.is_open()) {   // file does not exist
        filePresent = true;
    }
    return filePresent;
}

bool isNumeric (string numString) {
    /*
    char minus = '-';
    if (numString.front() == minus) {
        numString.erase(numString.begin());
    }
     */

    for (int i = 0; i < numString.length(); i++) {
        if (isdigit(numString[i]) == false) {
            return false;
        }
    }
    return true;
}

bool negativeNumeric (string numString) {

    char minus = '-';
    if (numString.front() == minus) {
        numString.erase(numString.begin());
    }

    for (int i = 0; i < numString.length(); i++) {
        if (isdigit(numString[i]) == false) {
            return false;
        }
    }
    return true;
}

int main( int argc, char *argv[])     // number of string in argv
{
    Tasks task;
    vector<string> arguments;
    arguments = vector<string>(argv, argv + argc);
    string method;
    int argCount = 0;

    string outputFile, firstFile, secondFile, thirdFile, fourthFile;
    string number;

    /*
    for (int i=0; i<arguments.size(); i++) {
        cout << i << " -> " << arguments[i] << endl;
        cout << endl;
    }
     */

    if (argc < 2) {
        cout << "Project 2: Image Processing, Spring 2024\n\n";
        cout << "Usage:\n\t./project2.out [output] [firstImage] [method] [...]\n";
        return 0;
    } else if (  arguments[1] == "--help" ) {
        cout << "Project 2: Image Processing, Spring 2024\n\n";
        cout << "Usage:\n\t./project2.out [output] [firstImage] [method] [...]\n";
        return 0;
    }

    //"Project 2: Image Processing, Fall 2023\n\n"
    //"Usage:\n\t./project2.out [output] [firstImage] [method] [...]\n"

    // validate output fileName
    if (!fileCheck(arguments[1])) {                  // does not end with .tga
        cout << "Invalid file name." << endl;
        return 0;
    } else {
        outputFile = arguments[1];                              // outputFile
    }

    // validate first target file
    if (argc < 3) {                             // first source file not passed
        cout << "Invalid file name." << endl;
        return 0;
    }

    if (!fileCheck(arguments[2])) {  // arguments[2} .tga file?
        cout << "Invalid file name." << endl;
        return 0;
    }

    if (!fileExists(arguments[2])) {    // file does not exist
        cout << "File does not exist." << endl;
        return 0;
    } else {
        firstFile = arguments[2];
    }

    Image trackingImage = task.readFile(firstFile);
    Image firstImage;
    Image secondImage;

    if (argc < 4) {                             // first source file not passed
        cout << "Invalid method name." << endl;
        return 0;
    }

    for (int j = 3; j < argc; j++) {
        cout << arguments[j] << endl;

        method = arguments[j];

        if (method == "onlyred") {                 //no additional arguments
            cout << "onlyred" << endl;
            vector<Image> image1 = task.onlyColor(trackingImage);
            trackingImage = image1.at(2);
            task.writeFile(outputFile, trackingImage);
        } else if (method == "onlygreen") {
            cout << "onlygreen" << endl;
            vector<Image> image2 = task.onlyColor(trackingImage);
            trackingImage = image2.at(1);
            task.writeFile(outputFile, trackingImage);
        } else if (method == "onlyblue") {
            cout << "onlyblue" << endl;
            vector<Image> image3 = task.onlyColor(trackingImage);
            trackingImage = image3.at(0);
            task.writeFile(outputFile, trackingImage);
        } else if (method == "flip") {
            cout << "flip" << endl;
            trackingImage = task.flip(trackingImage);
            task.writeFile(outputFile, trackingImage);

        } else if (method == "addred" || method == "addgreen" || method == "addblue" || \
                   method == "scalered" || method == "scalegreen" || method == "scaleblue") {  // one number argument
            if (argc < (j + 2)) {
                cout << "Missing argument." << endl;
                return 0;
            } else {
                j = j + 1;

                if (method == "addblue" || method == "addgreen" || method == "addred") {
                    if (negativeNumeric(arguments[j])) {
                        number = arguments[j];
                    } else {
                        cout << "Invalid argument, expected number." << endl;
                        return 0;
                    }
                } else {
                    if (isNumeric(arguments[j])) {
                        number = arguments[j];
                    } else {
                        cout << "Invalid argument, expected number." << endl;
                        return 0;
                    }

                }

            }
            if (method == "addred") {
                cout << "addred" << endl;
                trackingImage = task.addColor(trackingImage, 0, 0, stoi(number));
                task.writeFile(outputFile, trackingImage);
            } else if (method == "addgreen") {
                cout << "addgreen" << endl;
                trackingImage = task.addColor(trackingImage, 0, stoi(number), 0);
                task.writeFile(outputFile, trackingImage);
            } else if (method == "addblue") {
                cout << "addblue" << endl;
                trackingImage = task.addColor(trackingImage, stoi(number), 0, 0);
                task.writeFile(outputFile, trackingImage);
            } else if (method == "scalered") {
                cout << "scalered" << endl;
                trackingImage = task.scale(trackingImage, false, 0.0, false, 0.0, true, stoi(number));
                task.writeFile(outputFile, trackingImage);
            } else if (method == "scalegreen") {
                cout << "scalegreen" << endl;
                trackingImage = task.scale(trackingImage, false,0.0,true, stoi(number), false, 0.0);
                task.writeFile(outputFile, trackingImage);
            } else if (method == "scaleblue") {
                cout << "scaleblue" << endl;
                trackingImage = task.scale(trackingImage, true,stoi(number),false, 0.0, false, 0.0);
                task.writeFile(outputFile, trackingImage);
            }
            // one number argument ends

        //} else if (method == "multiply" || method == "subtract" || method == "overlay") {   // one image argument
        } else if (method == "multiply" || method == "subtract" || method == "overlay" || method == "screen") {   // one image argument
                if (argc < (j + 2)) {                             // first target file not passed
                    cout << "Missing argument." << endl;
                    return 0;
                }
                j = j + 1;
                if (!fileCheck(arguments[j])) {  // arguments[2} .tga file?
                    cout << "Invalid argument, invalid file name." << endl;
                    return 0;
                }
                if (!fileExists(arguments[j])) {    // file does not exist
                    cout << "Invalid argument, file does not exist." << endl;
                    return 0;
                } else {
                    firstImage = task.readFile(arguments[j]);
                }

                if (method == "multiply") {
                    cout << "multiply" << endl;
                    trackingImage = task.multiply(trackingImage, firstImage);
                    task.writeFile(outputFile, trackingImage);
                } else if (method == "subtract") {
                    cout << "subtract" << endl;
                    trackingImage = task.subtract(trackingImage, firstImage);
                    task.writeFile(outputFile, trackingImage);
                } else if (method == "overlay") {
                    cout << "overlay" << endl;
                    trackingImage = task.overlay(trackingImage, firstImage);
                    task.writeFile(outputFile, trackingImage);
                } else if (method == "screen") {
                    cout << "screen" << endl;
                    trackingImage = task.screen(trackingImage, firstImage);
                    task.writeFile(outputFile, trackingImage);
                }

                // one image argument ends

        //} else if (method == "combine" || method == "screen") {   // two image argument
        } else if (method == "combine") {   // two image argument
            if (argc < (j + 2)) {                             // first target file not passed
                cout << "Missing argument." << endl;
                return 0;
            }
            j = j + 1;
            if (!fileCheck(arguments[j])) {  // arguments[2} .tga file?
                cout << "Invalid argument, invalid file name." << endl;
                return 0;
            }
            if (!fileExists(arguments[j])) {    // file does not exist
                cout << "Invalid argument, file does not exist." << endl;
                return 0;
            } else {
                firstImage = task.readFile(arguments[j]);
            }

            if (argc < (j + 2)) {                             // first target file not passed
                cout << "Missing argument." << endl;
                return 0;
            }
            j = j + 1;
            if (!fileCheck(arguments[j])) {  // arguments[2} .tga file?
                cout << "Invalid argument, invalid file name." << endl;
                return 0;
            }
            if (!fileExists(arguments[j])) {    // file does not exist
                cout << "Invalid argument, file does not exist." << endl;
                return 0;
            } else {
                secondImage = task.readFile(arguments[j]);
            }

            if (method == "combine") {
                cout << "combine" << endl;
                //trackingImage = task.combine(trackingImage, firstImage, secondImage);
                trackingImage = task.combine(secondImage, firstImage, trackingImage);
                task.writeFile(outputFile, trackingImage);
            /*
            } else if (method == "screen") {
                cout << "screen" << endl;
                trackingImage = task.screen(trackingImage, firstImage, secondImage);
                task.writeFile(outputFile, trackingImage);
            }
                 */
            }

        } else {
            cout << "Invalid method name." << endl;
            return 0;
        }
    }
    return 0;
}
