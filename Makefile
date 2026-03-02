ifeq ($(OS),Windows_NT)
    TARGET   = main.exe
    RM       = del /f
else
    TARGET   = main
    RM       = rm -f
endif

CXXFLAGS = -O3 -flto -funroll-loops -fno-math-errno -fno-trapping-math -Wall -Wextra

.PHONY: run clean
.DEFAULT_GOAL := run

run: $(TARGET)
	./$(TARGET)

$(TARGET): main.cpp
	g++ main.cpp $(CXXFLAGS) -o $(TARGET) $(LIBS)

clean:
	$(RM) $(TARGET)