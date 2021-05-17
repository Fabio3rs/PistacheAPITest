SRC_DIR := ./src
OBJ_DIR := ./build/obj
CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES :=  $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CPP_FILES))
INCLUDES := -I../cereal/include
LDFLAGS := -lpthread -lpistache -lmysqlcppconn -lcurl
CPPFLAGS := -std=c++17 -O3 $(INCLUDES) -g -pipe
CFLAGS := -O3 -g -pipe
CXXFLAGS := -O3 -g -std=c++17 

noterest: $(OBJ_FILES)
	g++ -o $@ $(OBJ_DIR)/*.o $(LDFLAGS) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

