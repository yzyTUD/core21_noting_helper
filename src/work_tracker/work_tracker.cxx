#include <cgv/utils/stopwatch.h>
#include <cgv/utils/profiler.h>
#include <cgv/utils/file.h>
#include "zrtech_os_api.h"

int main(int argc, char** argv){
	int timelength = 30;
	std::string brief_task_description;
	std::cout << "Shift-F: force log, Shift-T: terminate, Shift-L: let me know how much time reminds" << std::endl;
	std::cout << "log automatically when time limit arrives for the first time" << std::endl;
	std::cout << "brief task description: "; cin >> brief_task_description;
	std::cout << "how long is the current task expected?: (in min) "; cin >> timelength;
	std::cout << "timer starts at: " + get_current_date_time_as_stemp() + ", " + to_string(timelength) + " min" <<std::endl;
	std::cout << "expected ending time: " + get_expected_time_from_current_given_mins_to_go(timelength) << std::endl;
	int start_min = get_current_date_time_as_minutes();
	string start_time_stemp = get_current_date_time_as_stemp();
	int temp_min = get_current_date_time_as_minutes();
	int num_timelength = 0;
	bool debug = false;
	while (true) {
		if(debug)
			std::cout << "current time in mins: " + to_string(get_current_date_time_as_minutes()) << std::endl;
		// check every ns
		Sleep(50); 
		// log when time arrives
		if ((get_current_date_time_as_minutes() - temp_min) == timelength) {
			Beep(400, 1000);
			Sleep(300);
			Beep(400, 1000);
			num_timelength++;
			temp_min = get_current_date_time_as_minutes();
			std::cout << "you have worked: " + to_string(timelength * num_timelength) + " min!" << std::endl;
			log_current_working(brief_task_description, timelength, start_time_stemp, get_current_date_time_as_stemp(), get_current_date_time_as_minutes() - start_min);
		}
		// force log
		if ((GetAsyncKeyState(VK_LSHIFT))&&(GetAsyncKeyState('F') & 0x8000)) {
			log_current_working(brief_task_description, timelength, start_time_stemp, get_current_date_time_as_stemp(), get_current_date_time_as_minutes() - start_min);
			Beep(528, 500);
		}
		// log when exit
		if ((GetAsyncKeyState(VK_LSHIFT)) && (GetAsyncKeyState('T') & 0x8000)) {
			log_current_working(brief_task_description, timelength, start_time_stemp, get_current_date_time_as_stemp(), get_current_date_time_as_minutes() - start_min);
			Beep(528, 500);
			exit(0);
		}
		// get time remind: 
		if ((GetAsyncKeyState(VK_LSHIFT)) && (GetAsyncKeyState('L') & 0x8000)) {
			int time_to_go = timelength - (get_current_date_time_as_minutes() - temp_min);
			std::cout << "time to go: (in min) " << time_to_go << std::endl;
		}
	}
	return 0;
}