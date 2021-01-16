
#include <iostream>
#include <ostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <algorithm>
using namespace std;

class RaiiClipboard
{
public:
	RaiiClipboard()
	{
		if (!OpenClipboard(nullptr))
			throw runtime_error("Can't open clipboard.");
		// ... or define some custom exception class for clipboard errors.
	}

	~RaiiClipboard()
	{
		CloseClipboard();
	}

	// Ban copy   
private:
	RaiiClipboard(const RaiiClipboard&);
	RaiiClipboard& operator=(const RaiiClipboard&);
};

class RaiiTextGlobalLock
{
public:
	explicit RaiiTextGlobalLock(HANDLE hData)
		: m_hData(hData)
	{
		m_psz = static_cast<const char*>(GlobalLock(m_hData));
		if (!m_psz)
			throw runtime_error("Can't acquire lock on clipboard text.");
	}

	~RaiiTextGlobalLock()
	{
		GlobalUnlock(m_hData);
	}

	const char* Get() const
	{
		return m_psz;
	}

private:
	HANDLE m_hData;
	const char* m_psz;

	// Ban copy
	RaiiTextGlobalLock(const RaiiTextGlobalLock&);
	RaiiTextGlobalLock& operator=(const RaiiTextGlobalLock&);
};

std::string get_current_date_time_as_stemp() {
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	int Year = timeinfo->tm_year;
	int Month = timeinfo->tm_mon;
	int Day = timeinfo->tm_mday;
	int Hour = timeinfo->tm_hour;
	int Min = timeinfo->tm_min;
	int Sec = timeinfo->tm_sec;

	return to_string(1900 + Year) + "/" + to_string(1 + Month) + "/" + to_string(Day) + "_"
		+ to_string(Hour) + ":" +
		to_string(Min) 
		//+ to_string(Sec) + "s"
		;
}

std::string get_current_date_time_for_filename() {
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	int Year = timeinfo->tm_year;
	int Month = timeinfo->tm_mon;
	int Day = timeinfo->tm_mday;
	int Hour = timeinfo->tm_hour;
	int Min = timeinfo->tm_min;
	int Sec = timeinfo->tm_sec;

	return to_string(1900 + Year) + "_" + to_string(1 + Month) + "_" + to_string(Day);
}

int get_current_date_time_as_minutes() {
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	int Year = timeinfo->tm_year;
	int Month = timeinfo->tm_mon;
	int Day = timeinfo->tm_mday;
	int Hour = timeinfo->tm_hour;
	int Min = timeinfo->tm_min;
	int Sec = timeinfo->tm_sec;

	return Day * 24 * 60 + Hour * 60 + Min;;
}

string get_expected_time_from_current_given_mins_to_go(int min_to_go) {
	int current_mins = get_current_date_time_as_minutes();
	int expected_mins = min_to_go + current_mins;
	int exp_day = expected_mins / (24 * 60);
	int exp_hour = (expected_mins - exp_day * 24 * 60) / 60;
	int exp_min = expected_mins % 60;
	return to_string(exp_hour) + ":" + to_string(exp_min);
}

string get_clipboard_text()
{
	RaiiClipboard clipboard;

	HANDLE hData = nullptr;
	while (hData == nullptr)
		hData = GetClipboardData(CF_TEXT);

	RaiiTextGlobalLock textGlobalLock(hData);
	string text(textGlobalLock.Get());

	return text;
}

void replace_string_in_place(std::string& subject, const std::string& search, const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}

void log_current_working(std::string task_description, int expected_working_time, string from_t, string to_t, int length_t) {
	// dulplicated recording now, can write an other code for cleaning 
	ofstream fs;
	fs.open(std::string("../log/work_time_tracking_" + get_current_date_time_for_filename() + ".txt"), std::ofstream::out | std::ofstream::app);
	fs << "\t " + task_description
		+ "\n\t\texp_time:\t" + std::to_string(expected_working_time)
		+ "\n\t\tactual_from:\t" + from_t 
		+ "\n\t\tactual_to:\t" + to_t 
		+ "\n\t\tactual_takes:\t" + std::to_string(length_t) 
		+ " min "<< endl;
	fs.close();
}