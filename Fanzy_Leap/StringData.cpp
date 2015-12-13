#include"StringData.h"
StringData::StringData(const std::string& message)
{
	setlocale(LC_ALL, "");
	bindtextdomain("StringData", ".");
	textdomain("StringData");
	if(message == "StartMenu")
	{
		data.push_back(gettext("Start"));
		data.push_back(gettext("Introduction"));
		data.push_back(gettext("Quit"));
		data.push_back(gettext("HighScore:"));
	}
	else if(message == "Help")
	{
		data.push_back(gettext("Whole"));
		data.push_back(gettext("Black"));
		data.push_back(gettext("Yellow"));
		data.push_back(gettext("Red"));
		data.push_back(gettext("Blue"));
		data.push_back(gettext("Purple"));
	}
	else if(message == "GameEnd")
	{
		data.push_back(gettext("Game Over"));
		data.push_back(gettext("your score is:"));
		data.push_back(gettext("Again"));
		data.push_back(gettext("Quit"));
		data.push_back(gettext("You break the record"));
	}
	else if(message == "PauseMenu")
	{
		data.push_back(gettext("Return"));
		data.push_back(gettext("Retry"));
		data.push_back(gettext("Quit"));
	}
	else if(message == "ScoreBoard")
	{
		data.push_back(gettext("Score:"));
	}
	else if(message == "GamePoccess")
	{
		data.push_back(gettext("HighScore:"));
	}

}
std::string StringData::operator [](const unsigned int& n) const
{
	if ( n >= data.size() )
		return 0;
	return data[n];
}