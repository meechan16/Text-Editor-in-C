#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/X.h>
int main(){
    Window win;
    Display* dsp = XOpenDisplay(NULL);  
    win = XCreateSimpleWindow(dsp, DefaultRootWindow(dsp), 0, 0, 1280, 720, 0, 0, 0);

    XMapWindow(dsp, win);

    Atom atom_delete_window = XInternAtom(dsp, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(dsp, win, &atom_delete_window, 1);

    XFlush(dsp);

    while(1){
        XEvent ev;
        XNextEvent(dsp, &ev);
        if(ev.type == ClientMessage){
            if(ev.xclient.data.l[0] == atom_delete_window){
                break;
            }
        }
    }

    XDestroyWindow(dsp, win);
    XCloseDisplay(dsp);
    printf("Hello World\n");
    return 0;
}