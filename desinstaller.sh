#!/usr/bash

green=`tput setaf 2`
bold=`tput bold`
reset=`tput sgr0`

echo "${green}${bold}\n********************************************************************************${reset}"
echo "${green}${bold}*****************************DESINSTALADOR*****************************************${reset}"
echo "${green}${bold}********************************************************************************${reset}"
# Loop through arguments and process them
for arg in "$@"
do
    case $arg in

        --qt)
        shift
        echo "${green}${bold}Desinstalando las dependencias de qt...${reset}"

        echo "${green}Desinstalando 'qt5'...${reset}"
        sudo apt-get remove qt5-default -y

        sudo apt-get remove qtbase5-dev

        sudo apt-get remove qtdeclarative5-dev

        echo "${green}Desinstalando 'libqt5multimedia5-plugins'...${reset}"
        sudo apt-get remove libqt5multimedia5-plugins -y
        
        ;;



        --yaml)
        shift
        echo "${green}${bold}Desinstalando las dependencias de yaml-cpp...${reset}"

        sudo apt-get remove libyaml-cpp-dev -y

        ;;



        --sdl)
        shift
        echo "${green}${bold}Desinstalando las dependencias de sdl2...${reset}"

        echo "${green}Desinstalando 'libgbm1'...${reset}"
        sudo apt-get remove libgbm1

        echo "${green}Desinstalando 'libegl1-mesa0'...${reset}"
        sudo apt-get remove libegl1-mesa -y

        echo "${green}Desinstalando 'libsdl2-dev'...${reset}"
        sudo apt-get remove libsdl2-dev -y

        echo "${green}Desinstalando 'libsdl2-image-dev'...${reset}"
        sudo apt-get remove libsdl2-image-dev -y

        echo "${green}Desinstalando 'libsdl2-gfx-dev'...${reset}"
        sudo apt-get remove libsdl2-gfx-dev -y

        echo "${green}Desinstalando 'libsdl2-mixer-dev'...${reset}"
        sudo apt-get remove libsdl2-mixer-dev -y

        echo "${green}Desinstalando 'libsdl2-image1.2-dev'...${reset}"
        sudo apt-get remove libsdl2-image1.2-dev
        
        ;;



        --cpp)
        shift
        echo "${green}${bold}Desinstalando las dependencias cpp...${reset}"

        echo "${green}Desinstalando 'clang'...${reset}"
        sudo apt-get remove clang -y 

        echo "${green}Desinstalando 'make'...${reset}"
        sudo apt-get remove make -y 

        echo "${green}Desinstalando 'cmake'...${reset}"
        sudo apt-get remove cmake -y

        echo "${green}Desinstalando 'build-essential'...${reset}"
        sudo apt-get remove build-essential -y

        ;;


        --repo)
        shift
        echo "${green}${bold}Borrando el repositorio...${reset}"
        cd ..
        rm Taller-1-Rocket-League
        ;;

	--game)
        shift
        echo "${green}${bold}Desinstalando ROCKET LEAGUE...${reset}"
	sudo rm -rf /var/game
	sudo rm /usr/bin/game_client
	sudo rm /usr/bin/game_server
	sudo rm /usr/bin/lobby
        ;;

	--box2d)
        shift
        echo "${green}${bold}Desinstalando BOX2D...${reset}"
	sudo rm -rf /usr/local/include/box2d
	sudo rm -rf /usr/local/lib/cmake/box2d/
	sudo rm /usr/local/lib/libbox2d.a
	;;
        --all)
        shift

        echo "${green}Desinstalando 'qt5'...${reset}"
        sudo apt-get remove qt5-default -y

        sudo apt-get remove qtbase5-dev

        sudo apt-get remove qtdeclarative5-dev

        echo "${green}Desinstalando 'libqt5multimedia5-plugins'...${reset}"
        sudo apt-get remove libqt5multimedia5-plugins -y
        
        echo "${green}Desinstalando las dependencias de yaml-cpp...${reset}"
        sudo apt-get remove libyaml-cpp-dev -y

        echo "${green}Desinstalando 'libsdl2-dev'...${reset}"
        sudo apt-get remove libsdl2-dev -y

        echo "${green}Desinstalando 'libsdl2-image-dev'...${reset}"
        sudo apt-get remove libsdl2-image-dev -y

        echo "${green}Desinstalando 'libsdl2-gfx-dev'...${reset}"
        sudo apt-get remove libsdl2-gfx-dev -y

        echo "${green}Desinstalando 'libsdl2-mixer-dev'...${reset}"
        sudo apt-get remove libsdl2-mixer-dev -y
        
        echo "${green}Desinstalando 'libsdl2-ttf-dev'...${reset}"
        sudo apt-get remove libsdl2-ttf-dev -y

        echo "${green}Desinstalando 'libsdl2-image1.2-dev'...${reset}"
        sudo apt-get remove libsdl2-image1.2-dev

        echo "${green}Desinstalando 'clang'...${reset}"
        sudo apt-get remove clang -y 

        echo "${green}Desinstalando 'make'...${reset}"
        sudo apt-get remove make -y 

        echo "${green}Desinstalando 'cmake'...${reset}"
        sudo apt-get remove cmake -y

        echo "${green}Desinstalando 'build-essential'...${reset}"
        sudo apt-get remove build-essential -y

        cd ..
        rmdir Taller-1-Rocket-League

        echo "${green}${bold}Desinstalando ROCKET_LEAGUE...${reset}"
	sudo rm -rf /var/game
	sudo rm /usr/bin/game_client
	sudo rm /usr/bin/game_server
	sudo rm /usr/bin/lobby

        echo "${green}${bold}Desinstalando BOX2D...${reset}"
	sudo rm -rf /usr/local/include/box2d
	sudo rm -rf /usr/local/lib/cmake/box2d/
	sudo rm /usr/local/lib/libbox2d.a

        ;;

    esac
done
