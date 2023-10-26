#include "main.hpp"

int main(int argc, const char** argv) {
	CxImage* images[3] = {
		new CxImage,
		new CxImage,
		new CxImage
	};

	const char* files[4] = {
		"",
		"squid_body.png",
		"squid_head.png",
		"squid_points.png"
	};
	
	if (!loadFiles((argc == 4 ? argv : files), images)) {
		return -1;
	}
	
	processImages(images);

	for (int i = 0; i < 3; i++) {
		free(images[i]);
	}

	return 0;
}

bool loadFiles(const char** files, CxImage** images) {
	for(int i = 0; i < 3; i++) {
		std::string fileName = std::string(files[i + 1]);
		std::wstring fileNameByte = std::wstring(fileName.begin(), fileName.end());
		if(!images[i]->Load(fileNameByte.c_str(), CXIMAGE_FORMAT_PNG)) {
			std::cout << "Failed to load image from: " << fileName << ". Error: " << images[i]->GetLastError() << "\n";  // GetLastError의 결과를 출력
			return false;
		}
	}

	return (images[0]->IsValid() && images[1]->IsValid() && images[2]->IsValid());
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