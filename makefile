inc=-I "./3rdparty/include"
lin=-L "./3rdparty/lib"
linker=-lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -l:nncam.lib  -l:libopencv_core455.dll.a -l:libopencv_imgcodecs455.dll.a -l:libopencv_imgproc455.dll.a -l:libopencv_photo455.dll.a

all: main button maths shapes TextBox Line lodepng controlPanel errorMessage
	g++ -g object/main object/button object/maths object/shapes object/TextBox object/Line object/lodepng object/ControlPanel object/errorMessage -o build/app $(lin) $(linker)
main: ./main.cpp globalVariables.hpp
	g++ $(inc) -c main.cpp -o object/main
button: ./gui/button.cpp ./gui/button.hpp
	g++ $(inc) -c gui/button.cpp -o object/button
maths: ./gui/maths.cpp ./gui/maths.hpp
	g++ $(inc) -c gui/maths.cpp -o object/maths
shapes: ./gui/shapes.cpp ./gui/shapes.hpp
	g++ $(inc) -c gui/shapes.cpp -o object/shapes
TextBox: ./gui/TextBox.cpp ./gui/TextBox.hpp
	g++ $(inc) -c gui/TextBox.cpp -o object/TextBox
Line: ./Line.cpp ./Line.hpp
	g++ $(inc) -c Line.cpp -o object/Line
lodepng: ./lodepng.cpp ./lodepng.h
	g++ $(inc) -c lodepng.cpp -o object/lodepng
controlPanel: ./ControlPanel.cpp ./ControlPanel.hpp
	g++ $(inc) -c ControlPanel.cpp -o object/ControlPanel
errorMessage: ./errorMessage.cpp ./errorMessage.hpp
	g++ $(inc) -c errorMessage.cpp -o object/errorMessage