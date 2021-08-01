all: install msg

install:
        @sudo cp ceval.h /usr/local/include
        @sudo cp -fr core /usr/local/include
msg:
        @echo "Use #include<ceval.h> directive to include the header file in your project"
