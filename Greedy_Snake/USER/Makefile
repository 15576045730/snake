#最终的目标名
TARGET := ../BIN/main

#指定一个编译器
CC := arm-linux-g++

# 添加 C++14 标准支持
CXXFLAGS := -std=c++14 

#找到我们的源文件夹 .cpp文件
#在当前路径下面找所有的.cpp文件
#CFILES := $(wildcard ../CODE/SRC/*.cpp ./*.cpp)
CFILES := $(wildcard ../CODE/SRC/*.cpp)
CFILES += $(wildcard ./*.cpp)

#去掉路径
#../CODE/SRC/Bitmap.cpp  ../CODE/SRC/Color.cpp ../CODE/SRC/Point.cpp ./main.cpp
#./main.cpp
CFILES := $(notdir $(CFILES))


#中间文件的名字  做模式替换
#将所有的.cpp模式替换为.o
#到这里为止 没有.o文件生成
#OBJS := $(patsubst %.cpp,../OBJ/%.o,$(CFILES))
#../CODE/SRC/Bitmap.cpp  ../CODE/SRC/Color.cpp ../CODE/SRC/Point.cpp ./main.cpp
OBJS := $(patsubst %.cpp,../OBJ/%.o,$(CFILES))
#OBJS += $(patsubst ./%.cpp,../OBJ/%.o,$(CFILESSS))
#../OBJ/Bitmap.o ../OBJ/Color.o ../OBJ/Point.o ./main.cpp

#头文件搜索路径  如果你的头文件不是放在这些路径下面的 请添加进来
#建议用这些
INCPATH := -I../CODE/INC
INCPATH += -I./
INCPATH += -I../LIB/inc

#库的搜索路径
LIBPATH := -L../LIB/lib

#库的名字
LIBFILES := -lpthread # 添加 pthread 库

#tftp 路径
TFTPPATH := ~/tftpboot


#最终的可执行文件依赖.o文件
#将所有的.o文件进行链接
$(TARGET): $(OBJS)
	$(CC) $(CXXFLAGS) $^ -o $@ $(INCPATH) $(LIBPATH) $(LIBFILES)
#	cp $(TARGET) $(TFTPPATH) 


#上面的OBJS只有名字没有文件  是不是要生成
../OBJ/%.o : ../CODE/SRC/%.cpp | ../OBJ
	@echo Compiling $<
	$(CC) $(CXXFLAGS) -c $< -o $@ $(INCPATH)

../OBJ/%.o : ./%.cpp | ../OBJ
	@echo Compiling $<
	$(CC) $(CXXFLAGS) -c $< -o $@ $(INCPATH)	

print:
	@echo $(CFILES)
	@echo -------
	@echo $(OBJS)


#加标记 你make clean就来这里执行
clean:
	rm -rf $(OBJS) $(TARGET)






