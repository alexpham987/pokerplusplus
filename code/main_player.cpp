#include "Mainwin.h"
#include "player_comm.h"
#include <gtkmm.h>
#include <thread>
#include <iostream>

//main function for the player's side of the game
int main(int argc, char *argv[])
{
  asio::io_context io_context;

  tcp::resolver resolver(io_context);
  auto endpoints = resolver.resolve(argv[1], argv[2]);

  player_comm* p = new player_comm(io_context, endpoints);
  assert(p);

  std::thread t([&io_context](){ io_context.run(); });

  Gtk::Main kit(argc, argv);
  Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("PokerPP.glade");

  Mainwin *win = 0;
  builder->get_widget_derived("Mainwin", win);

  Player_Game pg;
  p->setMainwin(win);

  win->setPlayerGame(pg);
  win->setPlayerComm(p);

  kit.run(*win);

  p->close();
  t.join();

  return 0;
}