#include "driver.h"

#include <thread>
#include <memory>
#include <iostream>

#include <terminal_out.h>

#include "terminal_display.h"
#include "terminal_input.h"

#include "state_play.h"
#include "state_edit.h"
#include "state_title.h"


#include "../interpreter/parser.h"


using namespace app;

driver::driver() {

	controllers[states::title]=std::unique_ptr<state_interface>(new state_title);
	controllers[states::play]=std::unique_ptr<state_interface>(new state_play);
	controllers[states::edit]=std::unique_ptr<state_interface>(new state_edit);
}

void driver::run() {

	//TODO: Add state_game_help

	try {
		interpreter::parser 	p;

//		p.load_board_from_filename("data/sets/original/test01.brd");
		p.new_board(20, 20);

		std::unique_ptr<display_interface> d(new terminal_display);
		std::unique_ptr<input_interface> i(new terminal_input);
		d->clear();

		auto last_tick=std::chrono::system_clock::now();
		auto last_refresh=last_tick;

		if(controllers.count(state)) {
			controllers[state]->do_draw(*d, p);
		}

		while(states::exit!=state) {

			do_input(*i, p.get_board());

			if(controllers.count(state)) {
				controllers[state]->do_logic(p, last_tick);
			}

			//TODO: Should not refresh until something has changed...
			auto diff_display=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-last_refresh);
			if(diff_display.count() >= refresh_rate) {

				last_refresh=std::chrono::system_clock::now();
				if(controllers.count(state)) {
					controllers[state]->do_draw(*d, p);
				}
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


	_i.collect();
	if(_i.is_input()) {

		if(_i.is_tab() ) {
		//TODO... && (state==states::play || state==states::edit)) {
			state=state==states::play 
				? states::edit
				: states::play;
		}

		if(_i.is_escape()) {
			state=states::exit;
		}

		if(controllers.count(state)) {
			controllers[state]->do_input(_i, _board);
		}
	}
}
