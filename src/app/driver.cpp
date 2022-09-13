#include "app/driver.h"

#include <thread>
#include <memory>
#include <iostream>

#include <tools/terminal_out.h>

#include "app/terminal_display.h"
#include "app/terminal_input.h"

#include "app/state_play.h"
#include "app/state_edit.h"
#include "app/state_title.h"

#include "interpreter/parser.h"


using namespace app;

driver::driver()
	:state_mngr(states::title) {

	//TODO: allow setting the speed at runtime.
	controllers[states::title]=std::unique_ptr<state_interface>(new state_title(state_mngr));
	controllers[states::play]=std::unique_ptr<state_interface>(new state_play(state_mngr));
	controllers[states::edit]=std::unique_ptr<state_interface>(new state_edit(state_mngr));
}

//TODO: There is stuff to do here... First, the driver acts like a program
//itself but it does not take any parameters at all and that makes a bit
//difficult to work with different boards. I guess the driver could have a 
//board, but considering the board is part of the interpreter, maybe it should
//have an interpreter we can clean up if need be. From there, we could have
//external methods like new_board_from_scratch() of from filename in the 
//driver. This method seems to be ok, there is no external or referenced 
//storage in the driver, so it will do.
void driver::run() {

	//TODO: Add state_game_help
	refresh_rate=100;

	try {
		interpreter::parser 	p;

		p.load_board_from_filename("data/sets/original/test01.brd");
//		p.new_board(20, 20);

		std::unique_ptr<display_interface> d(new terminal_display);
		std::unique_ptr<input_interface> i(new terminal_input);
		d->clear();

		auto last_tick=std::chrono::system_clock::now();
		auto last_refresh=last_tick;

		controllers[state_mngr.get_current()]->awake();

		while(!exit_signal) {

			do_input(*i, p.get_board());

			if(state_mngr.is_change()) {
				d->clear();
				controllers[state_mngr.get_current()]->sleep();
				state_mngr.accept();
				controllers[state_mngr.get_current()]->awake();
			}

			auto state=state_mngr.get_current();
			controllers[state]->do_logic(p, last_tick);

			//TODO: Should not refresh until something has changed...
			auto diff_display=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-last_refresh);
			if(diff_display.count() >= refresh_rate) {

				last_refresh=std::chrono::system_clock::now();
				controllers[state]->do_draw(*d, p);
			}
		}

		//Exit cleanly...
		d->cleanup();
	}
	//TODO: This is actually a particular case of the
	//display initialization... should be another type of exception.
	catch(display_size_exception& e) {
		//TODO: Yeah, no...
		std::cout<<tools::s::text_color(tools::txt_red)
			<<tools::s::background_color(tools::bg_white)
			<<"You cannot play Punge in your terminal:"
			<<tools::s::reset_text()
			<<" "<<e.what()<<std::endl;
	}
	catch(...) {
		throw;
	}
}

void driver::do_input(input_interface& _i, interpreter::board& _board) {

	const auto state=state_mngr.get_current();

	_i.collect();
	controllers[state]->do_input(_i, _board);

	if(_i.is_input()) {

		if(_i.is_escape()) {
			exit_signal=true;
		}
	}
}
