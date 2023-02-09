#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

int main() 
{
	auto start = std::chrono::high_resolution_clock::now();

	std::string htmlStart = "<!DOCTYPE html>\n<html>\n<head>\n<title>Image</title>\n <link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">\n</head>\n<body>\n <h1>Image.</h1>\n";
	std::string htmlEnd = "</body>\n</html>";
	int width, height, nrChannels;
	unsigned char* image = stbi_load("C:/Users/a/source/repos/ImageToCSS/x64/Debug/image.png",&width,&height,&nrChannels,0);

	//reserve space to increase speed
	std::string htmlData;
	//htmlData.reserve(150 + (width * height * 30));
	std::string cssData;
	cssData.reserve(width* height*170);

	
	htmlData.append(htmlStart);

	int index = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			//get pixel RGB values
			unsigned bytePerPixel = nrChannels;
			unsigned char* pixelOffset = image + (j + width * i) * bytePerPixel;
			unsigned char r = pixelOffset[0];
			unsigned char g = pixelOffset[1];
			unsigned char b = pixelOffset[2];
			unsigned char a = nrChannels >= 4 ? pixelOffset[3] : 0xff;


			cssData.append(".a" + std::to_string(index) + " {\n" +
				"position: absolute;\n" +
				"left: " + std::to_string(j) + "px;\n" +
				"top:" + std::to_string(i) + "px\n;" +
				"width: 1px;\n" +
				"height: 1px;\n" +
				"background: rgb(" + std::to_string(r) + "," + std::to_string(g) + "," + std::to_string(b) + ");\n" +
				"}\n");

			htmlData.append("<div class=\"a" + std::to_string(index) + "\"></div>\n");
			index++;
		}
	}
	htmlData.append(htmlEnd);

	std::ofstream htmlFile("C:/Users/a/source/repos/ImageToCSS/x64/Debug/index.html");
	std::ofstream cssFile("C:/Users/a/source/repos/ImageToCSS/x64/Debug/style.css");

	
	htmlFile << htmlData;
	cssFile << cssData;
	//htmlFile.write((char*)&htmlData, sizeof(std::string));

	//cssFile.write((char*)&cssData, sizeof(std::string));
	
	htmlFile.flush();
	cssFile.flush();
	htmlFile.close();
	cssFile.close();

	auto finish = std::chrono::high_resolution_clock::now();
	auto microseconds = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
	std::cout << microseconds.count() << "ms\n";

	return 0;
}