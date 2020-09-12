#include <stdlib.h>
#include <stdio.h>
#include "choosedlg.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "classes/glwindow.h"
#include "util.h"
#include "texturemanager.h"
#include "scenemanager.h"
#include "model.h"
#include <math.h>

class RenderWindow: public GLWindowBase
{
private:
	TextureManager * texman;
	SceneManager* sceneman;
	GLfloat light_position[4];
	char str[50];
    GLfloat dist;
    GLfloat rx, ry, rz;
    std::string fileName;
private:

	void loadObject(std::string fileName)
	{
		Model * model = new Model(texman);
		model->load(fileName);
		sceneman->clear();
		sceneman->add(model);
	}

protected:

	virtual void getWindowInfo(int& width, int& height, int& bpp, bool& fullscreen, bool& resizable)
	{
		GLWindowBase::getWindowInfo(width, height, bpp, fullscreen, resizable);
		width = 800;
		height = 600;
	}

	bool onInit(int argc, char** argv)
	{
		// qualidade do anti serrilhado
#ifdef WIN32
		if(argc >= 3 && (strcmp(argv[1], "--sample") == 0 || strcmp(argv[1], "-s") == 0)) {
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, atoi(argv[2]));
		}
#endif
		if(argc == 2)
			fileName = argv[1];
		else if(argc == 4)
			fileName = argv[3];
		return GLWindowBase::onInit(argc, argv);
	}

	virtual void onResize(int newWidth, int newHeight)
	{
		onCreate();
	}

	void setup3DScene()
	{
		int width = getWidth(), height = getHeight();
		if (height == 0)									// Prevent A Divide By Zero
			height = 1;
		glViewport(0, 0, width, height);					// Set The Current Viewport
		glMatrixMode( GL_PROJECTION );						// Select The Projection Matrix
		glLoadIdentity();									// Reset The Projection Matrix
		gluPerspective(45.0f, (GLfloat)width / height, 0.01f, 200.0f);
		// Calculate The Aspect Ratio Of The Window
		glMatrixMode( GL_MODELVIEW );						// Select The Modelview Matrix
		glLoadIdentity();									// Reset The Modelview Matrix
	}

	virtual void onKeyDown(int key, int state)
	{
		GLWindowBase::onKeyDown(key, state);
		switch(key)
		{
		case 'a':
		{
			OpenDialog * opendlg;

			opendlg = new OpenDialog();
			opendlg->setTitle("Selecione um arquivo");
			opendlg->getFilter().push_back("Arquivos Wavefront object|*.obj");
			opendlg->getFilter().push_back("Todos os arquivos|*.*");
			opendlg->setFilterIndex(0);
			opendlg->setMultiSelect(false);
			if(opendlg->execute()) {
				loadObject(opendlg->getFiles()[0]);
			}
			delete opendlg;
			break;
		}
		default:
			break;
		}
	}
	
	virtual void onMouseDown(int x, int y, int button, int state)
	{
		if(button == SDL_BUTTON_WHEELUP) {
			dist += 0.1;
		} else if(button == SDL_BUTTON_WHEELDOWN) {
			dist -= 0.1;
		} else if(button == SDL_BUTTON_LEFT) {
			onKeyDown('a', 0);
		}
	}

	virtual void onCreate()
	{
		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat mat_shininess[] = { 50.0 };

		if(fileName != "")
		{
			loadObject(fileName);
			fileName = "";
		}
		setup3DScene();
		glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );
		// Habilita teste de profundidade
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glClearDepth(1.0f);
		glDepthFunc(GL_LEQUAL);
		// Habilita luz
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		glShadeModel(GL_SMOOTH);
		// Habilita cor nor objetos
		glEnable(GL_COLOR_MATERIAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
	}

	virtual void render()
	{
		// limpa o buffer
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		glPushMatrix();
		glTranslatef(0.0f, 0.0f, dist);
        glRotatef(rx, 1.0f, 0.0f, 0.0f);
        glRotatef(ry, 0.0f, 1.0f, 0.0f);
        glRotatef(rz, 0.0f, 0.0f, 1.0f);
		sceneman->render();
		glPopMatrix();
		// mostra os desenhos
		swapBuffers();
		sprintf(str, "Object Viewer - FPS: %.2f", getFPS());
		setTitle(str);
        rx += 0.5f;
        ry += 0.4f;
        rz += 0.3f;
	}

public:
	RenderWindow()
	{
		texman = new TextureManager();
		sceneman = new SceneManager();
		light_position[0] = 0.0f;
		light_position[1] = 1.0f;
		light_position[2] = 1.0f;
		light_position[3] = 0.0f;
		dist = -8.0f;
		rx = ry = rz = 0.0f;
	}
	~RenderWindow()
	{
		delete sceneman;
		delete texman;
	}
};

int main(int argc, char *argv[])
{
	RenderWindow lp;

	lp.setTitle("Object Viewer");
	return lp.start(argc, argv);
}

