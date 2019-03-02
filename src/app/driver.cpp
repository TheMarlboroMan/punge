#include "driver.h"

#include <thread>
#include <memory>
#include <iostream>

#include <terminal_out.h>

#include "terminal_display.h"
#include "terminal_input.h"
#include "drawing_routines.h"
#include "../interpreter/parser.h"


using namespace app;

void driver::run() {

	try {
		interpreter::parser 	p;

//		p.load_board_from_filename("data/sets/original/test01.brd");
		p.new_board(20, 20);

		std::unique_ptr<display_interface> d(new terminal_display);
		std::unique_ptr<input_interface> i(new terminal_input);
		d->clear();

		auto last_tick=std::chrono::system_clock::now();
		auto last_refresh=last_tick;

		do_draw(*d, p);

		while(states::exit!=state) {

			do_input(*i, p.get_board());
			do_logic(p, last_tick);

			//TODO: Should not refresh until something has changed...
			auto diff_display=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-last_refresh);
			if(diff_display.count() >= refresh_rate) {

				last_refresh=std::chrono::system_clock::now();
				do_draw(*d, p);
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

void driver::do_logic(interpreter::parser& _p, t_time& _last_tick) {

	//TODO: Separate in different state classes.
	switch(state) {
		case states::edit:

		break;

		case states::play: {
	
			auto diff_tick=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-_last_tick);
			if(diff_tick.count() >= tick_speed) {
				_last_tick=std::chrono::system_clock::now();
				_p.step();
			}

			if(_p.is_end()) {
				state=states::exit;
			}
		}
		break;
		case states::exit: 

		break;
	}
}

void driver::do_input(input_interface& _i, interpreter::board& _board) {

	_i.collect();
	if(_i.is_input()) {

		if(_i.is_tab()) {
			state=state==states::play 
				? states::edit
				: states::play;
		}

		if(_i.is_escape()) {
			state=states::exit;
		}

		//TODO: Separate in different state classes.
		switch(state) {
			case states::play: do_input_play(_i, _board); break;
			case states::edit: do_input_edit(_i, _board); break;
			case states::exit: break;
		}
	}
}

void driver::do_input_play(input_interface& /*_i*/, const interpreter::board& /*_board*/) {

}

void driver::do_input_edit(input_interface& _i, interpreter::board& _board) {

	if(_i.is_arrow()) {

		auto future_position=edit_cursor;

		if(_i.is_arrow_up()) {--future_position.y;}
		else if(_i.is_arrow_down()) {++future_position.y;}
		else if(_i.is_arrow_left()) {--future_position.x;}
		else if(_i.is_arrow_right()) {++future_position.x;}

		//Validate the position...
		if(_board.check_coords(future_position)) {
			edit_cursor=future_position;
		}
	}
	else if(_i.is_char()) {

		_board.set_tile(edit_cursor, _i.get_char());
	}
}

void driver::do_draw(display_interface& _di, const interpreter::parser& _parser) {

	//TODO: Separate in different state classes.
	switch(state) {
		case states::edit: do_draw_edit(_di, _parser); break;
		case states::play: do_draw_play(_di, _parser); break;
		case states::exit: break;
	}

	_di.refresh();
}

void driver::do_draw_edit(display_interface& _di, const interpreter::parser& _parser) {

	draw_board_borders(_di, _parser.get_board());
	draw_board(_di, _parser.get_board());

	draw_cursor(_di, edit_cursor, _parser.get_board(), display_interface::color_fg::white, display_interface::color_bg::green);
	draw_cursor_pos(_di, edit_cursor); 
}

void driver::do_draw_play(display_interface& _di, const interpreter::parser& _parser) {

	const auto curpos=_parser.get_cursor().get_position();

	draw_board_borders(_di, _parser.get_board());
	draw_board(_di, _parser.get_board());

	//TODO: Change color when in string mode!!!
	//TODO: Set a reasonable refresh rate.
	draw_cursor(_di, curpos, _parser.get_board(), display_interface::color_fg::white, display_interface::color_bg::red);
	draw_stack(_di, _parser.get_stack());
	draw_output(_di, _parser.get_output());
	draw_cursor_pos(_di, curpos);
}
