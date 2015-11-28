#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
using namespace std;

int main() {
    Fl_Window win( 500,300,"Test window" );
    win.begin();
       Fl_Button but( 10, 150, 70, 30,"Click" );
    win.end();
    win.show();
    return Fl::run();
}
