//
// Created by Marek on 05.07.2019.
//

#pragma once

#include <gtkmm.h>
class main_window;

class gtk_app : public Gtk::Application {
    void on_hide_window(Gtk::Window* window);
    main_window * create_main_window();

protected:
    void on_activate() override;
    void on_open(const Gio::Application::type_vec_files& files,
                 const Glib::ustring& hint) override;
    gtk_app();

public:
    virtual ~gtk_app();
    static Glib::RefPtr<gtk_app> create();


};

