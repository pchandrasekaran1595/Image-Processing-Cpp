#include "Header.h"


wstring getPath() {
	wchar_t buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	wstring::size_type pos = wstring(buffer).find_last_of(L"\\/");
	return wstring(buffer).substr(0, pos);
}



int main(int argc, char* argv[]){

	const wstring path = getPath();
	const char* args_1[2] = { "--file", "-f" };
	const char* args_2[2] = { "--gauss-blur", "-gb" };
	const char* args_3[2] = { "--average-blur", "-ab" };
	const char* args_4[2] = { "--median-blur", "-mb" };
	const char* args_5[2] = { "--gamma", "-g" };
	const char* args_6[2] = { "--linear", "-l" };
	const char* args_7[2] = { "--clahe", "-ae" };
	const char* args_8[2] = { "--hist-equ", "-he" };
	const char* args_9[1] = { "--hue" };
	const char* args_10[2] = { "--saturation", "-sat" };
	const char* args_11[2] = { "--vibrance", "-vib" };
	const char* args_12[2] = { "--sharpen", "-sh" };
	const char* args_13[2] = { "--width", "-w" };
	const char* args_14[2] = { "--height", "-h" };
	const char* args_15[2] = { "--save", "-s" };

	int args_1_len = sizeof(args_1) / sizeof(args_1[0]);
	int args_2_len = sizeof(args_2) / sizeof(args_2[0]);
	int args_3_len = sizeof(args_3) / sizeof(args_3[0]);
	int args_4_len = sizeof(args_4) / sizeof(args_4[0]);
	int args_5_len = sizeof(args_5) / sizeof(args_5[0]);
	int args_6_len = sizeof(args_6) / sizeof(args_6[0]);
	int args_7_len = sizeof(args_7) / sizeof(args_7[0]);
	int args_8_len = sizeof(args_8) / sizeof(args_8[0]);
	int args_9_len = sizeof(args_9) / sizeof(args_9[0]);
	int args_10_len = sizeof(args_10) / sizeof(args_10[0]);
	int args_11_len = sizeof(args_11) / sizeof(args_11[0]);
	int args_12_len = sizeof(args_12) / sizeof(args_12[0]);
	int args_13_len = sizeof(args_13) / sizeof(args_13[0]);
	int args_14_len = sizeof(args_14) / sizeof(args_14[0]);
	int args_15_len = sizeof(args_15) / sizeof(args_15[0]);

	string filename = "";

	bool do_gaussian_blur = false;
	int gaussian_blur_kernel_size = 1;

	bool do_average_blur = false;
	int average_blur_kernel_size = 1;

	bool do_median_blur = false;
	int median_blur_kernel_size = 1;

	bool do_gamma_adjust = false;
	double gamma_alpha = 1.0;

	bool do_linear_adjust = false;
	double linear_alpha = 0.0;

	bool do_clahe = false;
	double clipLimit = 2.0;
	int tileGridSize = 2;

	bool do_hist_equ = false;

	bool do_hue_adjust = false;
	double hue = 1.0;

	bool do_saturation_adjust = false;
	double saturation = 1.0;

	bool do_vibrance_adjust = false;
	double vibrance = 1.0;

	bool do_sharpen = false;
	int sharpen_kernel_size = 1;

	bool do_resize_w = false;
	bool do_resize_h = false;
	int width, height;

	bool save = false;

	for (int i = 0; i < argc; i++) {

		for (int j = 0; j < args_1_len; j++) if (strcmp(args_1[j], argv[i]) == 0) filename = argv[i + 1];

		for (int j = 0; j < args_2_len; j++) {
			if (strcmp(args_2[j], argv[i]) == 0) {
				do_gaussian_blur = true;
				gaussian_blur_kernel_size = stoi(argv[i + 1]);
				if (gaussian_blur_kernel_size % 2 == 0) gaussian_blur_kernel_size++;
			}
		}

		for (int j = 0; j < args_3_len; j++) {
			if (strcmp(args_3[j], argv[i]) == 0) {
				do_average_blur = true;
				average_blur_kernel_size = stoi(argv[i + 1]);
			}
		}

		for (int j = 0; j < args_4_len; j++) {
			if (strcmp(args_4[j], argv[i]) == 0) {
				do_median_blur = true;
				median_blur_kernel_size = stoi(argv[i + 1]);
				if (median_blur_kernel_size % 2 == 0) median_blur_kernel_size++;
			}
		}

		for (int j = 0; j < args_5_len; j++) {
			if (strcmp(args_5[j], argv[i]) == 0) {
				do_gamma_adjust = true;
				gamma_alpha = stod(argv[i + 1]);
			}
		}

		for (int j = 0; j < args_6_len; j++) {
			if (strcmp(args_6[j], argv[i]) == 0) {
				do_linear_adjust = true;
				linear_alpha = stod(argv[i + 1]);
				if (linear_alpha > 255) linear_alpha = 255.0;
				if (linear_alpha < 0) linear_alpha = 0.0;
			}
		}

		for (int j = 0; j < args_7_len; j++) {
			if (strcmp(args_7[j], argv[i]) == 0) {
				do_clahe = true;
				clipLimit = stod(argv[i + 1]);
				tileGridSize = stoi(argv[i + 2]);
			}
		}

		for (int j = 0; j < args_8_len; j++) if (strcmp(args_8[j], argv[i]) == 0) do_hist_equ = true;
		
		for (int j = 0; j < args_9_len; j++) {
			if (strcmp(args_9[j], argv[i]) == 0) {
				do_hue_adjust = true;
				hue = stod(argv[i + 1]);
			}
		}

		for (int j = 0; j < args_10_len; j++) {
			if (strcmp(args_10[j], argv[i]) == 0) {
				do_saturation_adjust = true;
				saturation = stod(argv[i + 1]);
			}
		}

		for (int j = 0; j < args_11_len; j++) {
			if (strcmp(args_11[j], argv[i]) == 0) {
				do_vibrance_adjust = true;
				vibrance = stod(argv[i + 1]);
			}
		}

		for (int j = 0; j < args_12_len; j++) {
			if (strcmp(args_12[j], argv[i]) == 0) {
				do_sharpen = true;
				sharpen_kernel_size = stoi(argv[i + 1]);
				if (sharpen_kernel_size % 2 == 0) sharpen_kernel_size++;
			}
		}

		for (int j = 0; j < args_13_len; j++) {
			if (strcmp(args_13[j], argv[i]) == 0) {
				do_resize_w = true;
				width = stoi(argv[i + 1]);
			}
		}

		for (int j = 0; j < args_14_len; j++) {
			if (strcmp(args_14[j], argv[i]) == 0) {
				do_resize_h = true;
				height = stoi(argv[i + 1]);
			}
		}

		for (int j = 0; j < args_15_len; j++) if (strcmp(args_15[j], argv[i]) == 0) save = true;
	}

	assert(filename.empty() != 1);

	string READ_PATH = string(path.begin(), path.end()) + "\\Files\\" + filename;
	string SAVE_PATH = string(path.begin(), path.end()) + "\\Processed";

	const char* save_path_array = SAVE_PATH.c_str();
	int make_directory = _mkdir(save_path_array);
	if (make_directory != -1)
		cout << endl << "Creating Save Directory" << endl;


	ImageHandler image_handler;
	ImageProcessor image_processor;

	cv::Mat image = image_handler.read_image(READ_PATH);

	if (image.empty())
		cout << endl << "Failed to open Image; possibly not present in directory." << endl;

	if (do_gaussian_blur)	  image = image_processor.gauss_blur(image, gaussian_blur_kernel_size);
	if (do_average_blur)	  image = image_processor.average_blur(image, average_blur_kernel_size);
	if (do_median_blur)       image = image_processor.median_blur(image, median_blur_kernel_size);
	if (do_gamma_adjust)	  image = image_processor.gammaAdjust(image, gamma_alpha);
	if (do_linear_adjust)	  image = image_processor.linearContrastAdjust(image, linear_alpha);
	if (do_clahe)             image = image_processor.adaptiveEqualization(image, clipLimit, tileGridSize);
	if (do_hist_equ)          image = image_processor.histogramEqualization(image);
	if (do_hue_adjust)        image = image_processor.adjust_hue(image, hue);
	if (do_saturation_adjust) image = image_processor.adjust_saturation(image, saturation);
	if (do_vibrance_adjust)   image = image_processor.adjust_vibrance(image, vibrance);
	if (do_sharpen)           image = image_processor.sharpen(image, sharpen_kernel_size);

	if (do_resize_w) {
		int h = image.rows;
		image = image_processor.resize_image(image, width, h);
	}
	if (do_resize_h) {
		int w = image.cols;
		image = image_processor.resize_image(image, w, height);
	}
	if (do_resize_w && do_resize_h) image = image_processor.resize_image(image, width, height);

	if (!save)
		image_handler.show_image(image_handler.downscale(image));
	else
		image_handler.save_image(SAVE_PATH + "\\Processed.jpg", image);
		
	return 0;
}