#ifndef _GLWINDOW_H_
#define _GLWINDOW_H_
#include <SDL/SDL.h>

/**
 * representação de teclas de controle enviadas pelos métodos
 * onKeyDown, onKeyPress, onKeyUp, onMouseDown e onMouseUp
 * por exemplo quando você pressiona Ctrl+P o state(estado) é
 * o LeftCtrl
**/
typedef enum
{
	LeftCtrl   = 0x01,
	RightCtrl  = 0x02,
	LeftShift  = 0x04,
	RightShift = 0x08,
	LeftAlt    = 0x10,
	RightAlt   = 0x20,
	FnKey      = 0x40,
	CapsLock   = 0x80
} KeyState;

/**
 * classe responsável por facilitar a implementação de uma janela
 * opengl, nela é possível também receber eventos do mouse e do teclado
 * além de implementar funções que mudam a resolução para tela cheia, impedir
 * que o ponteiro do mouse saia da tela
**/
class GLWindowBase
{
public:
	GLWindowBase();
	~GLWindowBase();
	/****** Window *******/

	/** obtém a largura em pixels da área da janela renderizável */
	int getWidth();

	/** obtém a altura em pixels da área da janela renderizável */
	int getHeight();

	/** ajusta o quandro de renderização para a configuração atual do tamanho
	 * e configura para que seja criado objetos 3D
	**/
	void resize3DScene();

	/** ajusta o quadro de renderização para a configuração atual do tamanho
	 * e configura para que seja criado objetos 2D
	**/
	void resize2DScene();

	/** obtém o estado atual da janela(tela cheia ou não) */
	bool inFullscreen();

	/** define o estado atual da janela(tela cheia ou não) */
	void setFullscreen(bool fullscreen);

	/** mostra ou esconde o cursor do mouse */
	void showMouse(bool show);

	/** move o cursor do mouse para a posição relativa à janela informada em x e y */
	void setMousePos(int x, int y);

	/** trava ou destrava o mouse da área da região renderizável */
	void lockMouse(bool lock);

	/** permite que o cursor do mouse, não perca o foco quando movido para
	 * fora da janela
	**/
	void setMouseCapture();

	/** libera o cursor do mouse e permite a perda de foco da janela */
	void releaseMouseCapture();

	/** inicia a execução da aplicação criando a janela e configurando-a
	 * a fim de permitir a utilização da biblioteca OpenGL
	**/
	int start(int argc, char * argv[]);

	/** Para a renderização e fecha a aplicação */
	void close();

	/** altera o título da janela para o informado no parâmetro 'title' */
	void setTitle(const char * title);

	/** ontém o título da janela */
	const char * getTitle();

	/** aplica na tela do monitor a imagem renderizada em 'render' */
	void swapBuffers();

	/** retorna a quantidade de quadros sendo desenhados a cada segundo */
	float getFPS();

	/** informa a quantidade de quandros a ser desenhado por segundo */
	void setFrameRate(int fps);

	/** controla o tempo da renderização evitando a super aceleração */
	void delay();
protected:
	//Render
	/** função mais importante da aplicação, responsável pelo desenho da janela
	 * para isso ela deverá ser herdada, a mesma já é controlada por um
	 * temporizador que evita a aceleração indesejada das animações
	**/
	virtual void render();

	/** obtem informação de como a janela será
	 * por padrão a janela terá 640x480 e 32 bits de profundidade,
	 * em tela normal, caso queira mudar basta herdar esse método e atribuir
	 * os novos valores
	**/
	virtual void getWindowInfo(int & width, int & height, int & bpp,
							   bool & fullscreen, bool & resizable);

	/** função chamada pela função 'start' no início da mesma */
	virtual bool onInit(int argc, char * argv[]);

	/** função chamda por 'start', após a janela ter sido criada com sucesso */
	virtual void onCreate();

	/** função chamada ao término do laço que trata os eventos */
	virtual void onDestroy();

	//Events
	/** evento acionado quando é pressionado uma tecla, 'key' é essa tecla */
	virtual void onKeyDown(int key, int state);

	/** evento acionado quando é liberado uma tecla, 'key' é essa tecla */
	virtual void onKeyUp(int key, int state);

	/** evento acionado quando o mouse é movido */
	virtual void onMouseMove(int x, int y);

	/** evento acionado quando um botão do mouse é pressionado, 'button' é
	 * o número desse botão e iniciado apartir do 1, x e y é a posição em que foi
	 * pressionado
	**/
	virtual void onMouseDown(int x, int y, int button, int state);

	/** evento acionado quando um botão do mouse é liberado, 'state' é o estado
	 * das teclas de controle Ctrl, Alt, Shift
	**/
	virtual void onMouseUp(int x, int y, int button, int state);

	/** evento acionado quando a janela é redimencionada */
	virtual void onResize(int newWidth, int newHeight);

	/** evento acionado quando a janela é movida */
	virtual void onMove(int x, int y);

	/** evento acionado quando o botão fechar da janela é clicado
	 * caso seja retornado true, a janela será fechada, e se false for
	 * retornado nada aconecerá com a janela
	**/
	virtual bool onClose();
private:
	/* Métodos privados acessíveis somente a essa classe ou por meio de
	 * funções get e set
	 */
	/* variável responsável pelo laço principal do programa
	 * enquanto seu valor for false, os eventos serão disparados, e a
	 * renderização é continuada
	**/
	bool done;

	SDL_Surface* screen;    /* janela de desenho */
	bool fullscreen;        /* Guarda o estado da janela, tela cheia ou não */
	bool resizable;         /* Informa se a janela é redimensionável */
	char * title;           /* contém o título da janela */

	int width, height;      /* informa a largura e altura da área renderizável */
	int bpp;                /* quantidade de bits de profundidade das cores */
	int old_x, old_y;       /* usado para salvar a posição da janela, quando
                             * volta do estado de tela cheia
                            **/
	int x, y;               /* informa a posição x, y da janela */
	bool mlock;             /* informa se o mouse está preso à tela */
	int mcapture;           /* informa se o mouse está sendo usado apenas para
                             * essa janela, o mouse só será liberado quando seu
                             * valor for 0, para isso usa-se a função
                             * SetMouseCapture e ReleaseMouseCapture
                            **/
	//Timer
	Uint32 lastTicks;      /* guarda um tempo de relógio pra que seja possível
                             * estabilizar o processo de renderização para
                             * computadores muito rápido
                            **/
	Uint32 startTicks;       /* guarda um tempo de relógio para que seja
                               * possível calcular a taxa de quadros por segundo
                              **/

	unsigned char frameCount; /* Informa a quantidade de quadros processados */
	unsigned char frameRate;  /* informa a taxa de quadros que está sendo usada */
	unsigned char fpsCount;   /* contagem dos quadros */
	float fps;                /* taxa de quandros medida em segundos */
	inline void handleEvents(); /* manipula os eventos da janela */
};

#endif

