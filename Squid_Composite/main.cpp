#include "main.hpp"

int main() {
	CxImage* images[3] = {
		new CxImage,
		new CxImage,
		new CxImage
	};

	const char* files[3] = {
		"squid_body.png",
		"squid_head.png",
		"squid_points.png"
	};
	
	if (!loadFiles(files, images)) {
		system("PAUSE");
		return -1;
	}

	std::cout << "Files are opened Successfully. Converting Ongoing..." << std::endl;
	
	processImages(images);

	std::cout << "Converting Done..! Saved as Result.png." << std::endl;

	for (int i = 0; i < 3; i++) {
		delete(images[i]);
	}

	system("PAUSE");
	return 0;
}

bool loadFiles(const char** files, CxImage** images) {
	for(int i = 0; i < 3; i++) {
		std::string fileName = std::string(files[i]);
		std::wstring fileNameByte = std::wstring(fileName.begin(), fileName.end());
		if(!images[i]->Load(fileNameByte.c_str(), CXIMAGE_FORMAT_PNG)) {
			std::cout << "Failed to load image: " << fileName << std::endl;
			return false;
		}
	}

	return true;
}

void processImages(CxImage** images) {
	DWORD width = images[0]->GetWidth();
	DWORD height = images[0]->GetHeight();
	RGBQUAD newColor;

	for (DWORD y = 0; y < height; y++) {
		for (DWORD x = 0; x < width; x++) {
			RGBQUAD firstColor = images[0]->GetPixelColor(x, y);
			RGBQUAD secondColor = images[1]->GetPixelColor(x, y);
			RGBQUAD thirdColor = images[2]->GetPixelColor(x, y);

			float red = firstColor.rgbRed + secondColor.rgbRed - thirdColor.rgbRed;
			float green = firstColor.rgbGreen + secondColor.rgbGreen - thirdColor.rgbGreen;
			float blue = firstColor.rgbBlue + secondColor.rgbBlue - thirdColor.rgbBlue;

			newColor.rgbRed = red > 255 ? 255 : (red < 0 ? 0 : red);
			newColor.rgbGreen = green > 255 ? 255 : (green < 0 ? 0 : green);
			newColor.rgbBlue = blue > 255 ? 255 : (blue < 0 ? 0 : blue);

			images[0]->SetPixelColor(x, y, newColor);
		}
	}

	std::string fileName = std::string("Result.png");
	std::wstring fileNameByte = std::wstring(fileName.begin(), fileName.end());
	images[0]->Save(fileNameByte.c_str(), CXIMAGE_FORMAT_PNG);
}