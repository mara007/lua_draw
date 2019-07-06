//
// Created by Marek on 05.07.2019.
//

#include "gtk_app.h"
#include "logger.h"
#include "draw_area.h"

class main_window : public Gtk::ApplicationWindow
{
    Gtk::Grid  m_h_grid, m_v_grid;
    draw_area  m_draw_area;
    Gtk::Button m_button;
public:
    main_window() : Gtk::ApplicationWindow() {
        LOG("main_window() - ctor")
        m_h_grid.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
        m_v_grid.set_orientation(Gtk::ORIENTATION_VERTICAL);

        m_v_grid.add(m_h_grid);
        m_v_grid.add(m_draw_area);
        m_h_grid.add(m_button);

        add(m_v_grid);
        show_all_children();
    };

    void open_file_view(const Glib::RefPtr<Gio::File>& file) {
    }
};


gtk_app::~gtk_app() {
}

gtk_app::gtk_app()
 : Gtk::Application("lua_draw", Gio::APPLICATION_HANDLES_OPEN)
{
    LOG("gtk_app() - ctor")
}

Glib::RefPtr<gtk_app> gtk_app::create()
{
    return Glib::RefPtr<gtk_app>(new gtk_app());
}

main_window* gtk_app::create_main_window()
{
    LOG("gtk_app::create_main_window()")

    auto app_window = new main_window();

    add_window(*app_window);


    app_window->signal_hide().connect(
            sigc::bind<Gtk::Window*>(sigc::mem_fun(*this, &gtk_app::on_hide_window), app_window));

    return app_window;
}

void gtk_app::on_activate()
{
    LOG("gtk_app::on_activate()")
    // The application has been started, so let's show a window.
    auto app_window = create_main_window();
    app_window->present();
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
