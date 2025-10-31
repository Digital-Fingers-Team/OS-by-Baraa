// Minimal text editor demo in Rust using GTK (for Wayland compatibility)
// Assumptions: GTK installed, compiled with cargo

use gtk::prelude::*;
use gtk::{Application, ApplicationWindow, TextView, ScrolledWindow};

fn main() {
    let app = Application::builder()
        .application_id("com.blackboxos.texteditor")
        .build();

    app.connect_activate(|app| {
        let window = ApplicationWindow::builder()
            .application(app)
            .title("BlackboxOS Text Editor")
            .default_width(600)
            .default_height(400)
            .build();

        let text_view = TextView::new();
        let scrolled_window = ScrolledWindow::new();
        scrolled_window.set_child(Some(&text_view));
        window.set_child(Some(&scrolled_window));

        window.present();
    });

    app.run();
}

// Build: cargo build --release
// Run: ./target/release/text_editor
// Security: Sandboxed via Flatpak manifest (future)
