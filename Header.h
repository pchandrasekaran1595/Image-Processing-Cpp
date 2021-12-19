#pragma once

#include "iostream"
#include "string"
#include "Windows.h"
#include "direct.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

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

	cv::Mat gauss_blur(cv::Mat image, int kernel_size) {
		cv::Mat proc_image =  cv::Mat::zeros(image.size(), image.type());
		cv::GaussianBlur(image, proc_image, cv::Size(kernel_size, kernel_size), 0);
		return proc_image;
	}

	cv::Mat average_blur(cv::Mat image, int kernel_size) {
		cv::Mat proc_image = cv::Mat::zeros(image.size(), image.type());
		cv::blur(image, proc_image, cv::Size(kernel_size, kernel_size));
		return proc_image;
	}

	cv::Mat median_blur(cv::Mat image, int kernel_size) {
		cv::Mat proc_image = cv::Mat::zeros(image.size(), image.type());
		cv::medianBlur(image, proc_image, kernel_size);
		return proc_image;
	}

	cv::Mat gammaAdjust(cv::Mat image, double alpha) {
		cv::Mat proc_image = cv::Mat::zeros(image.size(), image.type());
		for (int y = 0; y < image.rows; y++) {
			for (int x = 0; x < image.cols; x++) {
				for (int c = 0; c < image.channels(); c++) {
					proc_image.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>(image.at<cv::Vec3b>(y, x)[c] * alpha - 100);
				}
			}
		}
		return proc_image;
	}

	cv::Mat linearContrastAdjust(cv::Mat image, double alpha) {
		cv::Mat proc_image = cv::Mat::zeros(image.size(), image.type());
		for (int y = 0; y < image.rows; y++) {
			for (int x = 0; x < image.cols; x++) {
				for (int c = 0; c < image.channels(); c++) {
					proc_image.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>(image.at<cv::Vec3b>(y, x)[c] + alpha);
				}
			}
		}
		return proc_image;
	}

	cv::Mat adaptiveEqualization(cv::Mat image, double clipLimit, int tileGridSize) {
		cv::Mat proc_image = cv::Mat::zeros(image.size(), image.type());

		std::vector<cv::Mat> proc_bgr_split(3);
		cv::split(proc_image, proc_bgr_split);

		std::vector<cv::Mat> bgr_split(3);
		cv::split(image, bgr_split);

		cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE(clipLimit, cv::Size(tileGridSize, tileGridSize));
		for (int c = 0; c < image.channels(); c++) 
			clahe->apply(bgr_split[c], proc_bgr_split[c]);
		cv::merge(proc_bgr_split, proc_image);

		return proc_image;
	}

	cv::Mat histogramEqualization(cv::Mat image) {
		cv::Mat proc_image = cv::Mat::zeros(image.size(), image.type());

		std::vector<cv::Mat> proc_bgr_split(3);
		cv::split(proc_image, proc_bgr_split);

		std::vector<cv::Mat> bgr_split(3);
		cv::split(image, bgr_split);

		for (int c = 0; c < image.channels(); c++)
			cv::equalizeHist(bgr_split[c], proc_bgr_split[c]);

		cv::merge(proc_bgr_split, proc_image);
		return proc_image;
	}

	cv::Mat adjust_hue(cv::Mat image, double hue) {
		cv::Mat proc_image = cv::Mat::zeros(image.size(), image.type());
		cv::cvtColor(image, proc_image, cv::COLOR_BGR2HSV_FULL);

		for (int y = 0; y < image.rows; y++) {
			for (int x = 0; x < image.cols; x++) {
				proc_image.at<cv::Vec3b>(y, x)[0] = cv::saturate_cast<uchar>(proc_image.at<cv::Vec3b>(y, x)[0] * hue);
			}
		}

		cv::cvtColor(proc_image, proc_image, cv::COLOR_HSV2BGR_FULL);
		return proc_image;
	}

	cv::Mat adjust_saturation(cv::Mat image, double saturation) {
		cv::Mat proc_image = cv::Mat::zeros(image.size(), image.type());
		cv::cvtColor(image, proc_image, cv::COLOR_BGR2HSV_FULL);

		for (int y = 0; y < image.rows; y++) {
			for (int x = 0; x < image.cols; x++) {
				proc_image.at<cv::Vec3b>(y, x)[1] = cv::saturate_cast<uchar>(proc_image.at<cv::Vec3b>(y, x)[1] * saturation);
			}
		}

		cv::cvtColor(proc_image, proc_image, cv::COLOR_HSV2BGR_FULL);
		return proc_image;
	}

	cv::Mat adjust_vibrance(cv::Mat image, double vibrance) {
		cv::Mat proc_image = cv::Mat::zeros(image.size(), image.type());
		cv::cvtColor(image, proc_image, cv::COLOR_BGR2HSV_FULL);

		for (int y = 0; y < image.rows; y++) {
			for (int x = 0; x < image.cols; x++) {
				proc_image.at<cv::Vec3b>(y, x)[2] = cv::saturate_cast<uchar>(proc_image.at<cv::Vec3b>(y, x)[2] * vibrance);
			}
		}

		cv::cvtColor(proc_image, proc_image, cv::COLOR_HSV2BGR_FULL);
		return proc_image;
	}

	cv::Mat resize_image(cv::Mat image, int width, int height) {
		cv::Mat proc_image;
		cv::resize(image, proc_image, cv::Size(width, height), cv::INTER_AREA);
		return proc_image;
	}

	cv::Mat sharpen(cv::Mat image, int kernel_size) {
		cv::Mat proc_image = cv::Mat::zeros(image.size(), image.type());
		cv::Mat kernel = cv::Mat::zeros(cv::Size(kernel_size, kernel_size), CV_16SC1);

		for (int y = 0; y < kernel.rows; y++) {
			for (int x = 0; x < kernel.cols; x++) {
				if (x == int(kernel_size / 2) || y == int(kernel_size / 2) && x != y) {
					kernel.at<short>(y, x) = -1;
				}
				if (x == int(kernel_size / 2) && y == int(kernel_size / 2)) {
					kernel.at<short>(y, x) = ((kernel_size - 1) * 2) + 1;
				}
			}
		}

		cv::filter2D(image, proc_image, -1, kernel);
		return proc_image;
	}
};