#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <vector>
#include <cstdio>
#include <cstdarg>
#include <cassert>
#include <stdexcept>
#include <iostream>
using uint8=unsigned char;
static int width=1280,height=720;
int GetPrimaryGLX(){return width;}
int GetPrimaryGLY(){return height;}
void LogError(const char*,...){}
#define NO_TEXTURE_LOADED 0
#define CHECK_GL_ERROR() do { while (glGetError()!=GL_NO_ERROR) {} } while(0)
static bool forceCopyError=false;
static void CopyTexture(GLenum target,GLint level,GLint xoffset,GLint yoffset,GLint x,GLint y,GLsizei w,GLsizei h) {
    glCopyTexSubImage2D(forceCopyError ? GL_FRAMEBUFFER : target,level,xoffset,yoffset,x,y,w,h);
}
#define glCopyTexSubImage2D CopyTexture
struct Surface {
    GLuint m_glTextureID=0;
    int m_texWidth,m_texHeight;
    void Bind(){glBindTexture(GL_TEXTURE_2D,m_glTextureID);}
    Surface(int w,int h,int filter):m_texWidth(w),m_texHeight(h){
        glGenTextures(1,&m_glTextureID);Bind();
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,filter);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,filter);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        std::vector<uint8> zero(w*h*4,0);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,zero.data());
    }
    ~Surface(){glDeleteTextures(1,&m_glTextureID);}
    void CopyFromScreen();
    void CopyFromScreenLegacy();
    std::vector<uint8> pixels(){
        GLuint fbo;glGenFramebuffers(1,&fbo);glBindFramebuffer(GL_FRAMEBUFFER,fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,m_glTextureID,0);
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)throw std::runtime_error("FBO incomplete");
        std::vector<uint8> data(m_texWidth*m_texHeight*4);
        glReadPixels(0,0,m_texWidth,m_texHeight,GL_RGBA,GL_UNSIGNED_BYTE,data.data());
        glBindFramebuffer(GL_FRAMEBUFFER,0);glDeleteFramebuffers(1,&fbo);return data;
    }
};
#include "surface_capture.inc"
int main(){
    EGLDisplay display=eglGetDisplay(EGL_DEFAULT_DISPLAY);EGLint major,minor;
    if(!eglInitialize(display,&major,&minor)){std::cerr<<"EGL init failed\n";return 1;}
    eglBindAPI(EGL_OPENGL_ES_API);
    EGLint attrs[]={EGL_SURFACE_TYPE,EGL_PBUFFER_BIT,EGL_RENDERABLE_TYPE,EGL_OPENGL_ES2_BIT,EGL_RED_SIZE,8,EGL_GREEN_SIZE,8,EGL_BLUE_SIZE,8,EGL_ALPHA_SIZE,8,EGL_NONE};
    EGLConfig config;EGLint n;eglChooseConfig(display,attrs,&config,1,&n);
    EGLint contextAttrs[]={EGL_CONTEXT_CLIENT_VERSION,2,EGL_NONE};
    EGLContext context=eglCreateContext(display,config,EGL_NO_CONTEXT,contextAttrs);
    EGLint surfaceAttrs[]={EGL_WIDTH,1280,EGL_HEIGHT,720,EGL_NONE};
    EGLSurface surface=eglCreatePbufferSurface(display,config,surfaceAttrs);
    if(!eglMakeCurrent(display,surface,surface,context)){std::cerr<<"EGL context failed\n";return 1;}
    int tests=0;
    for(int forced:{0,1}) for(int filter:{GL_NEAREST,GL_LINEAR}) for(int small:{0,1}) {
        forceCopyError=forced; width=small?73:1280;height=small?51:720;
        glViewport(0,0,width,height);glDisable(GL_SCISSOR_TEST);
        glClearColor(.2,.4,.6,.8);glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_SCISSOR_TEST);glScissor(3,9,width/3,height/2);
        glClearColor(1,.1,.5,1);glClear(GL_COLOR_BUFFER_BIT);glDisable(GL_SCISSOR_TEST);
        Surface legacy(small?128:2048,small?128:1024,filter),gpu(small?128:2048,small?128:1024,filter);
        legacy.CopyFromScreenLegacy();gpu.CopyFromScreen();
        if(legacy.pixels()!=gpu.pixels() || glGetError()!=GL_NO_ERROR){std::cerr<<"GPU/CPU pixels differ\n";return 1;}
        ++tests;
    }
    std::cout<<"PASS: "<<tests<<" GPU/CPU captures pixel-identical, including padding, filtering and forced fallback (EGL/GLES2).\n";
    eglMakeCurrent(display,EGL_NO_SURFACE,EGL_NO_SURFACE,EGL_NO_CONTEXT);
    eglDestroySurface(display,surface);eglDestroyContext(display,context);eglTerminate(display);
}
