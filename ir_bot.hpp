#ifndef __IR_BOT_H__
#define __IR_BOT_H__

#include <map>
#include <string>
#include <functional>

#include "couple.hpp"

template <typename T>
class IR_Bot
{
	public:
		IR_Bot(const T& conf_file);

		void Nudge(const T& ndg);
		void Join(const T& channel, T key = "");

		void Operation(const T& ndg, const T& channel);
		void Proc(const T& to);
		void Message(const T& recv, const T& msg);
		void Terminate(const T& msg);
		void Iterate();

		bool R_Pass(const T& pass);

		void Insert_RH(std::function<void (const T&)>);

	protected:
		void w_handle();   // Write The Handler
		void r_handle(const T& msg);

		std::vector<std::function<void (const T&)> > n_read_handlers;
		std::map<T, T> n_conf;
		Couple n_connection;
};

#endif __IR_BOT_H__
