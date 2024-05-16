#!/bin/bash

BLUE='\e[1;34m'
GREEN='\e[1;33m'
NC='\e[0m'

function test_map(){
	printf "${GREEN}Testing map: ${BLUE}$1${NC}\n"
	echo '['
	valgrind --quiet ./cub3D_bonus $1
	echo ']'
}

make fclean
make bonus
test_map maps/wrong_maps/doublecolor.cub
test_map maps/wrong_maps/doubletexture.cub
test_map maps/wrong_maps/empty.cub
test_map maps/wrong_maps/missingcolor.cub
mv assets/ assets_missing/
test_map maps/wrong_maps/missingfiles.cub
mv assets_missing/ assets/
test_map maps/wrong_maps/missingmap.cub
test_map maps/wrong_maps/missingspawn.cub
test_map maps/wrong_maps/missingtexture.cub
test_map maps/wrong_maps/notclosed.cub
test_map maps/wrong_maps/space3wrong.cub
test_map maps/wrong_maps/toomanyspawn.cub
test_map maps/wrong_maps/unordered.cub
test_map maps/wrong_maps/wrongchar.cub
test_map maps/wrong_maps/wrongextension.ber
test_map maps/wrong_maps/wrongrgb.cub
test_map maps/wrong_maps/wrongrgb2.cub

