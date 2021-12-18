#include "Header.h"


wstring getPath() {
	wchar_t buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	wstring::size_type pos = wstring(buffer).find_last_of(L"\\/");
	return wstring(buffer).substr(0, pos);
}



int main(int argc, char *argv[]){

	const wstring path = getPath();
	const char* args_1[2] = { "--file", "-f" };
	const char* args_2[2] = { "--gauss-blur", "-gb" };
	const char* args_19[2] = { "--save", "-s" };

	int args_1_len = sizeof(args_1) / sizeof(args_1[0]);
	int args_2_len = sizeof(args_2) / sizeof(args_2[0]);
	int args_19_len = sizeof(args_19) / sizeof(args_19[0]);

	string filename = "";

	bool do_gaussian_blur = false;
	int gaussian_kernel_size = 1;
	bool save = false;

	for (int i = 0; i < argc; i++) {

		for (int j = 0; j < args_1_len; j++) {
			if (strcmp(args_1[j], argv[i]) == 0) {
				filename = argv[i + 1];
			}
		}

		for (int j = 0; j < args_2_len; j++) {
			if (strcmp(args_2[j], argv[i]) == 0) {
				do_gaussian_blur = true;
				gaussian_kernel_size = stoi(argv[i + 1]);
				if (gaussian_kernel_size % 2 == 0) {
					gaussian_kernel_size++;
				}
			}
		}

		for (int j = 0; j < args_19_len; j++) {
			if (strcmp(args_19[j], argv[i]) == 0) {
				save = true;
			}
		}
	}

	assert(filename.empty() != 1);

	string READ_PATH = string(path.begin(), path.end()) + "\\Files\\" + filename;
	string SAVE_PATH = string(path.begin(), path.end()) + "\\Processed";

	const char* save_path_array = SAVE_PATH.c_str();

	if (_mkdir(save_path_array) == -1)
		cout << "Cannot Create Directory !!!!";


	ImageHandler image_handler;
	ImageProcessor image_processor;

	cv::Mat image = image_handler.read_image(READ_PATH);
	
	if (do_gaussian_blur) image_processor.gauss_blur(image, gaussian_kernel_size);

	if (!save)
		image_handler.show_image(image_handler.downscale(image_processor.proc_image));
	else
		image_handler.save_image(SAVE_PATH + "\\Processed.jpg", image_processor.proc_image);
		

	return 0;
}