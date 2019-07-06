//
// Created by Marek on 06.07.2019.
//

#pragma once

#include "gtkmm/drawingarea.h"

class draw_area : public Gtk::DrawingArea {
    size_t m_draw_count;
public:
    draw_area();
    virtual ~draw_area();

protected:
    bool on_draw(const ::Cairo::RefPtr< ::Cairo::Context>& cr) override;
};
