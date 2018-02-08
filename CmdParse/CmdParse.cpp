#include "CmdParse.h"


//static std::vector<std::string> splitString(const std::string s, const std::string delimeter)
//{
//	std::vector<int> idxVec;
//
//	int idx = 0;
//	while((idx = s.find_first_of(delimeter, idx)) != -1) {
//		idxVec.push_back(idx);
//	}
//
//	std::vector<std::string> vec;
//
//	int prev = 0;
//	for(int i = 0; i < idxVec.size(); i++) {
//
//		std::string tmp = s.substr(prev, idxVec[i] - prev);
//		prev = idxVec[i];
//
//		vec.push_back(tmp);
//	}
//
//	return vec;
//}

CmdParse::CmdParse()
{

}

void CmdParse::add(const std::string shortForm, bool hasArg)
{
	this->add(shortForm, "", hasArg);
}

void CmdParse::add(const std::string shortForm, const std::string longForm, bool hasArg)
{
	ArgType arg;
	arg.shortForm = shortForm;
	arg.longForm = longForm;
	arg.hasArg = hasArg;

	_argType.push_back(arg);
}

bool CmdParse::get(const std::string opt, ArgType &t)
{
	for(int i = 0; i < _argType.size(); i++) {
		if(_argType[i].shortForm == opt || _argType[i].longForm == opt) {
			t = _argType[i];
			return true;
		}
	}

	return false;
}

void CmdParse::parse(int argc, char **argv)
{
	for(int i = 1; i < argc; i++) {
		std::string arg(argv[i]);

		ArgType t;
		if(get(arg, t)) {
			// It is an option

			OptArg a;

			if(t.hasArg) {
				// It requires an argument

				if(i == argc - 1) {
					throw std::string("-k requires an argument");
				}

				std::string optArg(argv[i + 1]);
				i++;
				a.option = arg;
				a.arg = optArg;

			} else {
				// It does not require an argument

				a.option = arg;
				a.arg = "";
			}

			_optArgs.push_back(a);
			
		} else {
			// It is an operand

			_operands.push_back(arg);
		}
	}
}

std::vector<OptArg> CmdParse::getArgs()
{
	return _optArgs;
}

std::vector<std::string> CmdParse::getOperands()
{
	return _operands;
}