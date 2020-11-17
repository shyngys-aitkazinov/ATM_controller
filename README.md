# ATM controller
Simple ATM controller

I developed the project on ubuntu.

Requirements:
    gcc
    c++17
    cmake
    libncurses5-dev libncursesw5-dev

Some helpful terminal commands to install requirements to run the project:
    sudo apt update
    sudo apt install build-essential
    sudo apt install cmake
    sudo apt-get install libncurses5-dev libncursesw5-dev

git clone the project

cd <project name>
mkdir build && cd build
cmake ..
make
./bin/atm_controller
