INCLUDE="../../../extern/bgfx.cmake/bgfx/src"
SHADERC="../../../build/extern/bgfx.cmake/shaderc"

FILE=$1
TYPE=$2
PROFILE=$3

$SHADERC -f $FILE -o ${FILE%.*}.h --bin2c -i $INCLUDE -p $PROFILE --type $TYPE
