CFLAGS = -W -Wall -pedantic

SOURCE_DIR = src
OBJ_DIR = obj
DOC_DIR = doc

SRC= $(wildcard $(SOURCE_DIR)/*.c) 

OBJ_tempo= $(notdir $(SRC:%.c=%.o))
OBJ = $(OBJ_tempo:%.o=$(OBJ_DIR)/%.o)

DEP = -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -I/usr/local/include -L/usr/local/lib  


all: init compil

init:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(DOC_DIR)	

compil: $(OBJ)			
	@g++ -o $@ $^ $(DEP)

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c
	@g++ -o $@ -c $< $(CFLAGS) $(DEP)


clean:
	@rm -rf $(OBJ_DIR)/*.o

total_clean: clean
	@rm -rf $(EXEC)
