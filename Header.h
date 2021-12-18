#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <Windows.h>
#include <direct.h>
#include <opencv2/opencv.hpp>

using namespace std;


class ImageHandler {

private:
	string empty_string = "";

public:

	cv::Mat read_image(string path) {
		return cv::imread(path, cv::IMREAD_COLOR);
	}

	cv::Mat downscale(cv::Mat image, float scaleFactor = 0.5) {
		cv::Mat disp_image;
		cv::resize(image, disp_image, cv::Size(), scaleFactor, scaleFactor, cv::INTER_AREA);
		return disp_image;
	}

	void show_image(cv::Mat image, string title = "") {
		if (title.empty() != 0){
			cv::imshow("Image", image);
		}
		else {
			cv::imshow(title, image);
		}
		cv::waitKey(0);
	}

	void save_image(string path, cv::Mat image) {
		cv::imwrite(path, image);
	}

};


class ImageProcessor {

public:
	cv::Mat proc_image;

	void gauss_blur(cv::Mat image, int kernel_size) {
		cv::GaussianBlur(image, proc_image, cv::Size(kernel_size, kernel_size), 0);
	}
};