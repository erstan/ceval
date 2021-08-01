all: copy_all msg

copy_all:
        @cp ceval.h /usr/local/include || sudo cp ceval.h /usr/local/include
        @cp -fr core /usr/local/include || sudo cp -fr core /usr/local/include
msg:
        @echo "Include the library using #include<ceval.h> directive\n"
