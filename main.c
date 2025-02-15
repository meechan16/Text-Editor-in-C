#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/X.h>
#include <GL/glx.h>
#include <runara/runara.h>
Window win;

GLXContext gl_context;
Display* dsp;

void create_gl_context(){
    int screen_id = DefaultScreen(dsp);

    int attribs[] = {
        GLX_RGBA,
        GLX_DEPTH_SIZE, 24,
        GLX_DOUBLEBUFFER,
        None
    };
    XVisualInfo* visual_info = glXChooseVisual(dsp, screen_id, attribs);
    
    gl_context = glXCreateContext(dsp, visual_info, NULL, GL_TRUE);
    if(gl_context == NULL){
        fprintf(stderr, "Error: glXCreateContext failed\n");
        return;
    }


    if (visual_info == NULL){
        fprintf(stderr, "Error: glXChooseVisual failed\n");
        return;
    }
}
int main(){
    dsp = XOpenDisplay(NULL);  
    win = XCreateSimpleWindow(dsp, DefaultRootWindow(dsp), 0, 0, 1280, 720, 0, 0, 0);

    XSelectInput(dsp, win, ExposureMask | KeyPressMask);

    XMapWindow(dsp, win);

    Atom atom_delete_window = XInternAtom(dsp, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(dsp, win, &atom_delete_window, 1);

    XFlush(dsp);

    create_gl_context();

    glXMakeCurrent(dsp, win, gl_context);

    while(1){
        XEvent ev;
        XNextEvent(dsp, &ev);
        if(ev.type == ClientMessage){
            if(ev.xclient.data.l[0] == atom_delete_window){
                break;
            }
        }
        if(ev.type == Expose){
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

            glXSwapBuffers(dsp, win);
        }
    }

    XDestroyWindow(dsp, win);
    XCloseDisplay(dsp);
    printf("Exited\n");
    return 0;
}