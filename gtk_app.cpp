//
// Created by Marek on 05.07.2019.
//

#include "gtk_app.h"
#include "logger.h"

class main_window : public Gtk::ApplicationWindow
{
public:
    main_window() : Gtk::ApplicationWindow() {
    };

    void open_file_view(const Glib::RefPtr<Gio::File>& file) {
    }
};


gtk_app::~gtk_app() {
}

gtk_app::gtk_app()
        : Gtk::Application("org.gtkmm.examples.application", Gio::APPLICATION_HANDLES_OPEN)
{
}

Glib::RefPtr<gtk_app> gtk_app::create()
{
    return Glib::RefPtr<gtk_app>(new gtk_app());
}

main_window* gtk_app::create_main_window()
{
    auto appwindow = new main_window();

    // Make sure that the application runs for as long this window is still open.
    add_window(*appwindow);

    // Gtk::Application::add_window() connects a signal handler to the window's
    // signal_hide(). That handler removes the window from the application.
    // If it's the last window to be removed, the application stops running.
    // Gtk::Window::set_application() does not connect a signal handler, but is
    // otherwise equivalent to Gtk::Application::add_window().

    // Delete the window when it is hidden.
    appwindow->signal_hide().connect(sigc::bind<Gtk::Window*>(sigc::mem_fun(*this,
                                                                            &gtk_app::on_hide_window), appwindow));

    return appwindow;
}

void gtk_app::on_activate()
{
    // The application has been started, so let's show a window.
    auto appwindow = create_main_window();
    appwindow->present();
}

void gtk_app::on_open(const Gio::Application::type_vec_files& files,
                                 const Glib::ustring& /* hint */)
{
    // The application has been asked to open some files,
    // so let's open a new view for each one.
    main_window* appwindow = nullptr;
    auto windows = get_windows();
    if (windows.size() > 0)
        appwindow = dynamic_cast<main_window*>(windows[0]);

    if (!appwindow)
        appwindow = create_main_window();

    for (const auto& file : files)
        appwindow->open_file_view(file);

    appwindow->present();
}

void gtk_app::on_hide_window(Gtk::Window* window)
{
    delete window;
}
