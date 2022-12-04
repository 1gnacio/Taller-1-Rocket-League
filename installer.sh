green=`tput setaf 2`
bold=`tput bold`
reset=`tput sgr0`

echo "${green}${bold}\n********************************************************************************${reset}"
echo "${green}${bold}*****************************INSTALADOR*****************************************${reset}"
echo "${green}${bold}********************************************************************************${reset}"

echo "${green}\n~INSTALACIÓN DE DEPENDENCIAS C++~\n${reset}"

echo "${green}Instalando 'clang'...${reset}"
sudo apt-get install clang -y 

echo "${green}Instalando 'make'...${reset}"
sudo apt-get install make -y 

echo "${green}Instalando 'cmake'...${reset}"
sudo apt-get install cmake -y

echo "${green}Instalando 'build-essential'...${reset}"
sudo apt-get install build-essential -y

echo "${green}\n~INSTALACIÓN DE DEPENDENCIAS: QT5~\n${reset}"

echo "${green}Instalando 'qt5'...${reset}"
sudo apt-get install qt5-default -y

echo "${green}Instalando 'libqt5multimedia5-plugnins'...${reset}"
sudo apt-get install libqt5multimedia5-plugins -y

echo "${green}Instalando 'libqt5multimedia5-plugnins'...${reset}"
sudo apt-get install qtmultimedia5-dev -y

echo "\n${green}~INSTALACIÓN DE DEPENDENCIAS: YAML-CPP~\n${reset}"

sudo apt-get install libyaml-cpp-dev -y
echo "${green}Instalando 'libyaml-cpp-dev'...${reset}"

echo "${green}\n~INSTALACIÓN DE DEPENDENCIAS: SDL2~\n${reset}"

echo "${green}Instalando 'libsdl2-dev'...${reset}"
sudo apt-get install libsdl2-dev -y

echo "${green}Instalando 'libsdl2-image-dev'...${reset}"
sudo apt-get install libsdl2-image-dev -y

echo "${green}Instalando 'libsdl2-gfx-dev'...${reset}"
sudo apt-get install libsdl2-gfx-dev -y

echo "${green}Instalando 'libsdl2-mixer-dev'...${reset}"
sudo apt-get install libsdl2-mixer-dev -y

echo "${green}Instalando 'libsdl2-ttf-dev'...${reset}"
sudo apt-get install libsdl2-ttf-dev -y

echo "${green}\n~BUILD DEL JUEGO~\n${reset}"
mkdir build
cd build
cmake ..
make -j4

echo "${green}\n~INSTALANDO ROCKET LEAGUE~\n${reset}"
sudo make install -j 10
echo "${green} ROCKET LEAGUE instalado completamente ${reset}"
